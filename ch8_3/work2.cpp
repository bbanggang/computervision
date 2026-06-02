#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f cp(src.cols / 2.f, src.rows / 2.f);	// 원본영상 중심 (고정)
	double totalAngle = 0.0;			// 누적 회전각도

	imshow("src", src);
	imshow("dst", src);
	waitKey(1);

	while (true) {
		cout << "회전 각도 입력 (q: 종료): ";
		string input;
		cin >> input;

		if (input == "q" || input == "Q") break;

		totalAngle += stod(input);	// 각도 누적 (이전 각도에 더함)

		Mat M = getRotationMatrix2D(cp, totalAngle, 1);	// 누적 각도로 회전 행렬 생성

		Mat dst;
		// 항상 원본(src)에 누적 각도로 한 번만 적용 → 보간 1회로 왜곡 방지
		warpAffine(src, dst, M, src.size());

		imshow("dst", dst);
		waitKey(1);
	}

	return 0;
}
