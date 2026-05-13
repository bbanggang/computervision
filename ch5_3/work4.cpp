//work3
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat MycalcGrayHist(const Mat& img);
Mat MygetGrayHistImage(const Mat& hist);

int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat hist = MycalcGrayHist(src);
	Mat hist_img = MygetGrayHistImage(hist);
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
			Point(i, h - 1 - cvRound(hist.at<float>(i, 0) * (h - 1) / histMax)),
			Scalar(0));	// 인접한 히스토그램 값을 선으로 연결하여 꺾은선 그래프로 표현
	}
	return imgHist;
}