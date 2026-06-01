# ch 8-2 영상의 기하학적 변환

## 과제 1

3개 점의 대응 관계로 아핀 변환 행렬을 구하고 tekapo 영상을 (150, 100)만큼 이동하여 출력하는 프로그램이다.

---

### main()

모든 점을 x방향으로 150, y방향으로 100 이동시킨 dstPts를 설정하고 캔버스를 그만큼 확장하여 잘림 없이 출력한다.

```cpp
int main(void)
{
	Mat src = imread("tekapo.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(150, 100);				// 좌측상단 → (150, 100) 이동
	dstPts[1] = Point2f((src.cols - 1 + 150), 100);	// 우측상단 → x+150, y+100
	dstPts[2] = Point2f((src.cols - 1) + 150, (src.rows - 1) + 100);	// 우측하단 → x+150, y+100
	Mat M = getAffineTransform(srcPts, dstPts);	// 이동 변환 행렬 계산
	cout << M << endl;

	Mat dst;
	warpAffine(src, dst, M, src.size() + Size(150, 100));	// 캔버스를 이동량만큼 확장
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image1](https://github.com/user-attachments/assets/8e4abc3e-36e0-4117-8171-3135bcc3b23a)


## 과제 2

3개 점의 대응 관계로 x축 방향 전단(Shear) 변환 행렬을 구하고 전단 계수 m₀₁ = 0.3이 되도록 tekapo 영상을 변환하여 출력하는 프로그램이다.

---

### main()

우측하단 점의 x 이동량을 `0.3×(rows−1)` (rows 기준)으로 설정하여 전단 계수 m₀₁ = 정확히 0.3을 확보하고 캔버스 너비를 rows 기준으로 확장한다.

```cpp
int main(void)
{
	Mat src = imread("tekapo.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(0, 0);
	dstPts[1] = Point2f((src.cols - 1), 0);
	dstPts[2] = Point2f((src.cols - 1) + 0.3f * (src.rows - 1), (src.rows - 1));
	// x 이동량을 rows 기준(0.3*(rows-1))으로 설정하여 m01 = 0.3 확보
	Mat M = getAffineTransform(srcPts, dstPts);
	cout << M << endl;

	Mat dst;
	warpAffine(src, dst, M, Size(src.cols + src.rows * 0.3, src.rows));
	// 캔버스 너비도 rows 기준으로 확장
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image2](https://github.com/user-attachments/assets/7edb2aa4-ed9f-45d8-adcc-1e519aa5b371)



## 과제 3

3개 점의 대응 관계로 x축 방향 전단 변환 행렬을 구하고 lenna 영상을 가로 방향으로 2배 늘어난 형태로 출력하는 프로그램이다.

---

### main()

우측하단 점의 x 좌표를 2배로 설정하여 전단 계수 m₀₁ = 1.0인 전단 행렬을 생성하고 캔버스 너비를 2배로 확장한다. `BORDER_REPLICATE`로 경계 픽셀을 복제하여 빈 영역을 채운다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(0, 0);
	dstPts[1] = Point2f((src.cols - 1), 0);
	dstPts[2] = Point2f((src.cols - 1) * 2, (src.rows - 1));	// 우측하단 x 좌표 2배 → 전단 계수 1.0

	Mat M = getAffineTransform(srcPts, dstPts);
	cout << M << endl;

	Mat dst;
	warpAffine(src, dst, M, Size(src.cols * 2, src.rows), 1, 1);
	// 1: INTER_LINEAR(양선형 보간), 1: BORDER_REPLICATE(경계 픽셀 복제)
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image3](https://github.com/user-attachments/assets/2c7e5300-8289-45c3-afbb-9f9f9247e31c)



## 과제 4

3개 점의 대응 관계로 2배 확대 아핀 변환 행렬을 구하고 lenna 영상을 2배 확대하여 출력하는 프로그램이다.

---

### main()

우측상단·우측하단 점을 각각 x·y 방향으로 2배 좌표로 설정하여 2배 확대 행렬을 계산하고 캔버스를 2배로 확장한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(0, 0);
	dstPts[1] = Point2f((src.cols - 1) * 2.f, 0);			// 우측상단 → x 2배
	dstPts[2] = Point2f((src.cols - 1) * 2.f, (src.rows - 1) * 2.f);	// 우측하단 → x, y 2배

	Mat M = getAffineTransform(srcPts, dstPts);	// 2배 확대 아핀 행렬 계산
	cout << M << endl;

	Mat dst;
	warpAffine(src, dst, M, Size(src.cols * 2, src.rows * 2));	// 캔버스 2배 확장
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image4](https://github.com/user-attachments/assets/8da7ad8b-640c-4a0b-9daf-046ff6d3ba4e)



## 과제 5

`Mat_<double>`로 아핀 변환 행렬을 직접 설정하여 lenna 영상을 0.5배 축소하고 (150, 100)만큼 이동하여 출력하는 프로그램이다.

---

### main()

`getAffineTransform()` 없이 행렬 원소를 직접 지정하여 축소·이동 복합 변환을 적용한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	// 아핀 행렬 직접 설정: 0.5배 축소 + (150, 100) 이동
	// [0.5,   0, 150]   x' = 0.5x + 150
	// [  0, 0.5, 100]   y' = 0.5y + 100
	Mat M = Mat_<double>({ 2, 3 }, { 0.5, 0, 150, 0, 0.5, 100 });
	Mat dst;
	cout << M << endl;

	warpAffine(src, dst, M, Size());	// Size()는 입력과 동일한 캔버스 크기 사용
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image5](https://github.com/user-attachments/assets/ace24a61-431a-4401-972d-ecbcaa2a7d74)



## 과제 6

카메라 영상을 실시간으로 출력하고 키보드 입력(`a`/`b`/`q`)으로 원본 출력과 work5 아핀 변환 출력을 전환하는 프로그램이다.

---

### main()

work5와 동일한 행렬 M을 루프 전에 한 번 생성하고, 매 프레임마다 모드에 따라 원본 또는 변환 결과를 출력한다.

```cpp
int main(void)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) { cerr << "Camera open failed!" << endl; return -1; }

	// work5와 동일한 아핀 변환 행렬: 0.5배 축소 + (150, 100) 이동
	Mat M = Mat_<double>({ 2, 3 }, { 0.5, 0, 150, 0, 0.5, 100 });
	cout << "M = " << endl << M << endl;

	int mode = 1;	// 1: 원본(a키), 2: work5 변환(b키)

	Mat frame, dst;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		if (mode == 1) {
			imshow("dst", frame);			// a키: 원본 그대로 출력
		} else {
			warpAffine(frame, dst, M, Size());	// b키: work5 아핀 변환 적용
			imshow("dst", dst);
		}

		int key = waitKey(30);
		if      (key == 'q') break;		// q: 종료
		else if (key == 'a') mode = 1;	// a: 원본 출력
		else if (key == 'b') mode = 2;	// b: work5 변환 출력
	}

	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/2b570f9e-2181-4b77-83ab-0be4def0ce10)
