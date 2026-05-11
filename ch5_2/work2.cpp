#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat dst(src.rows, src.cols, src.type());	// src와 동일한 크기·타입의 출력 이미지 생성

	float alpha = 1.f;	// 명암비 조정 계수

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + (src.at<uchar>(j, i) - 128) * alpha);
			// dst = src + (src - 128) * alpha: 128 기준으로 밝은 픽셀은 더 밝게, 어두운 픽셀은 더 어둡게
		}
	}

	imshow("src", src);	// 원본 이미지 출력
	imshow("dst", dst);	// 명암비 조정된 이미지 출력
	waitKey();
	return 0;
}