#ifndef DESCRIPTOR_EXTRACTOR_HPP
#define DESCRIPTOR_EXTRACTOR_HPP
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
using namespace cv;

class DescriptorExtractor
{
	public:
	static Mat getHueDescriptor(Mat bgr_image, int nbins = 256);
};
#endif
