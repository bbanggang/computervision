#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);

	Mat src_f;
	src.convertTo(src_f, CV_32F);	// 큰 alpha 값 연산을 위해 float으로 변환

	Mat blurred_f;
	blur(src_f, blurred_f, Size(3, 3));	// 3x3 평균값 필터 적용

	for (int alpha = 10; alpha <= 50; alpha += 10) {
		Mat dst_f = (1.f + alpha) * src_f - alpha * blurred_f;
		// 언샤프 마스킹: dst = (1+α)*src - α*blurred
		Mat dst;
		dst_f.convertTo(dst, CV_8U);	// float 결과를 0~255로 클리핑하여 uchar 변환
		String desc = format("Mean blur, alpha: %d", alpha);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}