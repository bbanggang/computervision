#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat img1(200, 600, CV_8UC3, Scalar(255, 255, 255));	// 200x600 크기의 흰색 3채널 이미지 생성
	int index = 0;										// 빨간 블록의 현재 위치 인덱스 (0: 좌, 1: 중, 2: 우)
	while (true) {
		img1.setTo(Scalar(255, 255, 255));				// 매 프레임마다 이미지 전체를 흰색으로 초기화
		Rect area(index * 200, 0, 200, 200);			// 인덱스에 따라 200x200 크기의 블록 영역 계산 (x = index * 200)
		img1(area).setTo(Scalar(0, 0, 255));			// 해당 영역을 빨간색으로 채우기
		imshow("img1", img1);							// 현재 프레임 출력
		if (waitKey(1000) == 'q') break;				// 1초 대기 후 'q' 입력 시 반복 종료
		index = (index + 1) % 3;						// 인덱스를 0→1→2→0 순으로 순환
	}
	return 0;
}
