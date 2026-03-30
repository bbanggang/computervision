#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	cout << "좌표 (50, 50)의 화소값(B, G, R) : " << img.at<Vec3b>(50, 50) << endl;		// (행 50, 열 50) 위치의 BGR 화소값 출력
	cout << "좌표 (100, 100)의 화소값(B, G, R) : " << img.at<Vec3b>(100, 100) << endl;	// (행 100, 열 100) 위치의 BGR 화소값 출력
	cout << "좌표 (150, 150)의 화소값(B, G, R) : " << img.at<Vec3b>(150, 150) << endl;	// (행 150, 열 150) 위치의 BGR 화소값 출력
	return 0;
}
