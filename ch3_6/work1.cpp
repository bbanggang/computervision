#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

string getDepthStr(int depth) {
	switch (depth) {
	case CV_8U:  return "CV_8U";	// 부호 없는 8비트 정수
	case CV_8S:  return "CV_8S";	// 부호 있는 8비트 정수
	case CV_16U: return "CV_16U";	// 부호 없는 16비트 정수
	case CV_16S: return "CV_16S";	// 부호 있는 16비트 정수
	case CV_32S: return "CV_32S";	// 부호 있는 32비트 정수
	case CV_32F: return "CV_32F";	// 32비트 부동소수점
	case CV_64F: return "CV_64F";	// 64비트 부동소수점
	default:     return "Unknown";	// 알 수 없는 타입
	}
}

int main(void) {
	Mat img = imread("photo.jpg", IMREAD_COLOR);	// photo.jpg를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed." << endl;
		return -1;
	}
	cout << "행의 수 : " << img.rows << endl;					// 이미지의 세로 픽셀 수 출력
	cout << "열의 수 : " << img.cols << endl;					// 이미지의 가로 픽셀 수 출력
	cout << "채널 수 : " << img.channels() << endl;			// 채널 수 출력 (컬러: 3, 그레이스케일: 1)
	cout << "Type: " << getDepthStr(img.depth()) << "C" << img.channels() << endl;	// depth 문자열과 채널 수를 조합하여 타입 출력 (예: CV_8UC3)
	return 0;
}
