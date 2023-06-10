#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <inttypes.h>
#include <stdlib.h>

class Image {
public:
    Image(uint32_t t_width, uint32_t t_height);
    Image(std::string t_load_path);
    ~Image();

    void load(std::string t_load_path);
    void store(std::string t_store_path);

    uint32_t getWidth();
    uint32_t getHeight();

    uint32_t getPixel(int t_x, int t_y);
    void setPixel(int t_x, int t_y, uint32_t t_value);

private:
    uint32_t m_width  = 0;
    uint32_t m_height = 0;
    unsigned char* m_arr = nullptr;
};

#endif