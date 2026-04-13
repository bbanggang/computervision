#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void draw_circle(int pos, void* userdata);

int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("Lenna");
	createTrackbar("Trackbar", "Lenna", 0, 100, draw_circle, &img);
	// 0~100 범위의 트랙바 생성, 값 변경 시 draw_circle 콜백 호출, 이미지 주소를 userdata로 전달
	while (true) {
		imshow("Lenna", img);
		if (waitKey(10) == 'q') break;	// 'q': 종료
	}
	return 0;
}

void draw_circle(int pos, void* userdata) {
	int width_center = (*(Mat*)userdata).cols / 2;		// 이미지 너비의 중심 x 좌표 계산
	int height_center = (*(Mat*)userdata).rows / 2;		// 이미지 높이의 중심 y 좌표 계산
	Point center = Point(width_center, height_center);	// 이미지 중심점 설정
	cout << "트랙바 위치 : " << pos << endl;			// 현재 트랙바 위치 출력
	circle(*(Mat*)userdata, center, pos, Scalar(0, 255, 0), 5);
	// 이미지 중심에 반지름 pos, 초록색(BGR: 0,255,0), 두께 5인 원 그리기
}
