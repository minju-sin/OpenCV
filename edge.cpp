#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    int threshold_value = 127;
    Mat src = imread("d:/images/lenna.jpg", IMREAD_GRAYSCALE);

    if (src.empty()) {
        cout << "Image load failed!\n";
        return -1;
    }

    Mat dst, thr;
    Canny(src, dst, 50, 100);
    threshold(dst, thr, threshold_value, 255, THRESH_BINARY);

    imshow("src", src);
    imshow("dst", dst);
    imshow("threshold", thr);

    waitKey();
    destroyAllWindows();
}