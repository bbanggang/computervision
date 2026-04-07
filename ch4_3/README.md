# ch 4-3 OpenCV 주요 기능

## 과제 1

흰색 배경 이미지에 사각형과 그 안에 X자 대각선을 `line()`으로 그려 출력하는 프로그램이다.

---

### `DrawRectandTiledCross()`

이미지의 1/4 ~ 3/4 영역에 사각형 4변과 대각선 2개를 검은색으로 그린다.

```cpp
void DrawRectandTiledCross(Mat& img) {
	line(img, Point(img.cols / 4, img.rows / 4), Point(img.cols * 3 / 4, img.rows / 4), 0);		// 사각형 상단 변
	line(img, Point(img.cols / 4, img.rows * 3 / 4), Point(img.cols * 3 / 4, img.rows * 3 / 4), 0);	// 사각형 하단 변
	line(img, Point(img.cols / 4, img.rows / 4), Point(img.cols / 4, img.rows * 3 / 4), 0);		// 사각형 좌측 변
	line(img, Point(img.cols * 3 / 4, img.rows / 4), Point(img.cols * 3 / 4, img.rows * 3 / 4), 0);	// 사각형 우측 변
	line(img, Point(img.cols / 4, img.rows / 4), Point(img.cols * 3 / 4, img.rows * 3 / 4), 0);	// 좌상 → 우하 대각선
	line(img, Point(img.cols / 4, img.rows * 3 / 4), Point(img.cols * 3 / 4, img.rows / 4), 0);	// 좌하 → 우상 대각선
}
```

---

### `main()`

흰색 이미지를 생성하고 `DrawRectandTiledCross()`를 호출하여 결과를 출력한다.

