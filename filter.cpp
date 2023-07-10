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

    // ��� ���� ������ Ŀ�� ������
    int kernelSize = 20; 
    Mat dst;
   
    blur(src, dst, Size(kernelSize, 1));
    // blur(�Է¿���, ��¿���, ����ũ�� ũ�� ����)
    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    return 0;
}