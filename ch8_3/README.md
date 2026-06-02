# ch 8-3 영상의 기하학적 변환

## 과제 1

lenna 영상을 중심 기준 시계방향 45도 회전 후 2배 확대하는 프로그램이다. 회전과 확대를 두 단계로 분리하여 수행한다.

---

### main()

1단계에서 `warpAffine()`으로 원본 크기 그대로 회전하고, 2단계에서 `resize()`로 2배 확대한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f cp(src.cols / 2.f, src.rows / 2.f);	// 입력영상 중심 좌표
	Mat M = getRotationMatrix2D(cp, -45, 1);	// 시계방향 45도 회전 (음수 = 시계방향)

	// 1단계: 입력영상 크기 그대로 회전 변환 적용
	Mat rotated;
	warpAffine(src, rotated, M, src.size());

	// 2단계: 회전 결과영상을 2배로 확대
	Mat dst;
	resize(rotated, dst, Size(), 2, 2);	// x, y 방향 각각 2배 확대

	imshow("src", src);
	imshow("rotated", rotated);
	imshow("dst", dst);
	waitKey();
	return 0;
}
```

### 실행 결과
![image](https://github.com/user-attachments/assets/f40054ef-74ea-44bd-916c-3e2783ca22dd)


## 과제 2

키보드로 회전 각도를 입력받아 lenna 영상을 반복 회전하는 프로그램이다. 항상 원본에 누적 각도를 1회 적용하여 반복 보간 왜곡을 방지한다. q를 입력하면 종료한다.

---

### main()

`totalAngle`에 입력 각도를 누적하고 매 회전 시 원본(src)에 한 번만 `warpAffine()`을 적용한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f cp(src.cols / 2.f, src.rows / 2.f);	// 원본영상 중심 (고정)
	double totalAngle = 0.0;			// 누적 회전각도

	imshow("src", src);
	imshow("dst", src);
	waitKey(1);

	while (true) {
		cout << "회전 각도 입력 (q: 종료): ";
		string input;
		cin >> input;

		if (input == "q" || input == "Q") break;

		totalAngle += stod(input);	// 각도 누적 (이전 각도에 더함)

		Mat M = getRotationMatrix2D(cp, totalAngle, 1);	// 누적 각도로 회전 행렬 생성

		Mat dst;
		// 항상 원본(src)에 누적 각도로 한 번만 적용 → 보간 1회로 왜곡 방지
		warpAffine(src, dst, M, src.size());

		imshow("dst", dst);
		waitKey(1);
	}

	return 0;
}
```

