#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void DrawText(Mat& img) {
	putText(img, "Hello, Lenna", Point(120, 80), FONT_ITALIC, 1, Scalar(0, 255, 255), 2);
	// "Hello, Lenna" 문자열을 (120, 80) 위치에 이탤릭 폰트, 크기 1, 노란색(BGR: 0,255,255), 두께 2로 그리기
}

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawText(img);									// 텍스트 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
