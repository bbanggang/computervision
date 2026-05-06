# ch 5-1 영상의 밝기와 명암비 조절

## 과제 1

그레이스케일 이미지에서 좌클릭 시 전체 밝기를 높이고 우클릭 시 낮추는 프로그램이다.

---

### on_mouse()

좌클릭·우클릭 이벤트에 따라 이미지 전체 밝기를 ±10씩 조정한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환
	switch (event) {
	case EVENT_LBUTTONDOWN:
		img += 10;		// 좌클릭: 이미지 전체 밝기 +10
		break;
	case EVENT_RBUTTONDOWN:
		img -= 10;		// 우클릭: 이미지 전체 밝기 -10
		break;
	default:
		break;
	}
}
```

---

### main()

이미지를 그레이스케일로 불러와 마우스 콜백을 등록한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse, &img);	// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);
		if (key == 'q') break;		// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video1](https://github.com/user-attachments/assets/9132b925-90e1-48d7-80d0-16e31a293b43)



## 과제 2

그레이스케일 이미지에서 마우스 드래그로 선택한 ROI 영역의 밝기를 높이는 프로그램이다.

---

### on_mouse()

좌클릭 시 시작점을, 해제 시 끝점을 저장하고 두 점으로 ROI를 추출하여 밝기를 +100 높인다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환
	static Point ptOld;							// 드래그 시작점 (static: 함수 호출 간 유지)
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);	// 좌클릭: 드래그 시작점 저장
		break;
	case EVENT_LBUTTONUP:
		Point ptNew = Point(x, y);				// 좌클릭 해제: 드래그 끝점 저장
		Mat roi_img = img(Rect(ptOld, ptNew));	// 시작점~끝점으로 ROI 추출
		roi_img += 100;							// ROI 영역 밝기 +100
	}
}
```

---

### main()

이미지를 그레이스케일로 불러와 마우스 콜백을 등록한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse, &img);	// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);
		if (key == 'q') break;		// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video2](https://github.com/user-attachments/assets/4e46e74a-5c1a-431d-a848-f0d9cd8be543)

## 과제 3

트랙바로 밝기 조정 방향(밝게/어둡게)을 선택하고 좌클릭 시 이미지 전체 밝기를 조정하는 프로그램이다.

---

### set_pos()

트랙바 위치 값을 전역 변수에 저장하여 밝기 조정 방향을 선택한다.

```cpp
void set_pos(int pos, void* userdata) {
	trackbar_pos = pos;		// 트랙바 위치를 전역 변수에 저장
}
```

---

### on_mouse()

좌클릭 이벤트 발생 시 트랙바 위치에 따라 이미지 전체 밝기를 ±10씩 조정한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환
	switch (event) {
	case EVENT_LBUTTONDOWN:
		if(trackbar_pos == 0) img += 10;	// 트랙바 0: 좌클릭 시 밝기 +10
		else img -= 10;						// 트랙바 1: 좌클릭 시 밝기 -10
		break;
	default:
		break;
	}
}
```

---

### main()

이미지를 그레이스케일로 불러와 트랙바와 마우스 콜백을 함께 등록한다.

```cpp
int main(void) {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	namedWindow("dst");
	createTrackbar("mode", "dst", 0, 1, set_pos);		// 0~1 범위 트랙바 생성 (0: 밝게, 1: 어둡게)
	setMouseCallback("dst", on_mouse, &src);			// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	while (true) {
		imshow("dst", src);
		if (waitKey(100) == 'q') break;		// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video3](https://github.com/user-attachments/assets/16f78b4d-c8c1-4357-acda-91915db6a405)


## 과제 4

그레이스케일 이미지에서 마우스 좌클릭 드래그 시 붓처럼 지나간 영역의 밝기를 높이는 프로그램이다.

---

### on_mouse()

좌클릭을 누른 채 마우스를 이동할 때 현재 좌표와 인접 4개 좌표(십자 모양)의 밝기를 +100 높인다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	Mat& img = *static_cast<Mat*>(userdata);	// userdata를 Mat 참조로 변환

	switch (event) {
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {		// 좌클릭을 누른 채 이동 중일 때만 처리
			vector<Point> pts = {
				Point(x, y), Point(x + 1, y), Point(x - 1, y),
				Point(x, y + 1), Point(x, y - 1)
			};	// 현재 좌표와 상하좌우 인접 4개 좌표로 붓 영역 구성 (십자 모양)
			for (auto& pt : pts) {
				img.at<uchar>(pt) = saturate_cast<uchar>(img.at<uchar>(pt) + 100);
				// 각 좌표의 밝기 +100 (saturate_cast로 255 초과 방지)
			}
		}
		break;
	default:
		break;
	}
}
```

---

### main()

이미지를 그레이스케일로 불러와 마우스 콜백을 등록한다.

```cpp
int main(void) {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	namedWindow("dst");
	setMouseCallback("dst", on_mouse, &src);	// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	while (true) {
		imshow("dst", src);
		if (waitKey(100) == 'q') break;		// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video4](https://github.com/user-attachments/assets/4ead3e6f-26f8-40e6-a096-2e774a14907b)
