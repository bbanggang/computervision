#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("tekapo.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(0, 0);
	dstPts[1] = Point2f((src.cols - 1), 0);	
	dstPts[2] = Point2f((src.cols - 1) + 0.3f * (src.rows - 1), (src.rows - 1));
	// x 이동량을 rows 기준(0.3*(rows-1))으로 설정하여 m01 = 0.3 확보
	Mat M = getAffineTransform(srcPts, dstPts);
	cout << M << endl;

	Mat dst;
	warpAffine(src, dst, M, Size(src.cols + src.rows * 0.3, src.rows));
	// 캔버스 너비도 rows 기준으로 확장
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}	
