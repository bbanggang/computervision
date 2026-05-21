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
	Mat dst;
	int ksize[3] = { 3, 10 ,30 };
	for (int i = 0; i < 3;i++) {
		auto startTime = std::chrono::steady_clock::now(); // 시작시간 저장
		blur(src, dst, Size(ksize[i], ksize[i]));
		auto endTime = std::chrono::steady_clock::now(); // 종료시간 저장
		float totalTime = std::chrono::duration<float, std::milli>(endTime - startTime).count();
		String desc = format("Mean: %dx%d", ksize[i], ksize[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		cout << totalTime << "ms" << endl; // 시간차이(msec)출력
		waitKey();
	}
	return 0;
}