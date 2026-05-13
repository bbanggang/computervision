#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

int main(void)
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);
	cout << "Gmin:" << gmin << endl;
	cout << "Gmax:" << gmax << endl;
	Mat dst(src.size(), src.type());
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>((src.at<uchar>(j, i) - gmin) * 255 / (gmax - gmin));
		}
	}

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));
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