#include "Clusterer.hpp"

Clusterer :: Clusterer(const string& clusterFileName){
	ifstream in(clusterFileName.c_str());
	int cols, clusters;
	char delimiterRemover;
	double reader;
	in >> cols >> clusters;
	in >> delimiterRemover;
	for(int i = 0; i < clusters; ++ i){
		vector<double> center;
		for(int j = 0; j < cols; ++ j){
			in >> reader;
			center.push_back(reader);
		}
		clusterCenters.push_back(ClusterCenter(center));
	}
}

int Clusterer :: getCluster(const vector<double>& point){
	double dist = clusterCenters[0].distance(point);
	int ret = 0;
	for(int i = 1; i < clusterCenters.size(); ++ i){
		double tempDist = clusterCenters[i].distance(point);
		if(tempDist < dist){
			dist = tempDist;
			ret = i;
		}
	}
	return ret;
}


