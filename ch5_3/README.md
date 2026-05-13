# ch 5-3 영상의 밝기와 명암비 조절

## 과제 1

그레이스케일 이미지의 전체 픽셀 수, 최솟값·최댓값, 최빈 픽셀값, 특정 픽셀값의 빈도를 출력하는 프로그램이다.

---

### calcGrayHist()

그레이스케일 이미지의 히스토그램(256개 빈)을 계산하여 반환한다.

```cpp
Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);	// 그레이스케일 이미지인지 확인
	Mat hist;
	int channels[] = { 0 };			// 단일 채널(그레이)
	int dims = 1;						// 1차원 히스토그램
	const int histSize[] = { 256 };		// 0~255 총 256개 빈
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	return hist;
}
```

---

### print_image_prop()

이미지와 히스토그램을 받아 픽셀 통계 정보를 콘솔에 출력한다.

```cpp
void print_image_prop(const Mat& img, const Mat& hist) {
	cout << "영상의 전체 픽셀수 : " << img.cols * img.rows << endl;	// 전체 픽셀 수 출력
	double minVal, maxVal;
	minMaxLoc(img, &minVal, &maxVal);									// 픽셀 최솟값·최댓값 탐색
	cout << "영상에서 픽셀값의 최소값 : " << minVal << endl;
	cout << "영상에서 픽셀값의 최댓값 : " << maxVal << endl;
	double histMax;
	Point histMaxPos;
	minMaxLoc(hist, 0, &histMax, 0, &histMaxPos);						// 히스토그램 최댓값과 위치 탐색
	cout << "빈도 수가 가장 많은 픽셀값과 빈도 수 : " << histMaxPos.y << ", " << histMax << endl;
	cout << "픽셀값 80의 빈도수 : " << hist.at<float>(80, 0) << endl;	// 픽셀값 80의 빈도 출력
}
```

---

### main()

lenna.bmp를 그레이스케일로 읽고 히스토그램을 계산한 뒤 이미지 속성을 출력한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat hist = calcGrayHist(src);		// 히스토그램 계산
	print_image_prop(src, hist);		// 픽셀 통계 정보 콘솔 출력
	imshow("src", src);
	waitKey();
	return 0;
}
```

### 실행 결과
![image1](https://github.com/user-attachments/assets/728d4d3d-a970-4d5d-9156-65bbf38d9bdb)


## 과제 2

픽셀 단위 반복문으로 히스토그램을 직접 계산하고 막대 그래프로 시각화하는 프로그램이다.

---

### MycalcGrayHist()

픽셀 단위 이중 반복문으로 히스토그램을 직접 계산하여 `CV_32FC1` 타입 `Mat`으로 반환한다.

```cpp
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
```

---

### getGrayHistImage()

히스토그램 데이터를 최댓값 기준으로 정규화하여 막대 그래프 이미지로 변환한다.

```cpp
Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	minMaxLoc(hist, 0, &histMax);				// 히스토그램 최댓값 탐색
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));	// 흰 배경 이미지 생성
	for (int i = 0; i < 256; i++) {
		line(imgHist,
			Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)),
			Scalar(0));	// 각 빈 값을 최댓값 기준으로 정규화하여 막대 그리기
	}
	return imgHist;
}
```

---

### main()

lenna.bmp를 그레이스케일로 읽고 직접 계산한 히스토그램을 막대 그래프로 출력한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);						// 원본 이미지 출력
	Mat hist = MycalcGrayHist(src);			// 픽셀 단위 반복문으로 히스토그램 계산
	Mat hist_img = getGrayHistImage(hist);	// 히스토그램 막대 그래프 이미지 생성
	imshow("hist_img", hist_img);			// 히스토그램 이미지 출력
	waitKey();
	return 0;
}
```

