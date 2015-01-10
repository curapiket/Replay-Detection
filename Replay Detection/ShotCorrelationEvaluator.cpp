#include "ShotCorrelationEvaluator.hpp"
#include "Helper.hpp"
#include <cmath>
double ShotCorrelationEvaluator :: getCorrelation(const vector<Mat> shot1, const vector<Mat> shot2){
	double mxCorrelation = 0.0;
	for(int i = 0; i < shot1.size() - 5; ++ i){
		for(int j = 0; j < shot2.size() - 5; ++ j){
			double tmp = 0;
			for(int k = 0; k < 5; ++ k)
				tmp += compareHist(shot1[i+k],shot2[j+k],0);
			mxCorrelation = max(mxCorrelation, tmp/5.0);
		}
	}
	return mxCorrelation;
}
double ShotCorrelationEvaluator :: getSelfCorrelation(const vector<Mat> shot1){
	double mxCorrelation = 0.0;
	int cnt = 0;
	for(int i = 0; i < shot1.size() - 1; ++ i){
		for(int j = i+1; j < shot1.size() - 1; ++ j){
			mxCorrelation += compareHist(shot1[i],shot1[j],0);
			cnt ++;
		}
	}
	return mxCorrelation/cnt;
}
