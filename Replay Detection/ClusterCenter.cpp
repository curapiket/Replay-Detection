#include "ClusterCenter.hpp"

ClusterCenter :: ClusterCenter(const vector<double>& clusterCenter){
	center.assign(clusterCenter.begin(),clusterCenter.end());
}

double ClusterCenter :: distance(const vector<double>& point){
	double ret = 0;
	for(int i = 0; i < center.size(); ++ i){
		ret += (center[i] - point[i])*(center[i] - point[i]);
	}
	return ret;
}
