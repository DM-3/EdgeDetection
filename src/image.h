#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


class Image {
public:
    Image(uint32_t t_width, uint32_t t_height);
    Image(std::string t_load_path);
    ~Image();

    void load(std::string t_load_path);
    void store(std::string t_store_path);

    uint32_t getWidth();
    uint32_t getHeight();

private:
    uint32_t m_width;
    uint32_t m_height;
    char* m_arr;
};