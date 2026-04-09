# ch 4-4 OpenCV 주요 기능

## 과제 1

이미지를 출력하고 키 입력(`l`, `c`, `t`)에 따라 가로선·원·텍스트를 순서대로 그려 출력하는 프로그램이다.

---

### DrawText()

이미지에 이탤릭체 노란색 텍스트를 지정한 위치에 그린1다.

```cpp
void DrawText(Mat& img) {
	putText(img, "Hello, Lenna", Point(120, 80), FONT_ITALIC, 1, Scalar(0, 255, 255), 2);
	// "Hello, Lenna" 문자열을 (120, 80) 위치에 이탤릭 폰트, 크기 1, 노란색(BGR: 0,255,255), 두께 2로 그리기
}
```

---

### DrawCircle()

지정한 중심과 반지름으로 빨간색 원을 그린다.

```cpp
void DrawCircle(Mat& img) {
	circle(img, Point(280, 280), 160, Scalar(0, 0, 255), 2);
	// 중심 (280, 280), 반지름 160, 빨간색(BGR: 0,0,255), 두께 2인 원 그리기
}
```

---

### DrawLine()

지정한 두 점 사이에 흰색 가로선을 그린다.

```cpp
void DrawLine(Mat& img) {
	line(img, Point(100, 430),Point(440,430), Scalar(255, 255, 255), 2);
	// (100, 430) ~ (440, 430) 사이에 흰색(BGR: 255,255,255), 두께 2인 가로선 그리기
}
```

---

### main()

이미지를 불러와 키 입력에 따라 도형·텍스트를 누적하여 그린다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	int key;
	while (true) {
		imshow("img", img);				// 현재 이미지 출력
		key = waitKey();				// 키 입력 대기
		if (key == 'q') break;			// 'q': 종료
		else if (key == 'l') DrawLine(img);		// 'l': 가로선 그리기
		else if (key == 'c') DrawCircle(img);	// 'c': 빨간색 원 그리기
		else if (key == 't') DrawText(img);		// 't': 텍스트 그리기
		else {
			cout << "잘못된 입력입니다. l(line), c(circle), t(text), q(quit)" << endl;
			continue;
		}
	}
	destroyAllWindows();				// 모든 창 닫기
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/ded6d29d-c040-4d86-98df-9b7f23f05d1b)


## 과제 2

마우스 이벤트(좌클릭·해제·이동)가 발생할 때마다 누적 횟수를 콘솔에 출력하는 프로그램이다.

---

### on_mouse()

이벤트 종류에 따라 해당 카운트를 증가시키고 콘솔에 출력한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	switch (event) {
	case EVENT_LBUTTONUP:
		LButtonUp_count++;
		cout << "EVENT_LBUTTONUP" << LButtonUp_count << endl;		// 좌클릭 해제 횟수 출력
		break;
	case EVENT_LBUTTONDOWN:
		LButtonDown_count++;
		cout << "EVENT_LBUTTONDOWN" << LButtonDown_count << endl;	// 좌클릭 횟수 출력
		break;
	case EVENT_MOUSEMOVE:
		MouseMove_count++;
		cout << "EVENT_MOUSEMOVE" << MouseMove_count << endl;		// 마우스 이동 횟수 출력
		break;
	default:
		break;
	}
}
```

---

### main()

이미지를 불러와 마우스 콜백을 등록하고 이벤트를 감지한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse);	// 마우스 콜백 함수 등록
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);				// 100ms 대기
		if (key == 'q') break;			// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/6f5823f7-9eb5-440c-adf6-03f7ca5c6d13)


## 과제 3

그레이스케일 이미지에서 마우스 좌클릭 위치의 좌표와 화소값을 콘솔에 출력하는 프로그램이다.

---

### on_mouse()

좌클릭 이벤트 발생 시 `userdata`로 전달받은 이미지에서 해당 좌표의 화소값을 읽어 출력한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	if (event == EVENT_LBUTTONDOWN) {
		Mat& img = *static_cast<Mat*>(userdata);	// 강제 형변환인 C_Style보다 static_cast가 권장됨
		int value = img.at<uchar>(y, x);			// uchar 자료형에 대해 문자 출력이 되지 않도록 int 자료형에 저장
		cout << "좌표: " << Point(x, y) << ", 화소값: " << value << endl;	// 좌표와 화소값 출력
	}
}
```

