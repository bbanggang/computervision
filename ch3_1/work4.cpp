#include "opencv2/opencv.hpp"
#include <iostream>	
using namespace std;
using namespace cv;

Point getSafePoint(string name) {
	int x, y;
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		cout << name << "의 x,y 좌표를 입력 : ";
		if (cin >> x >> y) {						// 숫자 두 개 입력 성공 시
			return Point(x, y);						// Point 객체 생성 후 반환
		}
		else {
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}

Rect getSafeRect() {
	int x, y, width, height;
	Point pt1; Size sz1;
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		cout << "사각형의 좌측 상단의 좌표를 입력하시오(x,y) : ";
		if (cin >> x >> y) {						// 숫자 두 개 입력 성공 시
			if (x >= 0 && y >= 0) {					// 좌표가 양수인지 확인
				pt1 = Point(x, y);					// 좌측 상단 좌표 저장
			}
			else {
				cout << "오류 : 양수의 좌표를 입력하시오. 처음부터 다시 입력하세요." << endl;
				continue;							// 처음부터 다시 입력
			}
		}
		else
		{
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다. 처음부터 다시 입력하세요." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
			continue;
		}
		cout << "사각형의 폭, 높이를 입력하시오(width, height) : ";
		if (cin >> width >> height) {				// 숫자 두 개 입력 성공 시
			if (width >= 0 && height >= 0) {		// 폭과 높이가 양수인지 확인
				sz1 = Size(width, height);			// 크기 저장
				return Rect(pt1, sz1);				// Rect 객체 생성 후 반환
			}
			else {
				cout << "오류 : 양수의 값을 입력하시오. 처음부터 다시 입력하세요." << endl;
				continue;							// 처음부터 다시 입력
			}
		}
		else
		{
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다. 처음부터 다시 입력하세요." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}

int main(void) {
	Rect r = getSafeRect();						// 사각형 정보 입력
	Point pt = getSafePoint("점 P");			// 점 P의 좌표 입력

	if (pt.inside(r)) {							// 점이 사각형 내부에 있는지 확인
		cout << "점 P는 사각형 안에 있다." << endl;
	}
	else {
		cout << "점 P는 사각형 밖에 있다." << endl;
	}
	return 0;
}
