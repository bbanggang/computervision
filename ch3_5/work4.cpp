#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat img(400, 400, CV_8UC1, 255);			// 400x400 크기의 흰색(255) 그레이스케일 이미지 생성
	for (int x = 0; x < img.cols; x++) {			// x좌표 0~399 순회
		int y = (double)1 / 400 * x * x;		// y = x² / 400 으로 포물선의 y좌표 계산 (이미지 범위 내 스케일 조정)
		img.at<uchar>(y, x) = 0;				// (y, x) 위치의 화소를 검은색(0)으로 설정
	}
	imshow("gragh", img);						// 포물선이 그려진 이미지 출력
	waitKey();									// 키 입력 대기 
	return 0;
}