---

### main()

이미지를 그레이스케일로 불러와 이미지 주소를 userdata로 전달하며 마우스 콜백을 등록한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일 모드로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse, &img);	// 이미지 주소를 userdata로 전달하며 마우스 콜백 등록
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);				// 100ms 대기
		if (key == 'q') break;			// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/4c118b61-1a93-4e6e-84af-831202e2e539)


## 과제 4

컬러 이미지에서 마우스 좌클릭 위치의 좌표와 BGR 화소값을 콘솔에 출력하는 프로그램이다.

---

### on_mouse()

좌클릭 이벤트 발생 시 `userdata`로 전달받은 이미지에서 해당 좌표의 BGR 화소값을 읽어 출력한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	if (event == EVENT_LBUTTONDOWN) {
		Mat& img = *static_cast<Mat*>(userdata);	// 강제 형변환인 C_Style보다 static_cast가 권장됨
		cout << "좌표: " << Point(x, y) << ", 화소값(B, G, R): " << img.at<Vec3b>(y, x) << endl;
		// 클릭한 좌표의 BGR 화소값 출력
	}
}
```

---

### main()

이미지를 컬러로 불러와 이미지 주소를 userdata로 전달하며 마우스 콜백을 등록한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {					// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse, &img);	// 이미지 주소를 userdata로 전달하며 마우스 콜백 등록
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);				// 100ms 대기
		if (key == 'q') break;			// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/fc506b4f-03f7-491e-9a6c-edc5724889a8)


## 과제 5

마우스 드래그(좌클릭 후 해제)로 선택한 영역을 ROI로 추출하여 별도 창에 출력하는 프로그램이다.

---

### on_mouse()

좌클릭 시 시작점을, 해제 시 끝점을 저장하고 두 점으로 ROI를 추출하여 출력한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	static Point ptOld, ptNew;			// 드래그 시작점과 끝점 저장 (static: 함수 호출 간 유지)
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);			// 좌클릭: 드래그 시작점 저장
		cout << "EVENT_LBUTTONDOWN: " << Point(x, y) << endl;
		break;
	case EVENT_LBUTTONUP:
		ptNew = Point(x, y);			// 좌클릭 해제: 드래그 끝점 저장
		cout << "EVENT_LBUTTONUP: " << Point(x, y) << endl;
		Mat roi_img = img(Rect(ptOld, ptNew));	// 시작점~끝점으로 ROI 추출
		imshow("roi_img", roi_img);		// ROI 이미지 출력
		waitKey(0);						// 키 입력 대기 (창 유지)
		break;
	}
}
```

---

### main()

전역 이미지를 불러와 마우스 콜백을 등록한다.

```cpp
int main(void) {
	img = imread("lenna.bmp");		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {				// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	namedWindow("img");
	setMouseCallback("img", on_mouse);	// 마우스 콜백 등록 (전역 변수 img 사용)
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);				// 100ms 대기
		if (key == 'q') break;			// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/3dad3c40-c156-4e70-b756-1f89bdf970e0)


## 과제 6

흰색 이미지에서 마우스 좌클릭 시 빨간색, 우클릭 시 파란색으로 이미지 전체 색상을 변경하는 프로그램이다.

---

### on_mouse()

좌클릭과 우클릭 이벤트에 따라 이미지 전체를 해당 색상으로 채운다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		img.setTo(Scalar(0, 0, 255));	// 좌클릭: 이미지 전체를 빨간색으로 변경
		break;
	case EVENT_RBUTTONDOWN:
		img.setTo(Scalar(255, 0, 0));	// 우클릭: 이미지 전체를 파란색으로 변경
		break;
	}
}
```

