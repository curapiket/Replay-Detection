#include "DescriptorExtractor.hpp"

Mat DescriptorExtractor :: getHueDescriptor(Mat src, int nbins){
	Mat dst;
	cvtColor( src, dst, CV_BGR2HSV );

	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> hsv_planes;
	split( dst, hsv_planes );
	/// Establish the number of bins
	int histSize = nbins;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat h_hist;

	/// Compute the histograms:
	calcHist( &hsv_planes[0], 1, 0, Mat(), h_hist, 1, &histSize, &histRange, uniform, accumulate );

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(h_hist, h_hist, 0, hist_h, NORM_MINMAX, -1, Mat() );
	return h_hist;
}

