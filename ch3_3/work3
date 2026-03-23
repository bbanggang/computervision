#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

Scalar getSafeBGR() {
	Scalar BGR;
	string colors[3] = { "B", "G", "R" };				// 입력 안내에 사용할 채널 이름 배열
	int temp;
	for (int i = 0; i < 3; i++) {						// B, G, R 순서로 각 채널 값 입력
		while (true) {									// 유효한 입력이 들어올 때까지 반복
			cout << colors[i] << "값을 입력하라: ";
			if (cin >> temp) {							// 숫자 입력 성공 시
				if (temp >= 0 && temp <= 255) {			// 0~255 범위 확인
					BGR[i] = temp;						// 해당 채널에 값 저장
					break;								// 다음 채널로 이동
				}
				else
				{
					cout << "오류 : (0~255) 사이의 정수값을 입력하세요." << endl;
					continue;
				}
			}
			else {
				cout << "오류 : 숫자가 아닌 값이 입력되었습니다." << endl;
				cin.clear();							// 오류 상태 플래그 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
				continue;
			}
		}
	}
	return BGR;											// 완성된 BGR 색상값 반환
}
int main(void) {
	Scalar color = getSafeBGR();				// BGR 색상값 입력
	Mat tmp = Mat(300, 400, CV_8UC3);			// 300x400 크기의 3채널 컬러 이미지 생성 (초기값 없음)
	tmp.setTo(color);							// 이미지 전체를 입력받은 색상으로 채우기

	imshow("color", tmp);						// 색상 이미지 출력
	waitKey();									// 키 입력 대기 (창 유지)
	return 0;
}