---

### main()

흰색 이미지를 생성하고 마우스 콜백을 등록한다.

```cpp
int main(void) {
	img = Mat(200, 400, CV_8UC3, Scalar(255, 255, 255));	// 200x400 크기의 흰색 3채널 이미지 생성
	namedWindow("img");
	setMouseCallback("img", on_mouse);	// 마우스 콜백 등록
	int key;
	while (true) {
		imshow("img", img);
		key = waitKey(100);				// 100ms 대기
		if (key == 'q') break;			// 'q': 종료
	}
	destroyAllWindows();
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/90fa2322-3158-43e4-b464-6dc21efe39b2)


## 과제 7

그레이스케일 이미지에 Red·Green·Blue 버튼 3개를 그리고, 클릭 시 해당 버튼을 반전 표시하며 오른쪽에 "색상 pressed" 메시지를 출력하는 프로그램이다.

---

### GetButtonIndex()

클릭한 좌표를 받아 어느 버튼에 해당하는지 인덱스를 반환한다.

```cpp
int GetButtonIndex(int x, int y) {
    if (x >= 0 && x <= 200) {				// x 좌표가 버튼 영역(0~200) 내에 있는 경우
        if (y >= 0 && y < 100) return 0;	// 첫 번째 버튼 (Red)
        if (y >= 100 && y < 200) return 1;	// 두 번째 버튼 (Green)
        if (y >= 200 && y < 300) return 2;	// 세 번째 버튼 (Blue)
    }
    return -1;								// 버튼 영역 외 클릭
}
```

---

### on_mouse()

좌클릭 시 버튼 인덱스를 저장하고, 해제 시 초기화한다.

```cpp
void on_mouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        clicked_idx = GetButtonIndex(x, y);	// 좌클릭: 해당 버튼 인덱스 저장
    }
    else if (event == EVENT_LBUTTONUP) {
        clicked_idx = -1;					// 좌클릭 해제: 선택 해제
    }
}
```

---

### DrawUI()

버튼 3개를 그리며 클릭된 버튼은 반전 표시하고 오른쪽에 메시지를 출력한다.

```cpp
void DrawUI(Mat& img) {
    for (int i = 0; i < 3; i++) {
        Rect rc(0, 100 * i, 200, 100);		// i번째 버튼 영역 (높이 100씩)

        if (i == clicked_idx) {				// 클릭된 버튼: 반전 표시
            rectangle(img, rc, 0, -1); 		// 검은색으로 채우기 (반전)
            putText(img, colors[i], Point(40, 60 + 100 * i), FONT_HERSHEY_COMPLEX, 1, 255, 2);
            // 흰색 텍스트로 버튼 레이블 출력

            string msg = colors[i] + " pressed";
            putText(img, msg, Point(220, 160), FONT_HERSHEY_COMPLEX, 0.7, 0, 1);
            // 오른쪽 영역에 "색상 pressed" 메시지 출력
        }
        else {								// 비클릭 버튼: 테두리만 표시
            rectangle(img, rc, 0, 2);		// 검은색 테두리 사각형
            putText(img, colors[i], Point(40, 60 + 100 * i), FONT_HERSHEY_COMPLEX, 1, 0, 2);
            // 검은색 텍스트로 버튼 레이블 출력
        }
    }
}
```

---

### main()

매 프레임 새로운 흰색 이미지를 생성하고 DrawUI()를 호출하여 버튼을 그린다.

```cpp
int main(void) {
    namedWindow("img");
    setMouseCallback("img", on_mouse);	// 마우스 콜백 등록

    while (true) {
        img = Mat(300, 500, CV_8UC1, 255);	// 매 프레임 흰색 이미지 새로 생성
        DrawUI(img);						// UI 버튼 그리기
        imshow("img", img);
        if (waitKey(10) == 'q') break; 		// 'q': 종료
    }

    destroyAllWindows();
    return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/3984f2ae-bef4-4c35-87c3-223a95b145f1)