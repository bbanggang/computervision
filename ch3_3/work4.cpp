#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace cv;
int main() {
	vector<Mat> vec;
	Scalar colors[3] = { Scalar(255, 0, 0), Scalar(0, 255, 0) , Scalar(0, 0, 255) };	// BGR 순서로 파랑, 초록, 빨강 색상 정의
	string labels[3] = { "Blue", "Green", "Red" };										// 각 색상의 이름 정의 (현재 코드에서는 미사용)
	for (int i = 0; i < 3; i++) {
		Mat tmp = Mat(300, 400, CV_8UC3, colors[i]);	// 300x400 크기의 3채널 이미지를 단색으로 생성
		vec.push_back(tmp);								// 벡터에 이미지 추가
	}
	while (true) {										// 무한 반복 (슬라이드쇼)
		for (auto it = vec.begin(); it != vec.end(); it++) {	// 벡터의 이미지를 순서대로 순회
			imshow("test", *it);						// 현재 이미지를 "test" 창에 출력
			int ch = waitKey(1000);						// 1초 대기, 그 사이 키 입력 감지
			if (ch == 'q') return -1;					// 'q' 키 입력 시 프로그램 종료
		}
	}
	return 0;
}
