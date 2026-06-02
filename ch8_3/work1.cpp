#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	Point2f cp(src.cols / 2.f, src.rows / 2.f);	// 입력영상 중심 좌표
	Mat M = getRotationMatrix2D(cp, -45, 1);	// 시계방향 45도 회전 (음수 = 시계방향)

	// 1단계: 입력영상 크기 그대로 회전 변환 적용
	Mat rotated;
	warpAffine(src, rotated, M, src.size());

	// 2단계: 회전 결과영상을 2배로 확대
	Mat dst;
	resize(rotated, dst, Size(), 2, 2);	// x, y 방향 각각 2배 확대

	imshow("src", src);
	imshow("rotated", rotated);
	imshow("dst", dst);
	waitKey();
	return 0;
}