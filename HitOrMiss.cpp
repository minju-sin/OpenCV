#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    // 이미지 파일 로드
    Mat inputImage = imread("d:/images/HitMissInput.png", IMREAD_GRAYSCALE);

    // 찾고자 하는 글자의 이미지 로드 및 이진화
    Mat templateImage = imread("d:/images/found_e.png", IMREAD_GRAYSCALE);
    Mat binaryTemplate;
    threshold(templateImage, binaryTemplate, 128, 255, THRESH_BINARY);

    // 구조 요소 생성
    Mat element = binaryTemplate.clone();

    // 팽창 연산 수행
    Mat dilated;
    dilate(inputImage, dilated, element);

    // 침식 연산 수행
    Mat eroded;
    erode(inputImage, eroded, element);

    // 찾은 문자 영역 추출
    Mat result;
    subtract(dilated, eroded, result);

    // 찾은 문자에 빨간 동그라미 표시
    vector<vector<Point>> contours;
    findContours(result, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat outputImage = imread("d:/images/HitMissInput.png");

    for (const auto& contour : contours) {
        Rect boundingRect = cv::boundingRect(contour);
        Mat roi = inputImage(boundingRect);

        // 템플릿 매칭 수행
        Mat matchResult;
        matchTemplate(roi, binaryTemplate, matchResult, TM_CCOEFF_NORMED);

        double minVal, maxVal;
        Point minLoc, maxLoc;

        while (true) {
            minMaxLoc(matchResult, &minVal, &maxVal, &minLoc, &maxLoc);

            // 매칭 결과를 이용하여 일치하는지 확인
            if (maxVal >= 0.8) {
                Point2f center(maxLoc.x + boundingRect.x + binaryTemplate.cols / 2,
                    maxLoc.y + boundingRect.y + binaryTemplate.rows / 2);
                circle(outputImage, center, binaryTemplate.cols / 2, Scalar(0, 0, 255), 2);

                // 이미지에서 찾은 영역을 검은색으로 채우기
                rectangle(matchResult, Rect(maxLoc, binaryTemplate.size()), Scalar(0), FILLED);
            }
            else {
                break;
            }
        }
    }

    // 결과 이미지 출력
    imshow("Hit-or-Miss", outputImage);
    waitKey(0);

    return 0;
}
