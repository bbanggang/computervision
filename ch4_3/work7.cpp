#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void TimeCount(Mat& img) {
	int count = 0;							// 현재 카운트 값
	bool isCount = false;					// 카운트 진행 여부 플래그 (초기값: 정지)
	while (true) {
		putText(img, to_string(count), Point(100, 200), FONT_ITALIC, 5, Scalar(0), 2);
		// 현재 카운트 값을 (100, 200) 위치에 이탤릭 폰트, 크기 5, 검은색, 두께 2로 출력
		if (isCount) count++;				// 카운트 진행 중이면 1 증가
		imshow("src", img);					// 현재 프레임 출력
		img.setTo(255);						// 다음 프레임을 위해 이미지를 흰색으로 초기화 (텍스트 잔상 방지)
		int key = waitKey(1000);			// 1초 대기, 그 사이 키 입력 감지
		if (key == 's') isCount = true;		// 's' 키: 카운트 시작
		if (key == 'r') {
			count = 0;						// 'r' 키: 카운트 0으로 초기화
			waitKey(1000);					// 초기화 후 1초 추가 대기
		}
		if (key == 'q') break;				// 'q' 키: 종료
	}
}

int main(void) {
	Mat img(300, 300, CV_8UC1, 255);		// 300x300 크기의 흰색(255) 그레이스케일 이미지 생성
	if (img.empty()) {						// 이미지 생성 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	TimeCount(img);							// 타이머 실행
	return 0;
}
