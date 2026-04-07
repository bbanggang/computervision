#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void DrawRectandCircle(Mat& img) {
	Rect rect(Point(img.cols / 4, img.rows / 4), Size(img.cols / 2, img.rows / 2));	// 좌측 상단 (1/4, 1/4), 크기 (1/2, 1/2)인 사각형 영역 정의
	rectangle(img, rect, 0);							// 정의된 영역에 검은색 사각형 그리기
	circle(img, Point(200, 200), 100, 0);				// 중심 (200, 200), 반지름 100인 검은색 원 그리기
}

int main(void) {
	Mat img(400, 400, CV_8UC1, 255);				// 400x400 크기의 흰색(255) 그레이스케일 이미지 생성
	if (img.empty()) {								// 이미지 생성 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawRectandCircle(img);							// 사각형과 원 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
