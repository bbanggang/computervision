#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f cp(src.cols / 2.f, src.rows / 2.f);	// 영상 중심 좌표 (고정)
	double totalAngle = 0.0;			// 누적 회전각도

	imshow("dst", src);

	while (true) {
		int key = waitKey(0);	// 키 입력 대기

		if (key == 'r') {
			totalAngle -= 10.0;	// r키: 시계방향 10도 (음수 = 시계방향)
		} else if (key == 'b') {
			totalAngle += 10.0;	// b키: 반시계방향 10도 (양수 = 반시계방향)
		} else if (key == 'q') {
			break;			// q키: 종료
		} else {
			continue;		// r, b, q 외 키는 무시
		}

		// 360도 범위로 정규화 (36번 누르면 원본으로 복귀)
		if (totalAngle >= 360.0) totalAngle -= 360.0;
		if (totalAngle <= -360.0) totalAngle += 360.0;

		Mat M = getRotationMatrix2D(cp, totalAngle, 1);	// 누적 각도로 회전 행렬 생성

		Mat dst;
		warpAffine(src, dst, M, src.size());	// 항상 원본에 1회 적용 → 왜곡 방지

		cout << "누적 회전각도: " << totalAngle << "도" << endl;
		imshow("dst", dst);
	}

	return 0;
}
