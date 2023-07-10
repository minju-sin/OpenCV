#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    Mat src = imread("d:/images/1056.jpg");

    if (src.empty()) {
        cout << "Image load failed!\n";
        return -1;
    }

    // 모션 블러링 적용할 커널 사이즈
    int kernelSize = 20; 
    Mat dst;
   
    blur(src, dst, Size(kernelSize, 1));
    // blur(입력영상, 출력영상, 마스크의 크기 정의)
    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    return 0;
}