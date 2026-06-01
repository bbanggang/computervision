#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) { cerr << "Camera open failed!" << endl; return -1; }

	// work5와 동일한 아핀 변환 행렬: 0.5배 축소 + (150, 100) 이동
	Mat M = Mat_<double>({ 2, 3 }, { 0.5, 0, 150, 0, 0.5, 100 });
	cout << "M = " << endl << M << endl;

	int mode = 1;	// 1: 원본(a키), 2: work5 변환(b키)

	Mat frame, dst;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		if (mode == 1) {
			imshow("dst", frame);		// a키: 원본 그대로 출력
		} else {
			warpAffine(frame, dst, M, Size());	// b키: work5 아핀 변환 적용
			imshow("dst", dst);
		}

		int key = waitKey(30);
		if      (key == 'q') break;		// q: 종료
		else if (key == 'a') mode = 1;	// a: 원본 출력
		else if (key == 'b') mode = 2;	// b: work5 변환 출력
	}

	return 0;
}
