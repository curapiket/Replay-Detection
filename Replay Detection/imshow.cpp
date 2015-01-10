#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include "Helper.hpp"
using namespace std;
using namespace cv;
int main(){
	int a, b;
	cin >> a;
	b = a;
	for (; a < b + 3; ++ a){
		imshow(Helper ::intToStr6(a), imread("Frames/nba/" + Helper::intToStr6(a),1));
	}
	waitKey();
	return 0;
}
