# ch 7-2 영상의 필터링

## 과제 1

`filter2D()`와 균일 커널을 이용하여 평균값 필터(blur)를 구현하는 프로그램이다.

---

### main()

커널 크기를 3×3에서 7×7까지 2씩 증가시키며 `filter2D()`로 평균값 필터를 적용하고 결과를 출력한다.

```cpp
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat dst;
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		Mat kernel = Mat::ones(ksize, ksize, CV_32FC1) / (float)(ksize * ksize);
		// 모든 원소가 1/(ksize*ksize)인 평균값 필터 커널 생성
		filter2D(src, dst, -1, kernel);	// 커널을 이미지에 적용 (-1: 출력 깊이를 입력과 동일하게)
		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}
```

### 실행 결과



## 과제 2

`blur()` 함수의 커널 크기(3·10·30)에 따른 처리 시간을 측정하여 출력하는 프로그램이다.

---

### main()

커널 크기별로 `blur()`를 실행하고 `chrono`로 처리 시간을 측정하여 콘솔에 출력한다.

```cpp
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat dst;
	int ksize[3] = { 3, 10 ,30 };
	for (int i = 0; i < 3; i++) {
		auto startTime = std::chrono::steady_clock::now();	// 시작 시간 저장
		blur(src, dst, Size(ksize[i], ksize[i]));
		String desc = format("Mean: %dx%d", ksize[i], ksize[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		auto endTime = std::chrono::steady_clock::now();	// 종료 시간 저장
		float totalTime = std::chrono::duration<float, std::milli>(endTime - startTime).count();
		cout << totalTime << "ms" << endl;	// 처리 시간(ms) 출력
		waitKey();
	}
	return 0;
}
```

### 실행 결과



## 과제 3

가우시안 공식을 직접 계산하여 2D 커널을 생성하고 `filter2D()`로 가우시안 블러를 구현하는 프로그램이다.

---

### main()

sigma 1~5에 대해 `G(x,y) = exp(-(x²+y²)/2σ²)` 공식으로 커널을 직접 생성하고 `filter2D()`로 적용한다.

```cpp
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		int ksize = 8 * sigma + 1;	// ±4σ 범위를 포함하는 커널 크기
		int half = ksize / 2;
		Mat kernel2D(ksize, ksize, CV_32F);
		for (int y = -half; y <= half; y++) {
			for (int x = -half; x <= half; x++) {
				kernel2D.at<float>(y + half, x + half) =
					exp(-(x * x + y * y) / (2.f * sigma * sigma));
				// G(x,y) = exp(-(x²+y²) / 2σ²): 2D 가우시안 공식 직접 계산
			}
		}
		kernel2D /= sum(kernel2D)[0];	// 커널 원소 합이 1이 되도록 정규화
		filter2D(src, dst, -1, kernel2D);
		String desc = format("Gaussian: sigma = %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}
```

### 실행 결과



## 과제 4

`GaussianBlur()` 함수의 sigma 1~5에 따른 처리 시간을 측정하여 출력하는 프로그램이다.

---

### main()

sigma별로 `GaussianBlur()`만 타이밍 범위에 포함하여 처리 시간을 측정하고 콘솔에 출력한다.

```cpp
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);
	waitKey(1);	// 창 초기화를 루프 전에 완료하여 첫 번째 측정값 왜곡 방지
	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		auto startTime = chrono::steady_clock::now();
		GaussianBlur(src, dst, Size(), (double)sigma);	// 실행 시간 측정 대상
		auto endTime = chrono::steady_clock::now();
		float totalTime = chrono::duration<float, milli>(endTime - startTime).count();
		cout << "sigma = " << sigma << ": " << totalTime << "ms" << endl;	// 처리 시간 출력
		String desc = format("Gaussian: sigma = %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}
```

### 실행 결과



## 과제 5

마우스 드래그로 선택한 ROI 영역에만 가우시안 블러(sigma=5)를 적용하는 프로그램이다.

---

### on_mouse()

좌클릭 시 시작점을 저장하고, 클릭 해제 시 ROI를 추출하여 가우시안 블러를 적용한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptStart = Point(x, y);	// 드래그 시작점 저장
		break;
	case EVENT_LBUTTONUP: {
		Point ptEnd(x, y);
		// 두 점으로 유효한 ROI 사각형 생성 (좌상단~우하단 순서 보정)
		Rect roi(
			Point(min(ptStart.x, ptEnd.x), min(ptStart.y, ptEnd.y)),
			Point(max(ptStart.x, ptEnd.x), max(ptStart.y, ptEnd.y))
		);
		if (roi.width > 0 && roi.height > 0) {
			GaussianBlur(dst(roi), dst(roi), Size(), 5);	// ROI 영역에만 가우시안 블러 적용 (sigma=5)
			dst.copyTo(src);
			imshow("dst", dst);
		}
		break;
	}
	default:
		break;
	}
}
```

---

### main()

lenna.bmp를 그레이스케일로 읽고 마우스 콜백을 등록한다.

```cpp
int main(void)
{
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }

	img.copyTo(src);
	img.copyTo(dst);

	namedWindow("dst");
	setMouseCallback("dst", on_mouse);	// 마우스 콜백 등록

	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과



## 과제 6

트랙바로 sigma(0~9)를 선택하고 마우스 드래그로 선택한 ROI 영역에 가우시안 블러를 적용하는 프로그램이다.

---

### on_trackbar()

트랙바 위치 값을 전역 변수 `sigma`에 저장한다.

```cpp
void on_trackbar(int pos, void*)
{
	sigma = pos;	// 트랙바 위치를 전역 변수에 저장
}
```

---

### on_mouse()

좌클릭 해제 시 ROI를 추출하고 트랙바로 선택한 sigma로 가우시안 블러를 적용한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptStart = Point(x, y);	// 드래그 시작점 저장
		break;
	case EVENT_LBUTTONUP: {
		Point ptEnd(x, y);
		// 두 점으로 유효한 ROI 사각형 생성 (좌상단~우하단 순서 보정)
		Rect roi(
			Point(min(ptStart.x, ptEnd.x), min(ptStart.y, ptEnd.y)),
			Point(max(ptStart.x, ptEnd.x), max(ptStart.y, ptEnd.y))
		);
		if (roi.width > 0 && roi.height > 0 && sigma > 0) {
			GaussianBlur(dst(roi), dst(roi), Size(), sigma);	// 트랙바로 선택한 sigma로 블러 적용
			imshow("dst", dst);
		}
		break;
	}
	default:
		break;
	}
}
```

---

### main()

lenna.bmp를 그레이스케일로 읽고 트랙바(0~9, 초기값 1)와 마우스 콜백을 등록한다.

```cpp
int main(void)
{
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }

	img.copyTo(src);
	img.copyTo(dst);

	namedWindow("dst");
	createTrackbar("sigma", "dst", &sigma, 9, on_trackbar);	// 0~9 범위 트랙바 생성
	setTrackbarPos("sigma", "dst", 1);						// 초기값 1로 설정
	setMouseCallback("dst", on_mouse);						// 마우스 콜백 등록

	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
