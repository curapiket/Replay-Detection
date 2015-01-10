
#include "Helper.hpp"

string Helper :: intToStr6(int num){
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

