#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
using namespace cv;
string intToString(int num){
	string ret = "";
	while(num != 0){
		ret += ('0' + num%10);
		num /= 10;
	}
	reverse(ret.begin(),ret.end());
	while(ret.size() != 6)
		ret = "0" + ret;
	return ret + ".jpg";
}
/**
 * @function main
 */
int main( int argc, char** argv )
{
	vector<Mat> hists;
	int rows = 30000;
	for(int i = 20000; i < 50000; ++ i){
		
		cerr << i << endl;
  Mat src, dst;

  /// Load image
  src = imread( "Frames/As/" + intToString(i), 1 );
  waitKey();
  if( !src.data )
    { return -1; }

  /// Separate the image in 3 places ( B, G and R )
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

  // Draw the histograms for B, G and R
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );

  Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

  /// Normalize the result to [ 0, histImage.rows ]
  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  b_hist.push_back(g_hist);
  b_hist.push_back(r_hist);
  
  Mat dest;
  transpose(b_hist,dest);
  hists.push_back(dest);
  //cerr << dest.cols << endl;
}
 cerr << hists[0].cols << endl;
 int a[2] = {hists[0].cols,rows};
 int clusterCount = 4, attempts = 5;
 Mat centers,labels;
 //Mat samples(2,a,CV_64F,Scalar::all(0));
//cerr << samples.rows << ' ' << samples.cols << endl;
Mat samples;
 for(int i = 0; i < hists.size(); ++ i)
	samples.push_back(hists[i]);

 cerr << samples.rows << ' ' << samples.cols << endl;
 kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_RANDOM_CENTERS, centers );
  cout << centers.cols << ' ' << centers.rows << endl;
  cout << centers << endl;
  waitKey(0);

  return 0;
}
