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
	for (int sigma = 1; sigma <= 5; sigma++) {
		int ksize = 8 * sigma + 1;	// ±4σ 범위를 포함하는 커널 크기
		int half = ksize / 2;
		Mat kernel2D(ksize, ksize, CV_32F);
		for (int y = -half; y <= half; y++) {
			for (int x = -half; x <= half; x++) {
				kernel2D.at<float>(y + half, x + half) =
					exp(-(x * x + y * y) / (2.f * sigma * sigma));
			}
		}
		kernel2D /= sum(kernel2D)[0];	// 커널 원소 합이 1이 되도록 정규화
		filter2D(src, dst, -1, kernel2D);
		String desc = format("Gaussian: sigma = %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}