### 실행 결과
[video1](https://github.com/user-attachments/assets/67fb8c9a-0532-424e-a641-ac78769e152c)



## 과제 3

`r`키를 누를 때마다 시계방향 10도, `b`키를 누를 때마다 반시계방향 10도씩 회전하는 프로그램이다. 36번 누르면 원본으로 복귀하며 q를 누르면 종료한다.

---

### main()

`totalAngle`을 ±10도씩 누적하고 항상 원본(src)에 1회만 `warpAffine()`을 적용하여 왜곡을 방지한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Point2f cp(src.cols / 2.f, src.rows / 2.f);	// 영상 중심 좌표 (고정)
	double totalAngle = 0.0;			// 누적 회전각도

	imshow("dst", src);

	while (true) {
		int key = waitKey(0);	// 키 입력 대기

		if (key == 'r') {
			totalAngle -= 10.0;	// r키: 시계방향 10도 (음수 = 시계방향)
		} else if (key == 'b') {
			totalAngle += 10.0;	// b키: 반시계방향 10도 (양수 = 반시계방향)
		} else if (key == 'q') {
			break;			// q키: 종료
		} else {
			continue;		// r, b, q 외 키는 무시
		}

		// 360도 범위로 정규화 (36번 누르면 원본으로 복귀)
		if (totalAngle >= 360.0) totalAngle -= 360.0;
		if (totalAngle <= -360.0) totalAngle += 360.0;

		Mat M = getRotationMatrix2D(cp, totalAngle, 1);	// 누적 각도로 회전 행렬 생성

		Mat dst;
		warpAffine(src, dst, M, src.size());	// 항상 원본에 1회 적용 → 왜곡 방지

		cout << "누적 회전각도: " << totalAngle << "도" << endl;
		imshow("dst", dst);
	}

	return 0;
}
```

### 실행 결과
[video2](https://github.com/user-attachments/assets/2fccdd8b-4daa-4929-83ac-73f24153b41d)



## 과제 4

`flip()` 함수 대신 `warpAffine()`으로 동일한 좌우·상하·양방향 반전을 구현하는 프로그램이다.

---

### main()

반전 행렬을 직접 정의하고 세 가지 flipCode에 대해 순서대로 `warpAffine()`을 적용한다.

```cpp
int main(void)
{
	Mat src = imread("eastsea.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	imshow("src", src);

	int cols = src.cols;
	int rows = src.rows;

	// flip() 대신 warpAffine()으로 동일한 반전 효과 구현
	// flipCode=1: 좌우 반전 → x' = (cols-1)-x, y' = y
	Mat M1 = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, 1, 0);
	// flipCode=0: 상하 반전 → x' = x, y' = (rows-1)-y
	Mat M2 = (Mat_<double>(2, 3) << 1, 0, 0, 0, -1, rows - 1);
	// flipCode=-1: 좌우+상하 반전 → x' = (cols-1)-x, y' = (rows-1)-y
	Mat M3 = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, -1, rows - 1);

	Mat Ms[] = { M1, M2, M3 };
	int flipCode[] = { 1, 0, -1 };

	Mat dst;
	for (int i = 0; i < 3; i++) {
		warpAffine(src, dst, Ms[i], src.size());	// 반전 행렬 적용
		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255, 0, 0), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	return 0;
}
```

### 실행 결과
[video3](https://github.com/user-attachments/assets/79978969-393f-42cb-91fd-846b9b55bf8b)



## 과제 5

`a`키(좌우), `b`키(상하), `c`키(양방향) 입력으로 `warpAffine()` 기반 반전 변환을 실시간으로 전환하는 프로그램이다. q를 누르면 종료한다.

---

### main()

세 가지 반전 행렬을 루프 전에 사전 정의하고, 키 입력에 따라 해당 행렬을 원본(src)에 적용한다.

```cpp
int main(void)
{
	Mat src = imread("eastsea.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	int cols = src.cols;
	int rows = src.rows;

	// warpAffine용 반전 행렬 사전 정의
	// a키: 좌우 반전 → x' = (cols-1)-x, y' = y
	Mat M_a = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, 1, 0);
	// b키: 상하 반전 → x' = x, y' = (rows-1)-y
	Mat M_b = (Mat_<double>(2, 3) << 1, 0, 0, 0, -1, rows - 1);
	// c키: 좌우+상하 반전 → x' = (cols-1)-x, y' = (rows-1)-y
	Mat M_c = (Mat_<double>(2, 3) << -1, 0, cols - 1, 0, -1, rows - 1);

	imshow("dst", src);

	while (true) {
		int key = waitKey(0);

		Mat M, dst;
		String desc;

		if (key == 'a') {
			M = M_a;			// a키: 좌우 대칭
			desc = "Horizontal flip (a)";
		} else if (key == 'b') {
			M = M_b;			// b키: 상하 대칭
			desc = "Vertical flip (b)";
		} else if (key == 'c') {
			M = M_c;			// c키: 좌우+상하 대칭
			desc = "Both flip (c)";
		} else if (key == 'q') {
			break;				// q키: 종료
		} else {
			continue;			// 그 외 키 무시
		}

		warpAffine(src, dst, M, src.size());	// 반전 행렬 적용
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255, 0, 0), 1, LINE_AA);
		imshow("dst", dst);
	}

	return 0;
}
```

### 실행 결과
[video4](https://github.com/user-attachments/assets/99a086d5-277c-4149-a50c-187f1d6672d4)



## 과제 6

카메라 영상을 실시간으로 출력하고 `r`키를 누를 때마다 시계방향으로 90도씩 회전하는 프로그램이다. q를 누르면 종료한다.

---

### main()

매 프레임마다 카메라에서 새 프레임을 받아 누적 각도로 `warpAffine()`을 1회 적용한다.

```cpp
int main(void)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) { cerr << "Camera open failed!" << endl; return -1; }

	double totalAngle = 0.0;	// 누적 회전각도 (r키 누를 때마다 -90도씩 감소)

	Mat frame, dst;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		int key = waitKey(30);
		if      (key == 'q') break;
		else if (key == 'r') {
			totalAngle -= 90.0;		// r키: 시계방향 90도
			if (totalAngle <= -360.0)
				totalAngle += 360.0;	// 360도 정규화
		}

		Point2f cp(frame.cols / 2.f, frame.rows / 2.f);	// 매 프레임 중심
		Mat M = getRotationMatrix2D(cp, totalAngle, 1);		// 누적 각도로 회전 행렬 생성
		warpAffine(frame, dst, M, frame.size());		// 새 프레임에 회전 적용

		imshow("dst", dst);
	}

	return 0;
}
```

### 왜곡 발생 여부

카메라 입력에서는 **왜곡이 발생하지 않는다.**
카메라는 매 프레임마다 센서에서 새로 캡처한 원본 데이터를 제공하므로 `warpAffine()`이 항상 원본 화질의 프레임에 **1회만** 적용된다. 정지 영상을 반복 회전(과제 2 수정 전)할 때와 달리 보간 오차가 누적될 대상 자체가 없기 때문이다.

### 실행 결과
[video5](https://github.com/user-attachments/assets/e70890fb-3d58-4b8b-b76c-93e70f18aaa9)
