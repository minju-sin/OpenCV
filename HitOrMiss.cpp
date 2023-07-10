#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    // �̹��� ���� �ε�
    Mat inputImage = imread("d:/images/HitMissInput.png", IMREAD_GRAYSCALE);

    // ã���� �ϴ� ������ �̹��� �ε� �� ����ȭ
    Mat templateImage = imread("d:/images/found_e.png", IMREAD_GRAYSCALE);
    Mat binaryTemplate;
    threshold(templateImage, binaryTemplate, 128, 255, THRESH_BINARY);

    // ���� ��� ����
    Mat element = binaryTemplate.clone();

    // ��â ���� ����
    Mat dilated;
    dilate(inputImage, dilated, element);

    // ħ�� ���� ����
    Mat eroded;
    erode(inputImage, eroded, element);

    // ã�� ���� ���� ����
    Mat result;
    subtract(dilated, eroded, result);

    // ã�� ���ڿ� ���� ���׶�� ǥ��
    vector<vector<Point>> contours;
    findContours(result, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat outputImage = imread("d:/images/HitMissInput.png");

    for (const auto& contour : contours) {
        Rect boundingRect = cv::boundingRect(contour);
        Mat roi = inputImage(boundingRect);

        // ���ø� ��Ī ����
        Mat matchResult;
        matchTemplate(roi, binaryTemplate, matchResult, TM_CCOEFF_NORMED);

        double minVal, maxVal;
        Point minLoc, maxLoc;

        while (true) {
            minMaxLoc(matchResult, &minVal, &maxVal, &minLoc, &maxLoc);

            // ��Ī ����� �̿��Ͽ� ��ġ�ϴ��� Ȯ��
            if (maxVal >= 0.8) {
                Point2f center(maxLoc.x + boundingRect.x + binaryTemplate.cols / 2,
                    maxLoc.y + boundingRect.y + binaryTemplate.rows / 2);
                circle(outputImage, center, binaryTemplate.cols / 2, Scalar(0, 0, 255), 2);

                // �̹������� ã�� ������ ���������� ä���
                rectangle(matchResult, Rect(maxLoc, binaryTemplate.size()), Scalar(0), FILLED);
            }
            else {
                break;
            }
        }
    }

    // ��� �̹��� ���
    imshow("Hit-or-Miss", outputImage);
    waitKey(0);

    return 0;
}
