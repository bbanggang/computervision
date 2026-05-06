#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

static int trackbar_pos = 0;	// 트랙바 위치 (0: 밝게, 1: 어둡게)

void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환
	switch (event) {
	case EVENT_LBUTTONDOWN:
		if(trackbar_pos == 0) img += 10;	// 트랙바 0: 좌클릭 시 밝기 +10
		else img -= 10;						// 트랙바 1: 좌클릭 시 밝기 -10
		break;
	default:
		break;
	}
}

void set_pos(int pos, void* userdata) {
	trackbar_pos = pos;		// 트랙바 위치를 전역 변수에 저장
}

int main(void) {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	namedWindow("dst");
	createTrackbar("mode", "dst", 0, 1, set_pos);		// 0~1 범위 트랙바 생성 (0: 밝게, 1: 어둡게)
	setMouseCallback("dst", on_mouse, &src);			// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	while (true) {
		imshow("dst", src);
		if (waitKey(100) == 'q') break;		// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
