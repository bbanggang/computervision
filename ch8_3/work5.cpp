#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("eastsea.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	int cols = src.cols;
	int rows = src.rows;

	// warpAffine용 반전 행렬 사전 정의
	// a키: 좌우 반전 → x' = (cols-1)-x, y' = y
	Mat M_a = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, 1, 0);
	// b키: 상하 반전 → x' = x, y' = (rows-1)-y
	Mat M_b = (Mat_<double>(2, 3) << 1, 0, 0, 0, -1, rows - 1);
	// c키: 좌우+상하 반전 → x' = (cols-1)-x, y' = (rows-1)-y
	Mat M_c = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, -1, rows - 1);

	imshow("dst", src);

	while (true) {
		int key = waitKey(0);

		Mat M, dst;
		String desc;

		if (key == 'a') {
			M = M_a;			// a키: 좌우 대칭
			desc = "Horizontal flip (a)";
		} else if (key == 'b') {
			M = M_b;			// b키: 상하 대칭
			desc = "Vertical flip (b)";
		} else if (key == 'c') {
			M = M_c;			// c키: 좌우+상하 대칭
			desc = "Both flip (c)";
		} else if (key == 'q') {
			break;				// q키: 종료
		} else {
			continue;			// 그 외 키 무시
		}

		warpAffine(src, dst, M, src.size());	// 반전 행렬 적용
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255, 0, 0), 1, LINE_AA);
		imshow("dst", dst);
	}

	return 0;
}
