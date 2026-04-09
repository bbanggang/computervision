#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int LButtonUp_count = 0, LButtonDown_count = 0, MouseMove_count = 0;	// 마우스 이벤트별 카운트 변수
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse);	// 마우스 콜백 함수 등록
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);				// 100ms 대기
		if (key == 'q') break;			// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
	switch (event) {
	case EVENT_LBUTTONUP:
		LButtonUp_count++;
		cout << "EVENT_LBUTTONUP" << LButtonUp_count << endl;		// 좌클릭 해제 횟수 출력
		break;
	case EVENT_LBUTTONDOWN:
		LButtonDown_count++;
		cout << "EVENT_LBUTTONDOWN" << LButtonDown_count << endl;	// 좌클릭 횟수 출력
		break;
	case EVENT_MOUSEMOVE:
		MouseMove_count++;
		cout << "EVENT_MOUSEMOVE" << MouseMove_count << endl;		// 마우스 이동 횟수 출력
		break;
	default:
		break;
	}
}
