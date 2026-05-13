# ch 5-4 영상의 밝기와 명암비 조절

## 과제 1

직선의 방정식을 이용하여 히스토그램 스트레칭 수식을 유도한다.

---

히스토그램 스트레칭은 픽셀값의 최솟값 Gmin을 0으로, 최댓값 Gmax를 255로 선형 변환하는 연산이다.

두 점 **(Gmin, 0)** 과 **(Gmax, 255)** 를 지나는 직선의 방정식을 이용하면 다음과 같이 유도된다.

**기울기:**

$$m = \frac{255 - 0}{G_{max} - G_{min}} = \frac{255}{G_{max} - G_{min}}$$

**직선의 방정식 (점-기울기 형):**

$$dst = m \cdot (src - G_{min}) + 0$$

**수식 정리:**

$$dst(x, y) = \frac{src(x, y) - G_{min}}{G_{max} - G_{min}} \times 255$$

즉, 원본 픽셀에서 최솟값을 뺀 뒤 전체 범위(Gmax - Gmin)로 나누고 255를 곱하여 0~255 범위로 정규화한다.

---

### 실행 결과



## 과제 2

히스토그램 스트레칭과 히스토그램 평활화의 차이를 설명한다.

---

### 히스토그램 스트레칭 (Histogram Stretching)

픽셀값의 최솟값(Gmin)과 최댓값(Gmax)을 각각 0과 255로 **선형 변환**한다.

- 변환식: `dst = (src - Gmin) / (Gmax - Gmin) * 255`
- 픽셀 간 상대적 밝기 차이는 유지되며 히스토그램의 분포 형태는 그대로이고 범위만 확장된다.
- 원본 히스토그램이 한쪽에 몰려 있을 때 유효하지만, 고르게 분포된 영상에는 효과가 작다.

---

### 히스토그램 평활화 (Histogram Equalization)

누적 분포 함수(CDF)를 이용해 픽셀값을 **비선형 변환**하여 히스토그램을 균등하게 만든다.

- 변환식: `dst = CDF(src) / 전체픽셀수 * 255`
- 밝기 분포를 전체 0~255 범위에 최대한 균등하게 재분배한다.
- 대비(명암비)가 낮은 영상에서 효과적이며, 히스토그램 스트레칭보다 전반적으로 더 뚜렷한 개선을 보인다.

---

### 실행 결과



## 과제 3

픽셀 단위 반복문으로 히스토그램 스트레칭을 직접 구현하는 프로그램이다.

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

### getGrayHistImage()

히스토그램 데이터를 막대 그래프 이미지로 변환하여 반환한다.

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

Gmin·Gmax를 구한 뒤 픽셀 단위 반복문으로 스트레칭을 적용하고 원본·결과 이미지와 히스토그램을 출력한다.

```cpp
int main(void)
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);	// hawkes.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);		// 이미지 전체 픽셀의 최솟값·최댓값 탐색
	cout << "Gmin:" << gmin << endl;
	cout << "Gmax:" << gmax << endl;
	Mat dst(src.size(), src.type());
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>((src.at<uchar>(j, i) - gmin) * 255 / (gmax - gmin));
			// dst = (src - Gmin) / (Gmax - Gmin) * 255: 히스토그램 스트레칭 수식 적용
		}
	}

	imshow("src", src);							// 원본 이미지 출력
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));	// 원본 히스토그램 출력
	imshow("dst", dst);							// 스트레칭 결과 이미지 출력
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));	// 결과 히스토그램 출력
	waitKey();
	return 0;
}
```

### 실행 결과



## 과제 4

행렬 연산으로 히스토그램 스트레칭을 간결하게 구현하는 프로그램이다.

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

### getGrayHistImage()

히스토그램 데이터를 막대 그래프 이미지로 변환하여 반환한다.

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

픽셀 단위 반복문 대신 OpenCV 행렬 연산으로 스트레칭을 한 줄로 적용하고 결과를 출력한다.

