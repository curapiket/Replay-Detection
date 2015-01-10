#ifndef LOGO_NOISE_REMOVER_HPP
#define LOGO_NOISE_REMOVER_HPP
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ShotCorrelationEvaluator.hpp"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <fstream>
using namespace std;
using namespace cv;

class LogoNoiseRemover
{
	public:
	static vector<pair<int,int> > remove(string fileName, string imgName);
};
#endif
