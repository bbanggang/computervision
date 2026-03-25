#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Rect getSafeRect() {
	int x, y, width, height;
	Point pt1; Size sz1;
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		cout << "관심영역의 좌측상단좌표(x, y) : ";
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
		cout << "관심영역의 폭, 높이(width, height) : ";
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

int getSafeChange() {
	int pixel_change;
	cout << "픽셀변화량 : ";
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		if (cin >> pixel_change) {					// 숫자 입력 성공 시
			return pixel_change;					// 입력된 변화량 반환
		}
		else
		{
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	Mat roi = img(getSafeRect());					// 사용자가 입력한 영역을 ROI로 설정 (원본 이미지와 메모리 공유)
	roi.convertTo(roi, -1, 1, getSafeChange());		// ROI 픽셀값에 변화량을 더함 (-1: 원본 타입 유지, 1: 스케일 유지, 마지막 인자: 밝기 변화량)
	imshow("img", img);								// 변경된 원본 이미지 출력 (ROI가 원본과 메모리를 공유하므로 원본에 반영됨)
	waitKey();										// 키 입력 대기 (창 유지)
	return 0;
}
