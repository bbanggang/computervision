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
	cout << "M = " << endl << M << endl;

	float cx = (src.cols - 1) / 2.0f;
	float cy = (src.rows - 1) / 2.0f;

	Mat ptSrc(1, 1, CV_32FC3, Vec3f(cx, cy, 1.f));
	Mat ptDst;
	transform(ptSrc, ptDst, M);	

	Vec2f result = ptDst.at<Vec2f>(0, 0);
	cout << "원본 중앙점: (" << cx << ", " << cy << ")" << endl;
	cout << "변환된 좌표: (" << result[0] << ", " << result[1] << ")" << endl;

	Mat dst;
	warpAffine(src, dst, M, Size());
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}