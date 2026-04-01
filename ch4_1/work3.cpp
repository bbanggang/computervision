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
	int saved_count = 0;					// 저장된 파일 수 (파일명 순번에 사용)
	string filename;
	while (true) {
		cap >> frame;						// 웹캠에서 프레임 캡처
		if (frame.empty()) {				// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		imshow("frame", frame);				// 현재 프레임 출력
		int key = waitKey(10);				// 10ms 대기, 그 사이 키 입력 감지
		if (key == 's') {					// 's' 키 입력 시 현재 프레임 저장
			if (saved_count < 10) filename = "frame0" + to_string(saved_count) + ".jpg";	// 한 자리 수: "frame00.jpg" ~ "frame09.jpg"
			else  filename = "frame" + to_string(saved_count) + ".jpg";						// 두 자리 수: "frame10.jpg" ~
			if (imwrite(filename, frame)) {		// 파일 저장 성공 시
				cout << "Saved : " << filename << endl;		// 저장된 파일명 콘솔 출력
				saved_count++;				// 저장 횟수 증가
			}
		}
		if (key == 'Q' || key == 'q') break;	// 'q' 또는 'Q' 입력 시 종료
	}
}
