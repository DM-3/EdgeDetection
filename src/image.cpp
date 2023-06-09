#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


Image::Image(uint32_t t_width, uint32_t t_height) :
    m_width(t_width), m_height(t_height)
{
    m_arr = new unsigned char[m_width * m_height * 4];
}

Image::Image(std::string t_load_path) {
    this->load(t_load_path);
}

Image::~Image() {
    if(m_arr) delete[] m_arr;
}


void Image::load(std::string t_load_path) {
    if(m_arr) delete[] m_arr;

    int width, height, channels;
    m_arr = stbi_load(t_load_path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if(!m_arr) throw std::invalid_argument("Failed to load image");

    m_width = uint32_t(width);
    m_height = uint32_t(height);
}

void Image::store(std::string t_store_path) { 
    if(!stbi_write_jpg(t_store_path.c_str(), m_width, m_height, 4, m_arr, 100)) {
        throw std::runtime_error("Failed to save image");
    }
}



uint32_t Image::getWidth() { return m_width; }

uint32_t Image::getHeight() { return m_height; }



uint32_t Image::getPixel(int t_x, int t_y) {
    if(t_x >= m_width || t_y >= m_height) return 0;
    return ((uint32_t*)m_arr)[t_y * m_width + t_x];
}

void Image::setPixel(int t_x, int t_y, uint32_t t_value) {
    if(t_x >= m_width || t_y >= m_height) return;
    ((uint32_t*)m_arr)[t_y * m_width + t_x] = t_value;
}