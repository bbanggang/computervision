#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	for (int i = 0; i < img.rows; i++) {				// 모든 행을 순회
		for (int j = 0; j < 3; j++) {					// 세로 3줄 (열 방향 1/4, 2/4, 3/4 위치)
			img.at<Vec3b>(i, img.cols * (j + 1) / 4) = Vec3b(255, 255, 255);	// 해당 열의 BGR 화소값을 흰색으로 설정
		}
	}
	for (int i = 0; i < img.cols; i++) {				// 모든 열을 순회
		for (int j = 0; j < 3; j++) {					// 가로 3줄 (행 방향 1/4, 2/4, 3/4 위치)
			img.at<Vec3b>(img.rows * (j + 1) / 4, i) = Vec3b(255, 255, 255);	// 해당 행의 BGR 화소값을 흰색으로 설정
		}
	}
	imshow("line", img);								// 격자선이 그려진 이미지 출력
	waitKey();											// 키 입력 대기 (창 유지)
	return 0;
}