```cpp
int main(void)
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);	// hawkes.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);	// 이미지 전체 픽셀의 최솟값·최댓값 탐색
	cout << "Gmin:" << gmin << endl;
	cout << "Gmax:" << gmax << endl;
	Mat dst = (src - gmin) * 255 / (gmax - gmin);
	// 행렬 연산으로 히스토그램 스트레칭 수식을 한 줄로 적용 (과제 3과 동일한 결과)
	imshow("src", src);							// 원본 이미지 출력
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));	// 원본 히스토그램 출력
	imshow("dst", dst);							// 스트레칭 결과 이미지 출력
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));	// 결과 히스토그램 출력
	waitKey();
	return 0;
}
```

### 실행 결과



## 과제 5

OpenCV의 `equalizeHist()`를 사용하여 히스토그램 평활화를 수행하는 프로그램이다.

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

### getGrayHistImage()

히스토그램 데이터를 막대 그래프 이미지로 변환하여 반환한다.

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

`equalizeHist()`로 히스토그램 평활화를 수행하고 원본·결과 이미지와 히스토그램을 출력한다.

```cpp
int main(void)
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);	// hawkes.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);	// 이미지 전체 픽셀의 최솟값·최댓값 탐색
	cout << "Gmin:" << gmin << endl;
	cout << "Gmax:" << gmax << endl;
	Mat dst;
	equalizeHist(src, dst);	// CDF 기반 히스토그램 평활화 적용
	imshow("src", src);							// 원본 이미지 출력
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));	// 원본 히스토그램 출력
	imshow("dst", dst);							// 평활화 결과 이미지 출력
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));	// 결과 히스토그램 출력
	waitKey();
	return 0;
}
```

### 실행 결과



## 과제 6

히스토그램과 함께 누적 분포 함수(CDF) 곡선 그래프를 시각화하는 프로그램이다.

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

### getGrayHistImage()

히스토그램 데이터를 막대 그래프 이미지로 변환하여 반환한다.

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

### getGraySumHistImage()

히스토그램의 누적합을 구한 뒤 `normalize()`로 정규화하고 인접 점을 연결하여 CDF 곡선을 그린다.

```cpp
Mat getGraySumHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	const int h = 100;

	// 히스토그램 누적합(CDF) 계산
	Mat cdf;
	hist.copyTo(cdf);
	for (int i = 1; i < 256; i++)
		cdf.at<float>(i, 0) += cdf.at<float>(i - 1, 0);

	// 전체 픽셀 수 기준으로 [0, h-1] 범위에 정규화
	normalize(cdf, cdf, 0, h - 1, NORM_MINMAX);

	Mat imgHist(h, 256, CV_8UC1, Scalar(255));
	for (int i = 1; i < 256; i++) {
		// 인접한 CDF 값을 선으로 연결하여 누적 곡선으로 표현
		line(imgHist,
			Point(i - 1, h - 1 - cvRound(cdf.at<float>(i - 1, 0))),
			Point(i,     h - 1 - cvRound(cdf.at<float>(i, 0))),
			Scalar(0));
	}
	return imgHist;
}
```

---

### main()

원본 이미지의 히스토그램과 CDF 곡선을 함께 출력한다.

```cpp
int main(void)
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);	// hawkes.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);	// 이미지 전체 픽셀의 최솟값·최댓값 탐색
	cout << "Gmin:" << gmin << endl;
	cout << "Gmax:" << gmax << endl;
	Mat dst;
	equalizeHist(src, dst);	// 히스토그램 평활화 (결과는 미출력)
	imshow("src", src);									// 원본 이미지 출력
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));		// 원본 히스토그램 출력
	imshow("srcSumHist", getGraySumHistImage(calcGrayHist(src)));	// 원본 CDF 곡선 출력
	waitKey();
	return 0;
}
```

### 실행 결과
