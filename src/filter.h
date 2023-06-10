#ifndef FILTER_H
#define FILTER_H

#include "image.h"

void passConvolution(Image& t_input_image, Image& t_output_image);

void passAvgPooling(Image& t_input_image, Image& t_output_image);

void passThreshold(Image& t_input_image, Image& t_output_image, uint8_t t_threshold);

#endif