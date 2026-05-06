#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환
	switch (event) {
	case EVENT_LBUTTONDOWN:
		img += 10;		// 좌클릭: 이미지 전체 밝기 +10
		break;
	case EVENT_RBUTTONDOWN:
		img -= 10;		// 우클릭: 이미지 전체 밝기 -10
		break;
	default:
		break;
	}
}

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse, &img);	// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);
		if (key == 'q') break;		// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
