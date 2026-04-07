#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void DrawCircle(Mat& img) {
	circle(img, Point(280, 240), 185, Scalar(255, 0, 0), 2);	// 중심 (280, 240), 반지름 185, 파란색(BGR), 두께 2인 원 그리기
}

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawCircle(img);								// 파란색 원 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
