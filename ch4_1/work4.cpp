#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void DrawRedLine(Mat& frame) {
	for (int i = 0; i < frame.rows; i++) {					// 모든 행을 순회
		frame.at<Vec3b>(i, frame.cols / 2) = Vec3b(0, 0, 255);	// 열 방향 중앙에 빨간색 세로선 그리기
	}
	for (int i = 0; i < frame.cols; i++) {					// 모든 열을 순회
		frame.at<Vec3b>(frame.rows / 2, i) = Vec3b(0, 0, 255);	// 행 방향 중앙에 빨간색 가로선 그리기
	}
}

int main(void) {
	VideoCapture cap(0);					// 기본 웹캠(인덱스 0) 열기
	if (!cap.isOpened()) {					// 웹캠 열기 실패 시
		cerr << "Camera open failed" << endl;
		return -1;
	}
	Mat frame;
	while (true) {
		cap >> frame;						// 웹캠에서 프레임 캡처
		if (frame.empty()) {				// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		DrawRedLine(frame);					// 캡처한 프레임에 빨간색 십자선 그리기
		imshow("frame", frame);				// 십자선이 그려진 프레임 출력
		if (waitKey(10) == 'q') break;		// 10ms 대기 후 'q' 입력 시 종료
	}
}
