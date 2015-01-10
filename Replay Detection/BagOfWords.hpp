#ifndef BAG_OF_WORDS_HPP
#define BAG_OF_WORDS_HPP
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Clusterer.hpp"
#include "Helper.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>
using namespace cv;
using namespace std;

class BagOfWords{
	private:
	vector<string> classifiedFrames;
	map<string, int> histo;
	Clusterer clusterer;
	public:
	BagOfWords (const string& clusterFileName);
	void run(const string& imgDirect, int start, int end, int window);
	void display();
};
#endif
