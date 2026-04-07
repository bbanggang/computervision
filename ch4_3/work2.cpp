#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void DrawGridLine(Mat& img) {
	for (int i = 0; i < 3; i++) {																		// 세로 격자선 3줄
		line(img, Point(img.cols * (i + 1) / 4, 0), Point(img.cols * (i + 1) / 4, img.rows), Scalar(255, 255, 255));	// 열 방향 1/4, 2/4, 3/4 위치에 세로선 그리기
	}
	for (int i = 0; i < 3; i++) {																		// 가로 격자선 3줄
		line(img, Point(0, img.rows * (i + 1) / 4), Point(img.cols, img.rows * (i + 1) / 4), Scalar(255, 255, 255));	// 행 방향 1/4, 2/4, 3/4 위치에 가로선 그리기
	}
}

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawGridLine(img);								// 흰색 격자선 그리기
	imshow("Line", img);							// 격자선이 그려진 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
