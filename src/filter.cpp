#include <xmmintrin.h>
#include "filter.h"

int32_t pixelToSum(uint32_t t_pixel) {
    int32_t sum = 0;
    uint8_t mask = ~0;
    sum += int32_t(t_pixel       & uint32_t(mask));
    sum += int32_t(t_pixel >> 8  & uint32_t(mask));
    sum += int32_t(t_pixel >> 16 & uint32_t(mask));
    sum += int32_t(t_pixel >> 24 & uint32_t(mask));
    return sum;
}

uint32_t sumToPixel(int32_t t_sum) {
    uint8_t sum = t_sum > uint32_t(~uint8_t(0)) ? ~uint8_t(0) : uint8_t(t_sum);
    return (sum | (sum << 8) | (sum << 16) | (sum << 24));
}

class Kernel {
public:
    Kernel(int32_t t_0, int32_t t_1, int32_t t_2, int32_t t_3) :
        m_0(t_0), m_1(t_1), m_2(t_2), m_3(t_3)
    {}

    int32_t operator*(Kernel& t) {
        return  m_0 * t.m_0 + m_1 * t.m_1 
              + m_2 * t.m_2 + m_3 * t.m_3;
    }

private:
    //  2x2 kernel layout:      [ m_0 | m_1 ]
    //                          [ m_2 | m_3 ]
    int32_t m_0, m_1, m_2, m_3;
};

void passConvolution(Image& t_input_image, Image& t_output_image) {
    Kernel k0(-1,  1, -1,  1);
    Kernel k1( 1, -1,  1, -1);
    Kernel k2(-1, -1,  1,  1);
    Kernel k3( 1,  1, -1, -1);

    //Kernel k0(0, 1, 0, 1);
    //Kernel k1(1, 0, 1, 0);
    //Kernel k2(0, 0, 1, 1);
    //Kernel k3(1, 1, 0, 0);

    int h, w;
    for(h = 0; h < t_input_image.getHeight(); h++) {
        for(w = 0; w < t_input_image.getWidth(); w++) {
            Kernel load_kernel(
                pixelToSum(t_input_image.getPixel(w + 0, h + 0)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 0)),
                pixelToSum(t_input_image.getPixel(w + 0, h + 1)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 1)));

            int32_t total = 0;
            total += (k0 * load_kernel) * (k0 * load_kernel);
            total += (k1 * load_kernel) * (k1 * load_kernel);
            total += (k2 * load_kernel) * (k2 * load_kernel);
            total += (k3 * load_kernel) * (k3 * load_kernel);

            t_output_image.setPixel(w, h, sumToPixel(total));
        }
    }
}

void passThreshold(Image& t_working_image, uint8_t t_threshold) {

}