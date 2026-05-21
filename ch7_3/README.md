# ch 7-3 영상의 샤프닝

## 과제 1

샤프닝 필터를 1~5회 반복 적용하여 누적된 샤프닝 결과를 순서대로 출력하는 프로그램이다.

---

### main()

8방향 샤프닝 커널을 이전 결과에 반복 적용하며 각 회차의 결과를 출력한다.

```cpp
int main()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);	// rose.bmp를 그레이스케일로 읽기
	if (src.empty()) return -1;

	float weights[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };
	Mat mask = Mat(3, 3, CV_32F, weights);	// 8방향 샤프닝 커널

	imshow("src", src);

	Mat result;
	src.copyTo(result);

	for (int i = 1; i <= 5; i++) {
		filter2D(result, result, -1, mask);	// 이전 결과에 샤프닝을 반복 적용
		String desc = format("Sharpening x%d", i);
		Mat display;
		result.copyTo(display);
		putText(display, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("sharpen", display);
		waitKey(0);
	}
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/130ef728-54e7-4c43-9cf6-3e93af34dd02)



## 과제 2

평균값 필터를 이용한 언샤프 마스킹에서 α값을 10~50으로 변화시키며 샤프닝 결과를 출력하는 프로그램이다.

---

### main()

`CV_32F`로 변환 후 3×3 평균값 필터를 적용하고 `dst = (1+α)*src - α*blurred` 공식으로 샤프닝한다.

```cpp
int main(void)
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);

	Mat src_f;
	src.convertTo(src_f, CV_32F);	// 큰 alpha 값 연산을 위해 float으로 변환

	Mat blurred_f;
	blur(src_f, blurred_f, Size(3, 3));	// 3x3 평균값 필터 적용

	for (int alpha = 10; alpha <= 50; alpha += 10) {
		Mat dst_f = (1.f + alpha) * src_f - alpha * blurred_f;
		// 언샤프 마스킹: dst = (1+α)*src - α*blurred
		Mat dst;
		dst_f.convertTo(dst, CV_8U);	// float 결과를 0~255로 클리핑하여 uchar 변환
		String desc = format("Mean blur, alpha: %d", alpha);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/62f5e9ba-9c5f-4a47-944e-34114d46b94f)



## 과제 3

트랙바로 α값(0~50)을 실시간으로 조절하며 평균값 필터 기반 언샤프 마스킹을 수행하는 프로그램이다.

---

### on_trackbar()

트랙바 위치(α값)를 받아 언샤프 마스킹을 수행하고 결과를 출력한다.

```cpp
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
```

---

### main()

이미지를 읽고 평균값 필터를 미리 계산한 뒤 트랙바(0~50)와 콜백을 등록한다.

```cpp
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
```

### 실행 결과
[video](https://github.com/user-attachments/assets/50ede229-6334-4450-89fe-618831f95cde)



## 과제 4

마우스 드래그로 선택한 ROI 영역에만 샤프닝 필터를 적용하는 프로그램이다.

---

### on_mouse()

좌클릭 시 시작점을 저장하고, 클릭 해제 시 ROI를 추출하여 샤프닝 필터를 적용한다.

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
			filter2D(dst(roi), dst(roi), -1, mask);	// ROI 영역에만 샤프닝 필터 적용
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

lenna.bmp를 그레이스케일로 읽고 샤프닝 커널과 마우스 콜백을 등록한다.

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
[video](https://github.com/user-attachments/assets/74eecd20-3d15-48da-afa3-1ad240e3e14f)
