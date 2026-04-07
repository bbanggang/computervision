#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void DrawRectandTiledCross(Mat& img) {
	line(img, Point(img.cols / 4, img.rows / 4), Point(img.cols * 3 / 4, img.rows / 4), 0);		// 사각형 상단 변
	line(img, Point(img.cols / 4, img.rows * 3 / 4), Point(img.cols * 3 / 4, img.rows * 3 / 4), 0);	// 사각형 하단 변
	line(img, Point(img.cols / 4, img.rows / 4), Point(img.cols / 4, img.rows * 3 / 4), 0);		// 사각형 좌측 변
	line(img, Point(img.cols * 3 / 4, img.rows / 4), Point(img.cols * 3 / 4, img.rows * 3 / 4), 0);	// 사각형 우측 변
	line(img, Point(img.cols / 4, img.rows / 4), Point(img.cols * 3 / 4, img.rows * 3 / 4), 0);	// 좌상 → 우하 대각선
	line(img, Point(img.cols / 4, img.rows * 3 / 4), Point(img.cols * 3 / 4, img.rows / 4), 0);	// 좌하 → 우상 대각선
}

int main(void) {
	Mat img(400, 400, CV_8UC1, 255);			// 400x400 크기의 흰색(255) 그레이스케일 이미지 생성
	if (img.empty()) {							// 이미지 생성 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawRectandTiledCross(img);					// 사각형과 X자 대각선 그리기
	imshow("src", img);							// 결과 이미지 출력
	waitKey(0);									// 키 입력 대기 (창 유지)
	return 0;
}
