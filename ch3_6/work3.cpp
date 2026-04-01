#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	int brightness;
	cout << "밝기 변화량을 입력 : ";
	cin >> brightness;								// 밝기 변화량 입력 (양수: 밝게, 음수: 어둡게)
	img += Scalar(brightness, brightness, brightness);	// BGR 각 채널에 변화량을 더해 밝기 조정 (255 초과 시 자동 포화 처리)
	imshow("image", img);							// 밝기가 조정된 이미지 출력
	waitKey();										// 키 입력 대기 (창 유지)
	return 0;
}
