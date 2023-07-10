// ���콺�� ���ɿ��� ���ϰ� ���ɿ����� ��� �����
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat image;
string title = "image";
// �����ͷ� ���콺 ��ǥ �����ϱ� 
Point p1(0, 0);
Point p2(0, 0);

// ���콺 �̺�Ʈ Ÿ��, x��ǥ, y��ǥ, ���콺 �̺�Ʈ �߻��� �� Ư�� ����, �Լ��� ���޵Ǵ� ������ 
void onMouse(int event, int x, int y, int flags, void* param) {
	switch (event) {
	case EVENT_LBUTTONDOWN:  // ���콺 Ŭ��
		// ���� ��ǥ �� ��ǥ ��� x,y�� ���� 
		p1.x = x;
		p1.y = y;
		p2.x = x;
		p2.y = y;
		break;

	case EVENT_LBUTTONUP: // ���콺 Ŭ�� ����
		// �� ��ǥ ���� 
		p2.x = x;
		p2.y = y;
		cout << "p1=(" << p1.x << ", " << p1.y << ")" << endl;
		cout << "p2=(" << p2.x << ", " << p2.y << ")" << endl;
		showNewImg(); // �̹��� ������ 
		break;

	default:	break;
	}
}

void showNewImg() {//���ɿ����� �´� ���ο� �����츦 ǥ��
	double alpha = 1.5;
	int beta = 30;
	int width = p2.x - p1.x;
	int heigt = p2.y - p1.y;
	Rect roi(p1.x, p1.y, width, heigt);//���ɿ��� 
	Mat draggedImage = image.clone();//ȣ�� �� �� ���� �巡�׵� �̹����� ���� ����
	//Ŭ���ø��� ȣ���̴� Ŭ������ ���������� ��ø��Ű�� �ʴ´ٴ� ��
	Mat newimg = draggedImage(roi);

	// ��⿵������ �ٲٱ� 
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
