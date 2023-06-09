#ifndef FILTER_H
#define FILTER_H

#include "image.h"

void passConvolution(Image& t_input_image, Image& t_output_image);

void passThreshold(Image& t_working_image, uint8_t t_threshold);

#endif