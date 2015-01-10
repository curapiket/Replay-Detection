#ifndef CLUSTER_CENTER_HPP
#define CLUSTER_CENTER_HPP
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

class ClusterCenter{
	private:
	vector<double> center;
	public:
	ClusterCenter (const vector<double>& clusterCenter);
	double distance(const vector<double>& point);
};
#endif
