#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat	img1 = imread("dog.bmp", IMREAD_COLOR);		// dog.bmp를 컬러 모드로 읽기
	if (img1.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed!" << endl;
		return -1;
	}
	Mat img2 = img1(Rect(100, 40, 75, 75)).setTo(Scalar(255, 0, 0));	// 좌측 상단 (100, 40), 크기 75x75 영역을 파란색으로 채우기
	// setTo()는 원본 이미지와 메모리를 공유하므로 img1에도 반영됨
	imshow("img1", img1);							// 파란색 영역이 적용된 이미지 출력
	waitKey();										// 키 입력 대기 (창 유지)
	return 0;
}
