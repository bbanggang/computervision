#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환

	switch (event) {
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {		// 좌클릭을 누른 채 이동 중일 때만 처리
			vector<Point> pts = {
				Point(x, y), Point(x + 1, y), Point(x - 1, y),
				Point(x, y + 1), Point(x, y - 1)
			};	// 현재 좌표와 상하좌우 인접 4개 좌표로 붓 영역 구성 (십자 모양)
			for (auto& pt : pts) {
				img.at<uchar>(pt) = saturate_cast<uchar>(img.at<uchar>(pt) + 100);
				// 각 좌표의 밝기 +100 (saturate_cast로 255 초과 방지)
			}
		}
		break;
	default:
		break;
	}
}

int main(void) {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	namedWindow("dst");
	setMouseCallback("dst", on_mouse, &src);	// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	while (true) {
		imshow("dst", src);
		if (waitKey(100) == 'q') break;		// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
