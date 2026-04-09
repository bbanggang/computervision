#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


void DrawText(Mat& img) {
	putText(img, "Hello, Lenna", Point(120, 80), FONT_ITALIC, 1, Scalar(0, 255, 255), 2);
	// "Hello, Lenna" 문자열을 (120, 80) 위치에 이탤릭 폰트, 크기 1, 노란색(BGR: 0,255,255), 두께 2로 그리기
}

void DrawCircle(Mat& img) {
	circle(img, Point(280, 280), 160, Scalar(0, 0, 255), 2);
	// 중심 (280, 280), 반지름 160, 빨간색(BGR: 0,0,255), 두께 2인 원 그리기
}

void DrawLine(Mat& img) {
	line(img, Point(100, 430),Point(440,430), Scalar(255, 255, 255), 2);
	// (100, 430) ~ (440, 430) 사이에 흰색(BGR: 255,255,255), 두께 2인 가로선 그리기
}

int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	int key;
	while (true) {
		imshow("img", img);				// 현재 이미지 출력
		key = waitKey();				// 키 입력 대기
		if (key == 'q') break;			// 'q': 종료
		else if (key == 'l') DrawLine(img);		// 'l': 가로선 그리기
		else if (key == 'c') DrawCircle(img);	// 'c': 빨간색 원 그리기
		else if (key == 't') DrawText(img);		// 't': 텍스트 그리기
		else {
			cout << "잘못된 입력입니다. l(line), c(circle), t(text), q(quit)" << endl;
			continue;
		}
	}
	destroyAllWindows();				// 모든 창 닫기
	return 0;
}
