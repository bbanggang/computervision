#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void select_shape(int pos, void* userdata);
void draw_shape(int event, int x, int y, int flags, void* userdata);
int shape_pos;	// 트랙바로 선택한 도형 종류 (0: 파란색, 1: 초록색, 2: 빨간색, 3: 흰색 채우기)

int main(void) {
	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));	// 500x500 크기의 흰색 3채널 이미지 생성
	namedWindow("src");
	setMouseCallback("src", draw_shape, &img);			// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	createTrackbar("Trackbar", "src", 0, 3, select_shape);
	// 0~3 범위의 트랙바 생성, 값 변경 시 select_shape 콜백 호출
	while (true) {
		imshow("src", img);
		if (waitKey(10) == 'q') break;	// 'q': 종료
	}
	return 0;
}

void select_shape(int pos, void* userdata) {
	shape_pos = pos;	// 트랙바 위치를 전역 변수에 저장하여 도형 종류 선택
}

void draw_shape(int event, int x, int y, int flags, void* userdata) {
	static Point ptOld;		// 드래그 시작점 (static: 함수 호출 간 유지)
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);	// 좌클릭: 드래그 시작점 저장
	case EVENT_LBUTTONUP:
		Point ptNew = Point(x, y);	// 좌클릭 해제: 드래그 끝점 저장
		if (shape_pos == 0) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(255, 0, 0), 1);
		// shape_pos == 0: 파란색(BGR: 255,0,0) 테두리 사각형 그리기
		else if(shape_pos == 1) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(0, 255, 0), 1);
		// shape_pos == 1: 초록색(BGR: 0,255,0) 테두리 사각형 그리기
		else if(shape_pos == 2) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(0, 0, 255), 1);
		// shape_pos == 2: 빨간색(BGR: 0,0,255) 테두리 사각형 그리기
		else if(shape_pos == 3) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(255, 255, 255), -1);
		// shape_pos == 3: 흰색(BGR: 255,255,255)으로 채운 사각형 그리기 (지우개 효과)
	}
}
