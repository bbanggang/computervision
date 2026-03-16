#include "opencv2/opencv.hpp"
#include <iostream>
#include <limits>
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

int main(void) {
	Point pt1, pt2;
	pt1 = getSafePoint("첫번째 점");			// 첫번째 점 좌표 입력
	pt2 = getSafePoint("두번째 점");			// 두번째 점 좌표 입력
	cout << "pt1: " << pt1 << endl;				// pt1 좌표 출력
	cout << "pt2: " << pt2 << endl;				// pt2 좌표 출력
	double dist = norm(pt1 - pt2);				// 두 점의 차 벡터의 노름(norm)으로 유클리드 거리 계산
	cout << "두점사이의 거리:" << dist << endl;
	return 0;
}
