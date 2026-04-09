#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void on_mouse(int event, int x, int y, int flags, void* userdata);
Mat img;

int main(void) {
	img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {				// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse);	// 마우스 콜백 등록 (전역 변수 img 사용)
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
	static Point ptOld, ptNew;			// 드래그 시작점과 끝점 저장 (static: 함수 호출 간 유지)
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);			// 좌클릭: 드래그 시작점 저장
		cout << "EVENT_LBUTTONDOWN: " << Point(x, y) << endl;
		break;
	case EVENT_LBUTTONUP:
		ptNew = Point(x, y);			// 좌클릭 해제: 드래그 끝점 저장
		cout << "EVENT_LBUTTONUP: " << Point(x, y) << endl;
		Mat roi_img = img(Rect(ptOld, ptNew));	// 시작점~끝점으로 ROI 추출
		imshow("roi_img", roi_img);		// ROI 이미지 출력
		waitKey(0);						// 키 입력 대기 (창 유지)
		break;
	}
}
