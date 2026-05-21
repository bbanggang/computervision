#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	waitKey(1);	// 창 초기화를 루프 전에 완료하여 첫 번째 측정값 왜곡 방지
	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		auto startTime = chrono::steady_clock::now();
		GaussianBlur(src, dst, Size(), (double)sigma);	// 실행 시간 측정 대상
		auto endTime = chrono::steady_clock::now();
		float totalTime = chrono::duration<float, milli>(endTime - startTime).count();
		cout << "sigma = " << sigma << ": " << totalTime << "ms" << endl;
		String desc = format("Gaussian: sigma = %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}