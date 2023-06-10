#include <stdlib.h>
#include "filter.h"

int32_t pixelToSum(uint32_t t_pixel) {
    int32_t sum = 0;
    uint8_t mask = ~0;
    sum += int32_t(t_pixel       & uint32_t(mask));
    sum += int32_t(t_pixel >> 8  & uint32_t(mask));
    sum += int32_t(t_pixel >> 16 & uint32_t(mask));
    sum += int32_t(t_pixel >> 24 & uint32_t(mask));
    return sum /= 4;
}

uint32_t sumToPixel(int32_t t_sum) {
    uint8_t sum = t_sum > uint32_t(~uint8_t(0)) ? ~uint8_t(0) : uint8_t(t_sum);
    return (sum | (sum << 8) | (sum << 16) | (sum << 24));
}

class Kernel {
public:
    Kernel(int32_t* t_arr) {
        m_arr = t_arr;
    }

    int32_t operator*(Kernel& t) {
        int32_t sum = 0;
        for(int i = 0; i < 9; i++)
            sum += m_arr[i] * t.m_arr[i];
        return sum;
    }

private:
    //  3x3 kernel layout:      [ 0 | 1 | 2 ]
    //                          [ 3 | 4 | 5 ]
    //                          [ 6 | 7 | 8 ]
    int32_t* m_arr;
};

void passConvolution(Image& t_input_image, Image& t_output_image) {
    int32_t arr0[9] = { 1, 1, 1,  0, 0, 0, -1,-1,-1};
    Kernel k0(arr0);   
    int32_t arr1[9] = {-1,-1,-1,  0, 0, 0,  1, 1, 1};
    Kernel k1(arr1);   
    int32_t arr2[9] = { 1, 0,-1,  1, 0,-1,  1, 0,-1};
    Kernel k2(arr2);   
    int32_t arr3[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    Kernel k3(arr3); 

    for(int h = 0; h < t_input_image.getHeight() - 2; h++) {
        for(int w = 0; w < t_input_image.getWidth() - 2; w++) {

            int32_t load_pixels[9] = {
                pixelToSum(t_input_image.getPixel(w + 0, h + 0)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 0)),
                pixelToSum(t_input_image.getPixel(w + 2, h + 0)),
                
                pixelToSum(t_input_image.getPixel(w + 0, h + 1)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 1)),
                pixelToSum(t_input_image.getPixel(w + 2, h + 1)),
                
                pixelToSum(t_input_image.getPixel(w + 0, h + 2)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 2)),
                pixelToSum(t_input_image.getPixel(w + 2, h + 2))
            };
            Kernel load_kernel(load_pixels);

            int32_t f0 = k0 * load_kernel;
            int32_t f1 = k1 * load_kernel;
            int32_t f2 = k2 * load_kernel;
            int32_t f3 = k3 * load_kernel;

            int32_t total = 0;
            total += f0 > 0 ? f0 : -f0;
            total += f1 > 0 ? f1 : -f1;
            total += f2 > 0 ? f2 : -f2;
            total += f3 > 0 ? f3 : -f3;

            t_output_image.setPixel(w, h, sumToPixel(total));
        }
    }
}

void passAvgPooling(Image& t_input_image, Image& t_output_image) {
    for(int h = 0; h < t_input_image.getHeight(); h++) {
        for(int w = 0; w < t_input_image.getWidth(); w++) {
            if(h > t_input_image.getHeight() - 2 || w > t_input_image.getWidth() - 2) {
                t_output_image.setPixel(w, h, 0);
                continue;
            }

            int32_t load_pixels[9] = {
                pixelToSum(t_input_image.getPixel(w + 0, h + 0)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 0)),
                pixelToSum(t_input_image.getPixel(w + 2, h + 0)),
                
                pixelToSum(t_input_image.getPixel(w + 0, h + 1)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 1)),
                pixelToSum(t_input_image.getPixel(w + 2, h + 1)),
                
                pixelToSum(t_input_image.getPixel(w + 0, h + 2)),
                pixelToSum(t_input_image.getPixel(w + 1, h + 2)),
                pixelToSum(t_input_image.getPixel(w + 2, h + 2))
            };
            
            int32_t avg;
            for(int i = 0; i < 9; i++) 
                avg += load_pixels[i];
            avg /= 9;

            t_output_image.setPixel(w, h, sumToPixel(avg));
        }
    }
}

void passThreshold(Image& t_input_image, Image& t_output_image, uint8_t t_threshold) {
    
}