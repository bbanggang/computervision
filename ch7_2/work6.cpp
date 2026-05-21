#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat src, dst;
Point ptStart;
int sigma = 1;	// 트랙바 초기값 (표준편차)

void on_trackbar(int pos, void*)
{
	sigma = pos;	// 트랙바 위치를 전역 변수에 저장
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptStart = Point(x, y);	// 드래그 시작점 저장
		break;
	case EVENT_LBUTTONUP: {
		Point ptEnd(x, y);
		// 두 점으로 유효한 ROI 사각형 생성 (좌상단~우하단 순서 보정)
		Rect roi(
			Point(min(ptStart.x, ptEnd.x), min(ptStart.y, ptEnd.y)),
			Point(max(ptStart.x, ptEnd.x), max(ptStart.y, ptEnd.y))
		);
		if (roi.width > 0 && roi.height > 0 && sigma > 0) {
			GaussianBlur(dst(roi), dst(roi), Size(), sigma);	// 트랙바로 선택한 sigma로 블러 적용
			imshow("dst", dst);
		}
		break;
	}
	default:
		break;
	}
}

int main(void)
{
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }

	img.copyTo(src);
	img.copyTo(dst);

	namedWindow("dst");
	createTrackbar("sigma", "dst", &sigma, 9, on_trackbar);	// 0~9 범위 트랙바 생성
	setTrackbarPos("sigma", "dst", 1);						// 초기값 1로 설정
	setMouseCallback("dst", on_mouse);						// 마우스 콜백 등록

	imshow("dst", dst);
	waitKey();
	return 0;
}