### 실행 결과
![image2](https://github.com/user-attachments/assets/7f4112ee-7b7a-4d40-8f7c-a896fe2fd6e2)



## 과제 3

`calcHist()`로 히스토그램을 계산하고 인접 점을 연결한 꺾은선 그래프로 시각화하는 프로그램이다.

---

### calcGrayHist()

그레이스케일 이미지의 히스토그램(256개 빈)을 계산하여 반환한다.

```cpp
Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);	// 그레이스케일 이미지인지 확인
	Mat hist;
	int channels[] = { 0 };			// 단일 채널(그레이)
	int dims = 1;						// 1차원 히스토그램
	const int histSize[] = { 256 };		// 0~255 총 256개 빈
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	return hist;
}
```

---

### MygetGrayHistImage()

인접한 히스토그램 값을 선으로 연결하여 꺾은선 그래프 이미지로 변환한다.

```cpp
Mat MygetGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	int h = 100;
	minMaxLoc(hist, 0, &histMax);				// 히스토그램 최댓값 탐색
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));	// 흰 배경 이미지 생성
	for (int i = 1; i < 256; i++) {
		line(imgHist,
			Point(i - 1, h - 1 - cvRound(hist.at<float>(i - 1, 0) * (h - 1) / histMax)),
			Point(i,     h - 1 - cvRound(hist.at<float>(i, 0) * (h - 1) / histMax)),
			Scalar(0));	// 인접한 히스토그램 값을 선으로 연결하여 꺾은선 그래프로 표현
	}
	return imgHist;
}
```

---

### main()

lenna.bmp를 그레이스케일로 읽고 히스토그램을 꺾은선 그래프로 출력한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);						// 원본 이미지 출력
	Mat hist = calcGrayHist(src);			// calcHist()로 히스토그램 계산
	Mat hist_img = MygetGrayHistImage(hist);	// 꺾은선 그래프 이미지 생성
	imshow("hist_img", hist_img);			// 히스토그램 이미지 출력
	waitKey();
	return 0;
}
```

### 실행 결과
![image3](https://github.com/user-attachments/assets/ce915567-f175-40ad-aaf4-e22c52cd8def)



## 과제 4

픽셀 단위 반복문으로 히스토그램을 직접 계산하고 꺾은선 그래프로 시각화하는 프로그램이다.

---

### MycalcGrayHist()

픽셀 단위 이중 반복문으로 히스토그램을 직접 계산하여 `CV_32FC1` 타입 `Mat`으로 반환한다.

```cpp
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
```

---

### MygetGrayHistImage()

인접한 히스토그램 값을 선으로 연결하여 꺾은선 그래프 이미지로 변환한다.

```cpp
Mat MygetGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	int h = 100;
	minMaxLoc(hist, 0, &histMax);				// 히스토그램 최댓값 탐색
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));	// 흰 배경 이미지 생성
	for (int i = 1; i < 256; i++) {
		line(imgHist,
			Point(i - 1, h - 1 - cvRound(hist.at<float>(i - 1, 0) * (h - 1) / histMax)),
			Point(i,     h - 1 - cvRound(hist.at<float>(i, 0) * (h - 1) / histMax)),
			Scalar(0));	// 인접한 히스토그램 값을 선으로 연결하여 꺾은선 그래프로 표현
	}
	return imgHist;
}
```

---

### main()

lenna.bmp를 그레이스케일로 읽고 직접 계산한 히스토그램을 꺾은선 그래프로 출력한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);						// 원본 이미지 출력
	Mat hist = MycalcGrayHist(src);			// 픽셀 단위 반복문으로 히스토그램 계산
	Mat hist_img = MygetGrayHistImage(hist);	// 꺾은선 그래프 이미지 생성
	imshow("hist_img", hist_img);			// 히스토그램 이미지 출력
	waitKey();
	return 0;
}
```

### 실행 결과

![image4](https://github.com/user-attachments/assets/ce915567-f175-40ad-aaf4-e22c52cd8def)
