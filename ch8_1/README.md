# ch 8-1 영상의 기하학적 변환

## 과제 1

3개 점(좌측상단, 우측상단, 우측하단)의 대응 관계로 아핀 변환 행렬을 구하고 영상을 ½로 축소하여 출력하는 프로그램이다.

---

### main()

`getAffineTransform()`으로 ½ 축소 행렬 M을 계산하고 `warpAffine()`으로 변환을 적용한다.

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
	dstPts[1] = Point2f((src.cols - 1) / 2.0, 0);		// 우측상단 → x 좌표 절반
	dstPts[2] = Point2f((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);	// 우측하단 → x, y 절반
	Mat M = getAffineTransform(srcPts, dstPts);	// 3쌍의 대응점으로 2×3 아핀 행렬 계산
	cout << M << endl;
	Mat dst;
	warpAffine(src, dst, M, Size());	// Size()는 입력과 동일한 캔버스 크기 사용
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image1](https://github.com/user-attachments/assets/05b9d591-1383-4f90-8581-7781734fb0a6)


## 과제 2

work1과 동일한 아핀 변환에서 `transform()` 함수를 이용하여 원본영상의 정중앙점이 결과영상에서 어떤 좌표로 변환되는지 구하는 프로그램이다.

---

### main()

중앙점을 3채널(x, y, 1) 형태로 구성하고 `transform()`에 행렬 M을 적용하여 변환된 좌표를 출력한다.

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
	dstPts[1] = Point2f((src.cols - 1) / 2.0, 0);
	dstPts[2] = Point2f((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);

	Mat M = getAffineTransform(srcPts, dstPts);	// 아핀 변환 행렬 계산
	cout << "M = " << endl << M << endl;

	float cx = (src.cols - 1) / 2.0f;	// 원본영상의 정중앙점 x
	float cy = (src.rows - 1) / 2.0f;	// 원본영상의 정중앙점 y

	// transform()으로 중앙점이 결과영상에서 어디로 이동하는지 계산
	// 아핀 변환: [x', y'] = M * [x, y, 1]^T
	// 3채널 입력(x, y, 1)에 2x3 행렬 M을 곱하면 2채널 출력(x', y') 획득
	Mat ptSrc(1, 1, CV_32FC3, Vec3f(cx, cy, 1.f));
	Mat ptDst;
	transform(ptSrc, ptDst, M);	// 아핀 변환 행렬 M을 점에 직접 적용

	Vec2f result = ptDst.at<Vec2f>(0, 0);
	cout << "원본 중앙점: (" << cx << ", " << cy << ")" << endl;
	cout << "변환된 좌표: (" << result[0] << ", " << result[1] << ")" << endl;

	Mat dst;
	warpAffine(src, dst, M, Size());
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image2](https://github.com/user-attachments/assets/2b9dba19-4e6b-456d-a974-ad8be2db8d19)



## 과제 3

3개 점의 대응 관계로 아핀 변환 행렬을 구하고 입력영상을 2배로 확대하여 출력하는 프로그램이다. `dsize`를 입력영상의 2배 크기로 설정한다.

---

### main()

우측상단·우측하단 점을 2배 좌표로 설정하여 2배 확대 행렬을 계산하고, `dsize`를 명시하여 전체 확대 영상을 출력한다.

```cpp
int main(void)
{
	Mat src = imread("tekapo.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	// 3개 점(좌측상단, 우측상단, 우측하단)의 2배 확대 변환 관계 설정
	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);				// 좌측상단
	srcPts[1] = Point2f(src.cols - 1, 0);			// 우측상단
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);	// 우측하단

	dstPts[0] = Point2f(0, 0);					// 좌측상단 (고정)
	dstPts[1] = Point2f(2 * (src.cols - 1), 0);			// 우측상단 → x 2배
	dstPts[2] = Point2f(2 * (src.cols - 1), 2 * (src.rows - 1));	// 우측하단 → x, y 2배

	Mat M = getAffineTransform(srcPts, dstPts);	// 아핀 변환 행렬 계산 (2배 확대)
	cout << "M = " << endl << M << endl;

	// 결과영상 크기를 입력영상의 2배로 설정
	Size dsize(src.cols * 2, src.rows * 2);

	Mat dst;
	warpAffine(src, dst, M, dsize);	// dsize를 명시하여 2배 크기 결과영상 생성
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image3](https://github.com/user-attachments/assets/3143bae9-a0c8-49e7-8599-9e866cbc7f5c)

## 과제 4

카메라 영상을 실시간으로 출력하고 키보드 입력(`a`/`b`/`c`/`q`)으로 2배 확대·½ 축소·정상 크기 아핀 변환을 전환하는 프로그램이다.

---

### main()

매 프레임마다 모드에 맞는 대응점과 `dsize`를 설정하여 `warpAffine()`을 적용하고, 모드가 바뀔 때만 변환 행렬을 터미널에 출력한다.

```cpp
int main(void)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) { cerr << "Camera open failed!" << endl; return -1; }

	int mode = 1;		// 1: 정상, 2: 2배 확대, 3: 1/2 축소
	int prevMode = 0;	// 이전 모드 (0으로 초기화하여 시작 시 행렬 출력 유도)

	Mat frame, dst;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		int cols = frame.cols;
		int rows = frame.rows;

		Point2f srcPts[3];
		srcPts[0] = Point2f(0, 0);			// 좌측상단
		srcPts[1] = Point2f(cols - 1, 0);		// 우측상단
		srcPts[2] = Point2f(cols - 1, rows - 1);	// 우측하단

		Point2f dstPts[3];
		Size dsize;

		if (mode == 2) {
			// a키: 2배 확대 → 각 점의 x, y 좌표를 2배
			dstPts[0] = Point2f(0, 0);
			dstPts[1] = Point2f(2 * (cols - 1), 0);
			dstPts[2] = Point2f(2 * (cols - 1), 2 * (rows - 1));
			dsize = Size(cols * 2, rows * 2);	// 결과영상 크기 2배
		} else if (mode == 3) {
			// b키: 1/2 축소 → 각 점의 x, y 좌표를 1/2배
			dstPts[0] = Point2f(0, 0);
			dstPts[1] = Point2f((cols - 1) / 2.0f, 0);
			dstPts[2] = Point2f((cols - 1) / 2.0f, (rows - 1) / 2.0f);
			dsize = Size(cols / 2, rows / 2);	// 결과영상 크기 1/2배
		} else {
			// c키 또는 초기: 정상 크기 → 좌표 변환 없음 (항등 변환)
			dstPts[0] = Point2f(0, 0);
			dstPts[1] = Point2f(cols - 1, 0);
			dstPts[2] = Point2f(cols - 1, rows - 1);
			dsize = Size(cols, rows);		// 결과영상 크기 동일
		}

		Mat M = getAffineTransform(srcPts, dstPts);	// 아핀 변환 행렬 계산

		// 모드가 바뀐 경우에만 변환 행렬을 터미널에 출력
		if (mode != prevMode) {
			string label;
			if      (mode == 2) label = "[a] 2배 확대";
			else if (mode == 3) label = "[b] 1/2 축소";
			else                label = "[c] 정상 크기";
			cout << label << " M = " << endl << M << endl;
			prevMode = mode;
		}

		warpAffine(frame, dst, M, dsize);		// 아핀 변환 적용
		imshow("dst", dst);

		int key = waitKey(30);
		if      (key == 'q') break;		// q: 종료
		else if (key == 'a') mode = 2;	// a: 2배 확대
		else if (key == 'b') mode = 3;	// b: 1/2 축소
		else if (key == 'c') mode = 1;	// c: 정상 크기
	}

	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/7ec2e4bf-1905-4cc6-af7a-5a442fa6d588)
