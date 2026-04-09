#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void on_mouse(int event, int x, int y, int flags, void* userdata);

int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse, &img);	// 이미지 주소를 userdata로 전달하며 마우스 콜백 등록
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
	if (event == EVENT_LBUTTONDOWN) {
		Mat& img = *static_cast<Mat*>(userdata);	// 강제 형변환인 C_Style보다 static_cast가 권장됨
		cout << "좌표: " << Point(x, y) << ", 화소값(B, G, R): " << img.at<Vec3b>(y, x) << endl;
		// 클릭한 좌표의 BGR 화소값 출력
	}
}
