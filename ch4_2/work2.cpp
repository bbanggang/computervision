#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	VideoCapture cap("stopwatch.avi");				// 동영상 파일 열기
	if (!cap.isOpened()) {							// 동영상 열기 실패 시
		cerr << "video open failed" << endl;
		return -1;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));		// 원본 동영상의 프레임 너비 가져오기
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));	// 원본 동영상의 프레임 높이 가져오기
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');	// 출력 동영상 코덱을 DIVX로 설정
	VideoWriter outputVideo("output.avi", fourcc, 30, Size(w, h));	// 30fps, 원본과 동일한 해상도로 출력 파일 생성
	if (!outputVideo.isOpened()) {					// 출력 파일 생성 실패 시
		cout << "File open failed!" << endl;
		return -1;
	}
	Mat frame, bright;
	while (true) {
		cap >> frame;								// 동영상에서 프레임 읽기
		if (frame.empty()) {						// 프레임 읽기 실패 또는 영상 종료 시
			cerr << "frame empty" << endl;
			break;
		}
		bright = frame + Scalar(100, 100, 100);		// BGR 각 채널에 100을 더해 밝기 증가 (255 초과 시 자동 포화 처리)
		outputVideo << bright;						// 밝기 조정된 프레임을 출력 파일에 저장
		imshow("frame", frame);						// 원본 프레임 출력
		imshow("bright", bright);					// 밝기 조정된 프레임 출력
		int key = waitKey(33);						// 약 30fps에 맞춰 33ms 대기, 키 입력 감지
		if (key == 'q' || key == 'Q') break;		// 'q' 또는 'Q' 입력 시 종료
	}
	return 0;
}

