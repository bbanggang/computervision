#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img);
void print_image_prop(const Mat& img, const Mat& hist);

int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat hist = calcGrayHist(src);
	print_image_prop(src, hist);
	imshow("src", src);
	waitKey();
	return 0;
}

void print_image_prop(const Mat& img, const Mat& hist) {
	cout << "영상의 전체 픽셀수 : " << img.cols * img.rows << endl;
	double minVal, maxVal;
	minMaxLoc(img, &minVal, &maxVal);
	cout << "영상에서 픽셀값의 최소값 : " << minVal << endl;
	cout << "영상에서 픽셀값의 최댓값 : " << maxVal << endl;
	double histMax;
	Point histMaxPos;
	minMaxLoc(hist, 0, &histMax, 0 , &histMaxPos);
	cout << "빈도 수가 가장 많은 픽셀값과 빈도 수 : " << histMaxPos.y << ", " << histMax << endl;
	cout << "픽셀값 80의 빈도수 : " <<  hist.at<float>(80,0) <<  endl;
}

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);
	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	return hist;
}