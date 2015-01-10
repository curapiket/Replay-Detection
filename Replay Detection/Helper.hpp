#ifndef HELPER_HPP
#define HELPER_HPP
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Clusterer.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace cv;
using namespace std;

class Helper{
	public:
	static string intToStr6(int num);
};
#endif