```cpp
int main(void) {
	Mat img(400, 400, CV_8UC1, 255);			// 400x400 크기의 흰색(255) 그레이스케일 이미지 생성
	if (img.empty()) {							// 이미지 생성 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawRectandTiledCross(img);					// 사각형과 X자 대각선 그리기
	imshow("src", img);							// 결과 이미지 출력
	waitKey(0);									// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행 결과
![image](https://github.com/user-attachments/assets/f33a5fd6-dec9-4543-8411-5505f1085c7d)


## 과제 2

컬러 이미지에 `line()`을 사용하여 이미지를 4등분하는 흰색 격자선을 그려 출력하는 프로그램이다.

---

### `DrawGridLine()`

이미지를 가로·세로 각각 4등분하는 위치에 `line()`으로 흰색 격자선 3줄씩 그린다.

```cpp
void DrawGridLine(Mat& img) {
	for (int i = 0; i < 3; i++) {																		// 세로 격자선 3줄
		line(img, Point(img.cols * (i + 1) / 4, 0), Point(img.cols * (i + 1) / 4, img.rows), Scalar(255, 255, 255));	// 열 방향 1/4, 2/4, 3/4 위치에 세로선 그리기
	}
	for (int i = 0; i < 3; i++) {																		// 가로 격자선 3줄
		line(img, Point(0, img.rows * (i + 1) / 4), Point(img.cols, img.rows * (i + 1) / 4), Scalar(255, 255, 255));	// 행 방향 1/4, 2/4, 3/4 위치에 가로선 그리기
	}
}
```

---

### `main()`

이미지를 불러와 `DrawGridLine()`을 호출하여 격자선을 그린 뒤 출력한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawGridLine(img);								// 흰색 격자선 그리기
	imshow("Line", img);							// 격자선이 그려진 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행 결과
![image](https://github.com/user-attachments/assets/c94ea6fd-292c-4aa8-84d5-5230b7a437c8)


## 과제 3

흰색 배경 이미지에 사각형과 원을 검은색으로 그려 출력하는 프로그램이다.

---

### `DrawRectandCircle()`

이미지 중앙 영역에 사각형과 원을 `rectangle()`, `circle()`로 그린다.

```cpp
void DrawRectandCircle(Mat& img) {
	Rect rect(Point(img.cols / 4, img.rows / 4), Size(img.cols / 2, img.rows / 2));	// 좌측 상단 (1/4, 1/4), 크기 (1/2, 1/2)인 사각형 영역 정의
	rectangle(img, rect, 0);							// 정의된 영역에 검은색 사각형 그리기
	circle(img, Point(200, 200), 100, 0);				// 중심 (200, 200), 반지름 100인 검은색 원 그리기
}
```

---

### `main()`

흰색 이미지를 생성하고 `DrawRectandCircle()`을 호출하여 결과를 출력한다.

```cpp
int main(void) {
	Mat img(400, 400, CV_8UC1, 255);				// 400x400 크기의 흰색(255) 그레이스케일 이미지 생성
	if (img.empty()) {								// 이미지 생성 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawRectandCircle(img);							// 사각형과 원 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행 결과
![image](https://github.com/user-attachments/assets/0db25bf6-8f74-4925-860f-2216d0113892)


## 과제 4

컬러 이미지에 파란색 원을 `circle()`로 그려 출력하는 프로그램이다.

---

### `DrawCircle()`

지정한 중심과 반지름으로 파란색 원을 그린다.

```cpp
void DrawCircle(Mat& img) {
	circle(img, Point(280, 240), 185, Scalar(255, 0, 0), 2);	// 중심 (280, 240), 반지름 185, 파란색(BGR), 두께 2인 원 그리기
}
```

---

### `main()`

이미지를 불러와 `DrawCircle()`을 호출하여 원을 그린 뒤 출력한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawCircle(img);								// 파란색 원 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행 결과
![image](https://github.com/user-attachments/assets/0cfe19b6-49bb-41d6-ba51-2298f11b83fe)


## 과제 5

이미지를 파랑·초록·빨강 3개의 구역으로 나누고 각 구역에 사각형·원·X자를 흰색으로 그려 출력하는 프로그램이다.

---

### `DrawShape()`

`type` 값에 따라 ROI 영역에 사각형(0), 원(1), X자(2) 중 하나를 흰색으로 그린다.

```cpp
void DrawShape(Mat& roi, int type) {
	int w = roi.cols;
	int h = roi.rows;
	int margin = 50; 						// 도형과 영역 경계 사이의 여백
	Scalar white(255, 255, 255); 			// 도형 색상: 흰색
	int thickness = 5;						// 도형 선 두께
	if (type == 0) { 						// type 0: 사각형
		rectangle(roi, Rect(margin, margin, w - 2 * margin, h - 2 * margin), white, thickness);
	}
	else if (type == 1) { 					// type 1: 원
		circle(roi, Point(w / 2, h / 2), min(w, h) / 2 - margin, white, thickness);	// ROI 중심에 내접하는 원
	}
	else if (type == 2) { 					// type 2: X자 대각선
		line(roi, Point(margin, margin), Point(w - margin, h - margin), white, thickness);		// 좌상 → 우하 대각선
		line(roi, Point(w - margin, margin), Point(margin, h - margin), white, thickness);		// 우상 → 좌하 대각선
	}
}
```

---

### `DrawColorBox()`

이미지를 3등분하여 각 구역을 파랑·초록·빨강으로 채우고 `DrawShape()`를 호출한다.

```cpp
void DrawColorBox(Mat& img) {
	int num_sections = 3;								// 구역 수
	int section_w = img.cols / num_sections;			// 각 구역의 너비
	vector<Scalar> colors = { Scalar(255, 0, 0), Scalar(0, 255, 0), Scalar(0, 0, 255) };	// 파랑, 초록, 빨강
	for (int i = 0; i < num_sections; i++) {
		Rect rect_roi(i * section_w, 0, section_w, img.rows);	// i번째 구역의 ROI 정의
		Mat roi = img(rect_roi);							// 원본 이미지에서 ROI 참조
		roi.setTo(colors[i % colors.size()]);				// 해당 구역을 색상으로 채우기
		DrawShape(roi, i);									// 구역 인덱스에 맞는 도형 그리기 (0: 사각형, 1: 원, 2: X자)
	}
}
```

---

### `main()`

검은색 이미지를 생성하고 `DrawColorBox()`를 호출하여 결과를 출력한다.

```cpp
int main() {
	Mat img(200, 600, CV_8UC3, Scalar(0, 0, 0));	// 200x600 크기의 검은색 3채널 이미지 생성
	DrawColorBox(img);								// 색상 구역 및 도형 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행 결과
![image](https://github.com/user-attachments/assets/9281ad79-47ab-4aa3-864e-ea6b6c92d299)


## 과제 6

컬러 이미지에 `putText()`로 텍스트를 그려 출력하는 프로그램이다.

---

### `DrawText()`

이미지에 이탤릭체 노란색 텍스트를 지정한 위치에 그린다.

```cpp
void DrawText(Mat& img) {
	putText(img, "Hello, Lenna", Point(120, 80), FONT_ITALIC, 1, Scalar(0, 255, 255), 2);
	// "Hello, Lenna" 문자열을 (120, 80) 위치에 이탤릭 폰트, 크기 1, 노란색(BGR: 0,255,255), 두께 2로 그리기
}
```

---

### `main()`

이미지를 불러와 `DrawText()`를 호출하여 텍스트를 그린 뒤 출력한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	DrawText(img);									// 텍스트 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행 결과
![image](https://github.com/user-attachments/assets/d7b41bab-4d28-409a-9942-7d997af82858)


## 과제 7

흰색 이미지에 숫자를 텍스트로 표시하며 `s` 키로 카운트를 시작하고, `r` 키로 초기화, `q` 키로 종료하는 타이머 프로그램이다.

---

### `TimeCount()`

키 입력에 따라 카운트 시작·초기화·종료를 제어하며 1초 간격으로 숫자를 갱신하여 출력한다.

```cpp
void TimeCount(Mat& img) {
	int count = 0;							// 현재 카운트 값
	bool isCount = false;					// 카운트 진행 여부 플래그 (초기값: 정지)
	while (true) {
		putText(img, to_string(count), Point(100, 200), FONT_ITALIC, 5, Scalar(0), 2);
		// 현재 카운트 값을 (100, 200) 위치에 이탤릭 폰트, 크기 5, 검은색, 두께 2로 출력
		if (isCount) count++;				// 카운트 진행 중이면 1 증가
		imshow("src", img);					// 현재 프레임 출력
		img.setTo(255);						// 다음 프레임을 위해 이미지를 흰색으로 초기화 (텍스트 잔상 방지)
		int key = waitKey(1000);			// 1초 대기, 그 사이 키 입력 감지
		if (key == 's') isCount = true;		// 's' 키: 카운트 시작
		if (key == 'r') {
			count = 0;						// 'r' 키: 카운트 0으로 초기화
			waitKey(1000);					// 초기화 후 1초 추가 대기
		}
		if (key == 'q') break;				// 'q' 키: 종료
	}
}
```

---

### `main()`

흰색 이미지를 생성하고 `TimeCount()`를 호출한다.

```cpp
int main(void) {
	Mat img(300, 300, CV_8UC1, 255);		// 300x300 크기의 흰색(255) 그레이스케일 이미지 생성
	if (img.empty()) {						// 이미지 생성 실패 시
		cerr << "Image open failed" << endl;
		return -1;
	}
	TimeCount(img);							// 타이머 실행
	return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/56ff774b-b3a1-40e3-b23b-c5ba1850d3d1)


## 과제 8

## 전체 프로그램 동작 설명

5x5 격자 위에서 파란색 블록을 키 입력(`l`, `r`, `u`, `d`)으로 이동시키는 프로그램이다. 경계를 벗어나면 경고 메시지를 출력하고, `q` 또는 `Q` 키를 누르면 종료된다.

---

### `DrawGrid()`

지정한 분할 수에 따라 이미지에 검은색 격자선을 그린다.

```cpp
void DrawGrid(Mat& img, int sections) {
    int step_w = img.cols / sections;       // 열 방향 격자 간격
    int step_h = img.rows / sections;       // 행 방향 격자 간격
    for (int i = 1; i < sections; i++) {
        line(img, Point(i * step_w, 0), Point(i * step_w, img.rows), Scalar(0, 0, 0), 1);  // 세로선 그리기
        line(img, Point(0, i * step_h), Point(img.cols, i * step_h), Scalar(0, 0, 0), 1);  // 가로선 그리기
    }
}
```

---

### `SetBlueBox()`

격자 좌표 `(x, y)` 위치에 `size` 크기의 파란색 블록을 그린다.

```cpp
void SetBlueBox(Mat& img, int x, int y, int size) {
    int step_w = img.cols / 5;                              // 격자 한 칸의 너비
    int step_h = img.rows / 5;                              // 격자 한 칸의 높이
    Rect roi_rect(x * step_w, y * step_h, size * step_w, size * step_h);   // 블록 영역 계산
    Mat roi = img(roi_rect);                                // 해당 영역 ROI 참조
    roi.setTo(Scalar(255, 0, 0));                           // 파란색으로 채우기
}
```

---

### `main()`

매 프레임마다 이미지를 새로 생성하고 격자와 블록을 그린 뒤, 키 입력으로 블록 위치를 갱신한다.

```cpp
int main(void) {
    int grid_cnt = 5;           // 격자 분할 수 (5x5)
    int box_size = 1;           // 블록 크기 (1칸)
    int cur_x = 2, cur_y = 2;  // 블록 초기 위치 (격자 중앙)
    while (true) {
        Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));  // 매 프레임 흰색 이미지 새로 생성
        DrawGrid(img, grid_cnt);                            // 격자선 그리기
        SetBlueBox(img, cur_x, cur_y, box_size);            // 현재 위치에 파란색 블록 그리기
        imshow("src", img);
        int key = waitKey(0);                               // 키 입력 대기
        if (key == 'q' || key == 'Q') break;               // 'q'/'Q': 종료
        int next_x = cur_x;
        int next_y = cur_y;
        if (key == 'l') next_x--;      // 'l': 좌측 이동
        else if (key == 'r') next_x++; // 'r': 우측 이동
        else if (key == 'u') next_y--; // 'u': 위쪽 이동
        else if (key == 'd') next_y++; // 'd': 아래쪽 이동
        if (next_x >= 0 && next_x <= (grid_cnt - box_size) &&
            next_y >= 0 && next_y <= (grid_cnt - box_size)) {  // 격자 경계 내에 있는지 확인
            cur_x = next_x;
            cur_y = next_y;
        }
        else {
            cout << "경계 경고: 더 이상 움직일 수 없습니다." << endl;  // 경계 초과 시 경고 출력
        }
    }
    return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/6e85f493-b67d-4082-9cd0-4a2921e89c4d)


## 과제 9

흰색 이미지에서 키 입력(`l`, `r`, `u`, `d`)으로 현재 위치를 이동시키며 이동 경로를 검은색 선으로 그려나가는 프로그램이다. 화면 경계를 벗어나면 경고 메시지를 출력하고, `q` 또는 `Q` 키를 누르면 종료된다.

---

### `main()`

현재 위치에서 다음 위치로 이동 시 `line()`으로 경로를 그리고, 경계 조건을 검사하여 이동 여부를 결정한다.

```cpp
int main(void) {
    Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));      // 500x500 흰색 이미지 생성
    Point curr_pos(img.cols / 2, img.rows / 2);             // 시작 위치: 이미지 중앙 (250, 250)
    int step = 50;                                          // 한 번 이동 시 픽셀 단위 이동량
    cout << "프로그램 시작" << endl;
    while (true) {
        imshow("Line Drawing", img);
        int key = waitKey(0);                               // 키 입력 대기
        if (key == 'q' || key == 'Q') break;               // 'q'/'Q': 종료
        Point next_pos = curr_pos;
        if (key == 'l') next_pos.x -= step;     // 'l': 좌측으로 step만큼 이동
        else if (key == 'r') next_pos.x += step; // 'r': 우측으로 step만큼 이동
        else if (key == 'u') next_pos.y -= step; // 'u': 위쪽으로 step만큼 이동
        else if (key == 'd') next_pos.y += step; // 'd': 아래쪽으로 step만큼 이동
        else continue;                                      // 그 외 키는 무시하고 다음 반복으로
        if (next_pos.x >= 0 && next_pos.x <= img.cols &&
            next_pos.y >= 0 && next_pos.y <= img.rows) {   // 이미지 경계 내에 있는지 확인
            line(img, curr_pos, next_pos, Scalar(0, 0, 0), 2, LINE_AA);    // 현재 위치에서 다음 위치까지 안티앨리어싱 선 그리기
            curr_pos = next_pos;                            // 현재 위치 갱신
        }
        else {
            cout << "경고: 화면 범위를 벗어날 수 없습니다." << endl;
        }
    }
    return 0;
}
```

### 실행 결과
[video](https://github.com/user-attachments/assets/59e2e11d-3961-474c-bf48-8e7d76790013)

