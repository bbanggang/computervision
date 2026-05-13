#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat MycalcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat hist = MycalcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);
	imshow("hist_img", hist_img);
	waitKey();
	return 0;
}

Mat MycalcGrayHist(const Mat& img)
{
	Mat hist(256, 1, CV_32FC1, Scalar(0));	// 256x1 float Mat, 0으로 초기화
	for (int j = 0; j < img.rows; j++) {
		for (int i = 0; i < img.cols; i++) {
			hist.at<float>(img.at<uchar>(j, i), 0)++;	// 해당 픽셀값의 빈도 증가
		}
	}
	return hist;
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	minMaxLoc(hist, 0, &histMax);
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist,
			Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)),
			Scalar(0));
	}
	return imgHist;
}