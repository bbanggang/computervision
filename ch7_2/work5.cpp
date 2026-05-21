#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat src, dst;
Point ptStart;

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
		if (roi.width > 0 && roi.height > 0) {
			GaussianBlur(dst(roi), dst(roi), Size(), 5);	// ROI 영역에만 가우시안 블러 적용 (sigma=5)
			dst.copyTo(src);
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
	setMouseCallback("dst", on_mouse);	// 마우스 콜백 등록

	imshow("dst", dst);
	waitKey();
	return 0;
}