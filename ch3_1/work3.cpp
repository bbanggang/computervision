#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main(void) {
	Rect r1(10, 10, 20, 20);		// 좌측 상단 (10,10), 폭 20, 높이 20인 사각형 생성
	Point p1(10, 10);				// 좌표 (10, 10)인 점 생성
	if (r1.contains(p1)) {			// p1이 r1 내부에 포함되는지 확인 (경계 포함)
		cout << "사각형 r1 내부에 점 p1이 존재합니다." << endl;
	}
	else {
		cout << "사각형 r1 외부에 점 p1이 존재합니다." << endl;
	}
	return 0;
}
