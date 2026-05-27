#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("tekapo.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	// 3개 점(좌측상단, 우측상단, 우측하단)의 2배 확대 변환 관계 설정
	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);				// 좌측상단
	srcPts[1] = Point2f(src.cols - 1, 0);			// 우측상단
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);	// 우측하단

	dstPts[0] = Point2f(0, 0);					// 좌측상단 (고정)
	dstPts[1] = Point2f(2 * (src.cols - 1), 0);			// 우측상단 → x 2배
	dstPts[2] = Point2f(2 * (src.cols - 1), 2 * (src.rows - 1));	// 우측하단 → x, y 2배

	Mat M = getAffineTransform(srcPts, dstPts);	// 아핀 변환 행렬 계산 (2배 확대)
	cout << "M = " << endl << M << endl;

	// 결과영상 크기를 입력영상의 2배로 설정
	Size dsize(src.cols * 2, src.rows * 2);

	Mat dst;
	warpAffine(src, dst, M, dsize);	// dsize를 명시하여 2배 크기 결과영상 생성
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
