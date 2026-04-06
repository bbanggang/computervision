#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	VideoCapture cap(0);							// 기본 웹캠(인덱스 0) 열기
	if (!cap.isOpened()) {							// 웹캠 열기 실패 시
		cerr << "Camera open failed" << endl;
		return -1;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));		// 웹캠 프레임 너비 가져오기
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));	// 웹캠 프레임 높이 가져오기
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');	// 출력 동영상 코덱을 DIVX로 설정
	VideoWriter outputVideo("press_s_output.avi", fourcc, 30, Size(w, h));	// 30fps, 웹캠과 동일한 해상도로 출력 파일 생성
	if (!outputVideo.isOpened()) {					// 출력 파일 생성 실패 시
		cout << "File open failed!" << endl;
		return -1;
	}
	Mat frame;
	bool isSave = false;							// 녹화 시작 여부 플래그
	while (true) {
		cap >> frame;								// 항상 프레임을 읽어 카메라 버퍼 누적 방지
		if (frame.empty()) {						// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		imshow("frame", frame);						// 항상 출력하여 waitKey 키 입력 감지 보장
		if (isSave) outputVideo << frame;			// 's' 키 입력 이후에만 파일 저장
		int key = waitKey(33);						// 약 30fps에 맞춰 33ms 대기, 키 입력 감지
		if (key == 's') isSave = true;				// 's' 키 입력 시 녹화 시작
		if (key == 'q' || key == 'Q') break;		// 'q' 또는 'Q' 입력 시 종료
	}
	return 0;
}
