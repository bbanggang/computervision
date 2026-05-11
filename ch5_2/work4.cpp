#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat dst(src.rows, src.cols, src.type());	// src와 동일한 크기·타입의 출력 이미지 생성

	Scalar avg = mean(src);	// 이미지 전체 픽셀의 평균값 계산
	float alpha = 1.f;		// 명암비 조정 계수

	cout << "src의 평균값 : " << avg[0] << endl;	// 평균값 출력

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + (src.at<uchar>(j, i) - avg[0]) * alpha);
			// dst = src + (src - avg) * alpha: 실제 평균을 기준으로 명암비 조정
		}
	}

	imshow("src", src);	// 원본 이미지 출력
	imshow("dst", dst);	// 명암비 조정된 이미지 출력
	waitKey();
	return 0;
}