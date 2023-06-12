#ifndef FILTER_H
#define FILTER_H

#include "image.h"

// performs a convolution across t_input_image,
// using 4 fixed 3x3 filters in horizontal and vertical layout,
// and stores the result in t_output_image
void passConvolution(Image& t_input_image, Image& t_output_image);

// pools in a 3x3 grid of neighbouring pixels from t_input_image,
// computes the average,
// and stores the result in t_output_image
void passAvgPooling(Image& t_input_image, Image& t_output_image);

// stores in t_output_image:
// a max value of 255, for every pixel in t_input_image greater than t_threshold,
// a min value of 0, for every pixel in t_input_image less that t_threshold.
void passThreshold(Image& t_input_image, Image& t_output_image, uint8_t t_threshold);

#endif