#include "LogoNoiseRemover.hpp"
#include "Helper.hpp"
vector<pair<int,int> > LogoNoiseRemover :: remove(string fileName,string imgName){
	vector<pair<int,int> > ret, pairs;
	vector< vector<Mat> > shots;
	vector<int> resmb;
	vector<double> selfCorrelation;
	vector<vector<int> > adj;
	ifstream in(fileName.c_str());
	int start, end, avg = 0;
	
	while(in >> start >> end){
		vector<Mat> shot;
		for(int i = start; i <= end; ++ i){
			shot.push_back(DescriptorExtractor::getHueDescriptor(imread(imgName + Helper::intToStr6(i), 1 )));
		}
		shots.push_back(shot);
		pairs.push_back(pair<int,int>(start,end));
	}
	
	resmb.assign((int)shots.size(), 0);
	//selfCorrelation((int)shots.size(), 0.0);
	for(int i = 0; i < shots.size(); ++ i){
		//cout << "---- "  << i << endl;
		for(int j = i + 1; j < shots.size(); ++ j){
			//cout << j << " - " << ShotCorrelationEvaluator::getCorrelation(shots[i],shots[j]) << endl;
			if(ShotCorrelationEvaluator::getCorrelation(shots[i],shots[j]) >= 0.6){
				resmb[i] ++;
				resmb[j] ++;
				avg += 2;
			}
		}
	}
	for(int i = 0; i < shots.size(); ++ i){
		selfCorrelation.push_back(ShotCorrelationEvaluator::getSelfCorrelation(shots[i]));
	}
	avg /= shots.size();
	for(int i = 0; i < resmb.size(); ++ i)
		if(resmb[i] >= avg - 0.2*avg){
			cout << pairs[i].first << ' ' << pairs[i].second << ' ' << resmb[i] << " " << selfCorrelation[i]<< " chosen ";
			double tmp = 0;
			for(int j = 0; j < resmb.size(); ++ j)
				if(i != j && resmb[i] >= avg - 0.2*avg)
					tmp = max(tmp,ShotCorrelationEvaluator::getCorrelation(shots[i],shots[j]));
			cout << tmp<< endl;
			ret.push_back(pairs[i]);
		}
		else
			cout << pairs[i].first << ' ' << pairs[i].second << ' ' << resmb[i] << ' ' << selfCorrelation[i]<< endl;
	return ret;
}
int main(){
	LogoNoiseRemover :: remove("nba.txt", "Frames/nba/");
}
