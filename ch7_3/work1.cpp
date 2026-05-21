#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) return -1;

	float weights[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };
	Mat mask = Mat(3, 3, CV_32F, weights);	// 8방향 샤프닝 커널

	imshow("src", src);

	Mat result;
	src.copyTo(result);

	for (int i = 1; i <= 5; i++) {
		filter2D(result, result, -1, mask);	// 이전 결과에 샤프닝을 반복 적용
		String desc = format("Sharpening x%d", i);
		Mat display;
		result.copyTo(display);
		putText(display, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("sharpen", display);
		waitKey(0);
	}
	return 0;
}
