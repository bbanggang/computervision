#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;


void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환
	static Point ptOld;							// 드래그 시작점 (static: 함수 호출 간 유지)
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);	// 좌클릭: 드래그 시작점 저장
		break;
	case EVENT_LBUTTONUP:
		Point ptNew = Point(x, y);				// 좌클릭 해제: 드래그 끝점 저장
		Mat roi_img = img(Rect(ptOld, ptNew));	// 시작점~끝점으로 ROI 추출
		roi_img += 100;							// ROI 영역 밝기 +100
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
