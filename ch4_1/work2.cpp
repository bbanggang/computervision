#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

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
		Mat bright_frame = frame + Scalar(100, 100, 100);	// BGR 각 채널에 100을 더해 밝기 증가 
		imshow("origin", frame);			// 원본 프레임 출력
		imshow("bright", bright_frame);		// 밝기 증가된 프레임 출력
		if (waitKey(10) == 27) break;		// 10ms 대기 후 ESC(27) 입력 시 종료
	}
	return 0;
}
