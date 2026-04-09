#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void on_mouse(int event, int x, int y, int flags, void* userdata);
Mat img;

int main(void) {
	img = Mat(200, 400, CV_8UC3, Scalar(255, 255, 255));	// 200x400 크기의 흰색 3채널 이미지 생성
	namedWindow("img");
	setMouseCallback("img", on_mouse);	// 마우스 콜백 등록
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
	case EVENT_LBUTTONDOWN:
		img.setTo(Scalar(0, 0, 255));	// 좌클릭: 이미지 전체를 빨간색으로 변경
		break;
	case EVENT_RBUTTONDOWN:
		img.setTo(Scalar(255, 0, 0));	// 우클릭: 이미지 전체를 파란색으로 변경
		break;
	}
}
