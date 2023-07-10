// 마우스로 관심영역 정하고 관심영역만 밝게 만들기
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat image;
string title = "image";
// 포인터로 마우스 좌표 저장하기 
Point p1(0, 0);
Point p2(0, 0);

// 마우스 이벤트 타입, x좌표, y좌표, 마우스 이벤트 발생할 때 특정 조건, 함수로 전달되는 포인터 
void onMouse(int event, int x, int y, int flags, void* param) {
	switch (event) {
	case EVENT_LBUTTONDOWN:  // 마우스 클릭
		// 시작 좌표 끝 좌표 모두 x,y로 설정 
		p1.x = x;
		p1.y = y;
		p2.x = x;
		p2.y = y;
		break;

	case EVENT_LBUTTONUP: // 마우스 클릭 해제
		// 끝 좌표 설정 
		p2.x = x;
		p2.y = y;
		cout << "p1=(" << p1.x << ", " << p1.y << ")" << endl;
		cout << "p2=(" << p2.x << ", " << p2.y << ")" << endl;
		showNewImg(); // 이미지 보여줌 
		break;

	default:	break;
	}
}

void showNewImg() {//관심영역이 맞는 새로운 윈도우를 표시
	double alpha = 1.5;
	int beta = 30;
	int width = p2.x - p1.x;
	int heigt = p2.y - p1.y;
	Rect roi(p1.x, p1.y, width, heigt);//관심영역 
	Mat draggedImage = image.clone();//호출 될 때 마다 드래그된 이미지의 깊은 복사
	//클릭시마다 호출이니 클릭마다 반전영역을 중첩시키지 않는다는 뜻
	Mat newimg = draggedImage(roi);

	// 밝기영역으로 바꾸기 
	newimg = newimg * alpha + beta;

	imshow(title, draggedImage);
}

int main() {
	image = imread("d:/images/lenna.jpg", IMREAD_COLOR);

	imshow(title, image);

	setMouseCallback(title, onMouse, 0);
	waitKey();

	return 0;

}
