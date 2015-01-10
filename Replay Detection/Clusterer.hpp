#ifndef CLUSTERER_HPP
#define CLUSTERER_HPP
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ClusterCenter.hpp"
#include <string>
#include <vector>
#include <fstream>
using namespace cv;
using namespace std;

class Clusterer{
	private:
	vector<ClusterCenter> clusterCenters;
	public:
	Clusterer (const string& clusterFileName);
	int getCluster(const vector<double>& point);
};
#endif
