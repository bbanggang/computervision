#include "opencv2/opencv.hpp"
#include <iostream>
#include<limits>
using namespace std;
using namespace cv;

Size getSafeSize(string name) {
	int width, height;
	while (true) {										// 유효한 입력이 들어올 때까지 반복
		cout << name << "사각형의 폭, 높이 입력 : ";
		if (cin >> width >> height) {					// 숫자 두 개 입력 성공 시
			if (width >= 0 && height >= 0) {			// 폭과 높이가 양수인지 확인
				return Size(width, height);				// Size 객체 생성 후 반환
			}
			else {
				cout << "오류 : 사각형의 크기는 음수가 될 수 없습니다." << endl;
			}
		}
		else {
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다. 다시 입력하세요." << endl;
			cin.clear();								// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}

int main(void) {
	Size s1 = getSafeSize("첫번째");		// 첫번째 사각형 크기 입력
	Size s2 = getSafeSize("두번째");		// 두번째 사각형 크기 입력
	cout << "s1 : " << s1 << endl;			// s1의 폭, 높이 출력
	cout << "s2 : " << s2 << endl;			// s2의 폭, 높이 출력
	cout << "s1의 면적 " << s1.area() << endl;		// s1의 면적(width * height) 출력
	cout << "s2의 면적 " << s2.area() << endl;;		// s2의 면적(width * height) 출력
	return 0;
}
