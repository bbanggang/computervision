#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace cv;
int main() {
	vector<Mat> vec;							// 이미지를 저장할 Mat 벡터 선언
	for (int i = 0; i < 3; i++) {
		string filename = "test" + to_string(i + 1) + ".jpg";	// "test1.jpg", "test2.jpg", "test3.jpg" 파일명 생성
		Mat tmp = imread(filename, IMREAD_COLOR);				// 컬러 모드로 이미지 읽기
		vec.push_back(tmp);										// 벡터에 이미지 추가
	}
	while (true) {												// 무한 반복 
		for (auto it = vec.begin(); it != vec.end(); it++) {	// 벡터의 이미지를 순서대로 순회
			imshow("test", *it);								// 현재 이미지를 "test" 창에 출력
			int ch = waitKey(1000);								// 1초 대기, 그 사이 키 입력 감지
			if (ch == 'q') return -1;							// 'q' 키 입력 시 프로그램 종료
		}
	}
	return 0;
}
