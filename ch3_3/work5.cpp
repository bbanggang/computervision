#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace cv;

int main() {
	int grayscale_size = 0;								// 현재 밝기 값 (0~255)
	bool flag = 1;										// true: 밝기 증가 방향, false: 밝기 감소 방향
	Mat image = Mat(400, 400, CV_8UC1, Scalar(grayscale_size));	// 400x400 크기의 1채널(그레이스케일) 이미지 생성, 초기값 0(검정)
	while (true) {
		if (flag) {										// 밝기 증가 구간
			imshow("image", image);						// 현재 밝기의 이미지 출력
			grayscale_size++;							// 밝기 1 증가
			cout << grayscale_size << endl;				// 현재 밝기 값 콘솔 출력
			if (grayscale_size == 255) flag = 0;		// 최대 밝기(255) 도달 시 감소 방향으로 전환
			image.setTo(grayscale_size);				// 이미지 전체를 새 밝기 값으로 갱신
		}
		else {											// 밝기 감소 구간
			imshow("image", image);						// 현재 밝기의 이미지 출력
			grayscale_size--;							// 밝기 1 감소
			cout << grayscale_size << endl;				// 현재 밝기 값 콘솔 출력
			if (grayscale_size == 0) flag = 1;			// 최소 밝기(0) 도달 시 증가 방향으로 전환
			image.setTo(grayscale_size);				// 이미지 전체를 새 밝기 값으로 갱신
		}
		int ch = waitKey(5);							// 5ms 대기, 그 사이 키 입력 감지
		if (ch == 'Q') return -1;						// 'Q' 키 입력 시 프로그램 종료
	}
	return 0;
}
