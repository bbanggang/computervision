#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat dst;
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		Mat kernel = Mat::ones(ksize, ksize, CV_32FC1) / (float)(ksize * ksize);
		filter2D(src, dst, -1, kernel);	
		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}