#include "BagOfWords.hpp"


BagOfWords :: BagOfWords(const string& clusterFileName):clusterer(clusterFileName){

}

void BagOfWords :: run(const string& imgDirect, int start, int end, int window){
	for(int i = start; i + window <= end + 1; i ++){
		string rep = "";
		for(int j = 0; j < window; ++ j){
			cerr << i + j << endl;
			Mat src, dst;
			src = imread( imgDirect + Helper::intToStr6(i + j), 1);
			vector<Mat> bgr_planes;
			split( src, bgr_planes);
			/// Establish the number of bins
			int histSize = 256;

			/// Set the ranges ( for B,G,R) )
			float range[] = { 0, 256 } ;
			const float* histRange = { range };

			bool uniform = true; bool accumulate = false;

			Mat b_hist, g_hist, r_hist;

			/// Compute the histograms:
			calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
			calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
			calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

			/// Draw the histograms for B, G and R
			int hist_w = 512; int hist_h = 400;
			int bin_w = cvRound( (double) hist_w/histSize );

			Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

			/// Normalize the result to [ 0, histImage.rows ]
			normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
			normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
			normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
			b_hist.push_back(g_hist);
			b_hist.push_back(r_hist);
			vector<double> point;
			for (int k = 0; k < b_hist.cols; ++ k){
				point.push_back(b_hist.at<double>(0,k));
			}
			rep += (clusterer.getCluster(point) + 'A');
		}
		sort(rep.begin(),rep.end());
		if(rep == "AAB")
			cout << i << ' ' << i + window << endl;
		histo[rep] ++;
		classifiedFrames.push_back(rep);
	}
}
bool cmp(pair<string,int> i, pair<string,int> j){
	return i.second > j.second;
}
void BagOfWords :: display(){
	map<string,int> :: iterator it;
	vector<pair<string,int> > pairs;
	for(it = histo.begin(); it != histo.end(); ++ it){
		pairs.push_back(pair<string,int>(it->first,it->second));
	}
	sort(pairs.begin(), pairs.end(), cmp);
	for(int i = 0; i < pairs.size(); ++ i)
		cout << pairs[i].first << ' ' << pairs[i].second << endl;
}

int main(){
	BagOfWords bg("10.txt");
	bg.run("Frames/As/", 50000, 80000, 3);
	bg.display();
	return 0;
}
