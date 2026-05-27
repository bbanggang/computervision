#include <opencv2/opencv.hpp>
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
	dstPts[1] = Point2f((src.cols - 1) / 2.0, 0);
	dstPts[2] = Point2f((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);
	Mat M = getAffineTransform(srcPts, dstPts);
	cout << M << endl;
	Mat dst;
	warpAffine(src, dst, M, Size());
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}