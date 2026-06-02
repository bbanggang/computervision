#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) { cerr << "Camera open failed!" << endl; return -1; }

	double totalAngle = 0.0;	// 누적 회전각도 (r키 누를 때마다 -90도씩 감소)

	Mat frame, dst;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		int key = waitKey(30);
		if      (key == 'q') break;
		else if (key == 'r') {
			totalAngle -= 90.0;		// r키: 시계방향 90도
			if (totalAngle <= -360.0)
				totalAngle += 360.0;	// 360도 정규화
		}

		Point2f cp(frame.cols / 2.f, frame.rows / 2.f);	// 매 프레임 중심
		Mat M = getRotationMatrix2D(cp, totalAngle, 1);		// 누적 각도로 회전 행렬 생성
		warpAffine(frame, dst, M, frame.size());		// 새 프레임에 회전 적용

		imshow("dst", dst);
	}

	return 0;
}
