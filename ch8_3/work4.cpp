#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("eastsea.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);

	int cols = src.cols;
	int rows = src.rows;

	// flip() 대신 warpAffine()으로 동일한 반전 효과 구현
	// flipCode=1: 좌우 반전 → x' = (cols-1)-x, y' = y
	Mat M1 = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, 1, 0);
	// flipCode=0: 상하 반전 → x' = x, y' = (rows-1)-y
	Mat M2 = (Mat_<double>(2, 3) << 1, 0, 0, 0, -1, rows - 1);
	// flipCode=-1: 좌우+상하 반전 → x' = (cols-1)-x, y' = (rows-1)-y
	Mat M3 = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, -1, rows - 1);

	Mat Ms[] = { M1, M2, M3 };
	int flipCode[] = { 1, 0, -1 };

	Mat dst;
	for (int i = 0; i < 3; i++) {
		warpAffine(src, dst, Ms[i], src.size());	// 반전 행렬 적용
		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255, 0, 0), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	return 0;
}