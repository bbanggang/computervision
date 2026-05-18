#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat src;	// 콜백 함수에서 접근할 수 있도록 전역 변수로 선언

// 마우스 이벤트 콜백 함수
// event: 마우스 이벤트 종류, (x, y): 클릭 좌표, flags: 보조 키 상태
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	Mat dst;

	// 더블 클릭을 단일 클릭보다 먼저 검사 — 더블 클릭 시 LBUTTONDOWN도 함께 발생하므로
	// 순서를 바꾸면 단일 클릭 결과가 먼저 출력된 뒤 덮어씌워지는 문제가 생김
	if (event == EVENT_LBUTTONDBLCLK) {
		// 왼쪽 버튼 더블 클릭: 소벨 x방향 에지 검출 (과제 3)
		// 좌우 밝기 차이를 계산하여 수직 방향 경계선을 강조
		float data3[] = { -1.0, 0, 1.0,	// 좌(-) → 우(+) 기울기
		                  -2.0, 0, 2.0,	// 중앙 행에 가중치 2 부여
		                  -1.0, 0, 1.0 };
		Mat kernel3(3, 3, CV_32FC1, data3);
		filter2D(src, dst, -1, kernel3, Point(-1, -1), 0);	// 소벨 필터 적용
		imshow("dst", dst);
	}
	else if (event == EVENT_LBUTTONDOWN) {
		// 왼쪽 버튼 단일 클릭: 평균 블러링 (과제 1)
		// 3×3 이웃 픽셀의 평균으로 대체하여 영상을 부드럽게 만듦
		float data1[] = { 1.0/9.0, 1.0/9.0, 1.0/9.0,	// 모든 계수가 동일(1/9)하여
		                  1.0/9.0, 1.0/9.0, 1.0/9.0,	// 9개 픽셀의 단순 평균값으로
		                  1.0/9.0, 1.0/9.0, 1.0/9.0 };	// 중심 픽셀을 교체
		Mat kernel1(3, 3, CV_32FC1, data1);
		filter2D(src, dst, -1, kernel1, Point(-1, -1), 0);	// 평균 블러링 필터 적용
		imshow("dst", dst);
	}
	else if (event == EVENT_RBUTTONDOWN) {
		// 오른쪽 버튼 클릭: 샤프닝 (과제 2)
		// 중심 픽셀을 9배 강조하고 주변 8개 픽셀을 빼서 경계를 선명하게 만듦
		float data2[] = { -1.0, -1.0, -1.0,	// 주변 계수 -1: 이웃 픽셀 억제
		                  -1.0,  9.0, -1.0,	// 중심 계수  9: 중심 픽셀 강조
		                  -1.0, -1.0, -1.0 };
		Mat kernel2(3, 3, CV_32FC1, data2);
		filter2D(src, dst, -1, kernel2, Point(-1, -1), 0);	// 샤프닝 필터 적용
		imshow("dst", dst);
	}
}

int main(void)
{
	src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	namedWindow("src");
	namedWindow("dst");
	setMouseCallback("src", onMouse);	// src 창에 마우스 콜백 등록

	imshow("src", src);	// 원본 영상 출력
	imshow("dst", src);	// 초기 dst 창에는 원본 영상 표시
	waitKey();
	return 0;
}
