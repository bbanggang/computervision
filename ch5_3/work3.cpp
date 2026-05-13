//work3
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img);
Mat MygetGrayHistImage(const Mat& hist);

int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat hist = calcGrayHist(src);
	Mat hist_img = MygetGrayHistImage(hist);
	imshow("hist_img", hist_img);
	waitKey();
	return 0;
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

Mat MygetGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	int h = 100;
	minMaxLoc(hist, 0, &histMax);
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 1; i < 256; i++) {
		line(imgHist,
			Point(i - 1, h - 1 - cvRound(hist.at<float>(i - 1, 0) * (h - 1) / histMax)),
			Point(i,     h - 1 - cvRound(hist.at<float>(i, 0) * (h - 1) / histMax)),
			Scalar(0));	// 인접한 히스토그램 값을 선으로 연결하여 꺾은선 그래프로 표현
	}
	return imgHist;
}