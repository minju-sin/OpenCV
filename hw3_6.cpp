// 화소처리 6번 선형대비확대
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("d:/images/lenna.jpg", IMREAD_GRAYSCALE);
	imshow("원본 이미지", img);

	Mat table(1, 256, CV_8U);

	uchar* p = table.ptr();
	for (int i = 0; i < 256; ++i) {
		if (i > 120 && i < 192) {
			p[i] = 0;
		}
		else p[i] = i;
	}


	Mat LUTimg;
	LUT(img, table, LUTimg);

	imshow("LUT 이미지", LUTimg);
	waitKey(0);

	return 0;
}