#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat src_f, blurred_f;
int alpha = 0;	// 트랙바 초기값

void on_trackbar(int pos, void*)
{
	Mat dst_f = (1.f + pos) * src_f - pos * blurred_f;
	// 언샤프 마스킹: dst = (1+α)*src - α*blurred
	Mat dst;
	dst_f.convertTo(dst, CV_8U);	// float 결과를 0~255로 클리핑하여 uchar 변환
	String desc = format("Mean blur, alpha: %d", pos);
	putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
		Scalar(255), 1, LINE_AA);
	imshow("dst", dst);
}

int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	src.convertTo(src_f, CV_32F);		// 큰 alpha 값 연산을 위해 float으로 변환
	blur(src_f, blurred_f, Size(3, 3));	// 3x3 평균값 필터 적용 (트랙바 변경 시마다 재계산 불필요)

	namedWindow("dst");
	createTrackbar("alpha", "dst", &alpha, 50, on_trackbar);	// 0~50 범위 트랙바 생성

	imshow("src", src);
	on_trackbar(0, nullptr);	// 초기 화면 출력 (alpha=0)
	waitKey();
	return 0;
}
