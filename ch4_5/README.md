# ch 4-5 OpenCV 주요 기능

## 과제 1

트랙바 값을 반지름으로 사용하여 이미지 중심에 초록색 원을 그리는 프로그램이다.

---

### draw_circle()

트랙바 위치 값을 반지름으로 사용하여 이미지 중심에 초록색 원을 그린다.

```cpp
void draw_circle(int pos, void* userdata) {
	int width_center = (*(Mat*)userdata).cols / 2;		// 이미지 너비의 중심 x 좌표 계산
	int height_center = (*(Mat*)userdata).rows / 2;		// 이미지 높이의 중심 y 좌표 계산
	Point center = Point(width_center, height_center);	// 이미지 중심점 설정
	cout << "트랙바 위치 : " << pos << endl;			// 현재 트랙바 위치 출력
	circle(*(Mat*)userdata, center, pos, Scalar(0, 255, 0), 5);
	// 이미지 중심에 반지름 pos, 초록색(BGR: 0,255,0), 두께 5인 원 그리기
}
```

---

### main()

이미지를 불러와 트랙바를 생성하고, 트랙바 변경 시 draw_circle 콜백을 호출한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("Lenna");
	createTrackbar("Trackbar", "Lenna", 0, 100, draw_circle, &img);
	// 0~100 범위의 트랙바 생성, 값 변경 시 draw_circle 콜백 호출, 이미지 주소를 userdata로 전달
	while (true) {
		imshow("Lenna", img);
		if (waitKey(10) == 'q') break;	// 'q': 종료
	}
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/58209525-cce2-408e-a671-770b054d5f4f)

## 과제 2

트랙바로 도형 색상을 선택하고 마우스 드래그로 해당 색상의 사각형을 그리는 프로그램이다.

---

### select_shape()

트랙바 위치 값을 전역 변수에 저장하여 그릴 도형 종류를 선택한다.

```cpp
void select_shape(int pos, void* userdata) {
	shape_pos = pos;	// 트랙바 위치를 전역 변수에 저장하여 도형 종류 선택
}
```

---

### draw_shape()

마우스 드래그(좌클릭~해제) 시 선택된 색상으로 사각형을 그린다.

```cpp
void draw_shape(int event, int x, int y, int flags, void* userdata) {
	static Point ptOld;		// 드래그 시작점 (static: 함수 호출 간 유지)
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);	// 좌클릭: 드래그 시작점 저장
	case EVENT_LBUTTONUP:
		Point ptNew = Point(x, y);	// 좌클릭 해제: 드래그 끝점 저장
		if (shape_pos == 0) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(255, 0, 0), 1);
		// shape_pos == 0: 파란색(BGR: 255,0,0) 테두리 사각형 그리기
		else if(shape_pos == 1) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(0, 255, 0), 1);
		// shape_pos == 1: 초록색(BGR: 0,255,0) 테두리 사각형 그리기
		else if(shape_pos == 2) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(0, 0, 255), 1);
		// shape_pos == 2: 빨간색(BGR: 0,0,255) 테두리 사각형 그리기
		else if(shape_pos == 3) rectangle(*(Mat*)userdata, Rect(ptOld, ptNew), Scalar(255, 255, 255), -1);
		// shape_pos == 3: 흰색(BGR: 255,255,255)으로 채운 사각형 그리기 (지우개 효과)
	}
}
```

---

### main()

흰색 이미지를 생성하고 마우스 콜백과 트랙바를 함께 등록한다.

```cpp
int main(void) {
	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));	// 500x500 크기의 흰색 3채널 이미지 생성
	namedWindow("src");
	setMouseCallback("src", draw_shape, &img);			// 마우스 콜백 등록, 이미지 주소를 userdata로 전달
	createTrackbar("Trackbar", "src", 0, 3, select_shape);
	// 0~3 범위의 트랙바 생성, 값 변경 시 select_shape 콜백 호출
	while (true) {
		imshow("src", img);
		if (waitKey(10) == 'q') break;	// 'q': 종료
	}
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/a59e083d-6b15-4689-811d-3cb62f8bafea)
