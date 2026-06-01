#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat M = Mat_<double>({ 2, 3 }, { 0.5, 0, 150, 0, 0.5, 100 });
	Mat dst;
	cout << M << endl;

	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}