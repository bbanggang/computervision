#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat dst(src.rows, src.cols, src.type());	// src와 동일한 크기·타입의 출력 이미지 생성

	float s = 2.f;	// 밝기 배율 (2배)

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>((s * src.at<uchar>(j, i)));
			// 각 픽셀에 s를 곱한 값 저장 (saturate_cast로 0~255 범위 클리핑)
		}
	}

	imshow("src", src);	// 원본 이미지 출력
	imshow("dst", dst);	// 밝기 조정된 이미지 출력
	waitKey();
	return 0;
}