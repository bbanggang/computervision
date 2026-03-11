#include "opencv2/opencv.hpp"
#include <iostream>	
using namespace std;
using namespace cv;

int main() {
	int count = 0;
	Mat img;
	img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed!" << endl;		// 에러 메시지 출력
		return -1;									// 프로그램 종료
	}
	Mat bright_img = img + 100;						// 픽셀 값에 100을 더해 밝기 증가 
	imshow("gray image", img);						// 원본 그레이스케일 이미지 출력
	imshow("bright image", bright_img);				// 밝기 증가된 이미지 출력

	imwrite("bright.jpg", bright_img);				// 밝기 증가된 이미지를 파일로 저장
	waitKey();										// 키 입력 대기 
	return 0;
}
