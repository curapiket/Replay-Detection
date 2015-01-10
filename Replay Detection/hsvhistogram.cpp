#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "DescriptorExtractor.hpp"
using namespace std;
using namespace cv;

/**
 * @function main
 */
 string intToStr6(int num){
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
int main( int argc, char** argv )
{
	string match;
	Mat prev;
	int start, end;
	cerr << "StartFrame EndFrame MatchFolderName" << endl;
	cin >> start >> end >> match;
	int last = start;
	int lastlogo = 0;
	vector<int> spikes;
	for(int i = start; i < end; ++ i){
		/// Load image
		Mat src = imread("Frames/"+match+"/" + intToStr6(i), 1 );
		Mat h_hist = DescriptorExtractor :: getHueDescriptor(src);
		if (i != start){
			double base_base = compareHist( h_hist, prev, 0);
			cerr << i <<endl;//<< ' ' << base_base<< endl;
			if(base_base < 0.945){
				spikes.push_back(i);
				cerr << "pushed " << i << endl;
				/*//cerr << i << ' ' << i - last << ' ' << i - lastlogo << endl;
				if(i - last >= 5 && i - last <= 10 && i - lastlogo > 30){
					cout << last << ' ' << i << endl;
					//cerr << last << ' ' << i << endl;
					lastlogo = i;
				}
				if (i - last > 10)
					last = i;*/
			}
			if (!spikes.size() == 0 && i - 10 > spikes[spikes.size() - 1]){
					int tmpLast = spikes[spikes.size() - 1];
					int tmpStart = tmpLast;
					cerr << tmpLast << ' ';
					for(int k = spikes.size() - 2; k >= 0; -- k){
						cerr << spikes[k] << ' ';
						if(tmpLast - spikes[k] < 15)
							tmpStart = spikes[k];
					}
					cerr << endl;
					if(tmpLast - tmpStart >= 8)
						cout << tmpStart << ' ' << tmpLast << endl;
					spikes.clear();
					cerr << tmpLast << ' ' << tmpStart << " cleared at " << i << endl;
				}
		}
		prev = h_hist;
	}
  waitKey(0);

  return 0;
}
