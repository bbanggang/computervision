#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main(void) {
	String str;								// OpenCV의 String 타입 변수 선언 (cv::String)
	for (int i = 1; i <= 15; i += 2) {		// i = 1, 3, 5, 7, 9, 11, 13, 15 (홀수만 순회)
		str = format("실행결과%d.bmp", i);	// "실행결과1.bmp" ~ "실행결과15.bmp" 형식의 문자열 생성
		cout << str << endl;				// 생성된 파일명 문자열을 콘솔에 출력
	}
	return 0;
}
