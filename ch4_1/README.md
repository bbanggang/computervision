# ch 4-1 OpenCV 주요 기능

## 과제 1

**API (Application Programming Interface)**

소프트웨어 간의 상호작용을 위한 규약 및 인터페이스의 집합이다.
운영체제, 라이브러리, 서비스 등이 제공하는 기능을 외부 프로그램에서 사용할 수 있도록 정의된 함수, 프로토콜, 도구의 모음이다.
개발자는 내부 구현을 알지 않아도 API를 통해 해당 기능을 호출하고 활용할 수 있다.
OpenCV도 이미지 처리 기능을 외부에서 사용할 수 있도록 API 형태로 제공된다.

---

**V4L (Video4Linux)** 

리눅스 커널에 내장된 비디오 캡처 장치용 API이다.
웹캠, TV 튜너 등 비디오 입력 장치를 리눅스 환경에서 제어하기 위한 드라이버 인터페이스를 제공한다.
현재는 개선된 버전인 V4L2(Video4Linux2)가 주로 사용되며, OpenCV에서 리눅스 환경의 카메라 입력을 처리할 때 내부적으로 V4L2를 사용한다.

---

**FFMPEG**

오디오 및 비디오를 녹화, 변환, 스트리밍할 수 있는 오픈소스 멀티미디어 프레임워크이다.
다양한 코덱과 컨테이너 포맷을 지원하며, 명령줄 도구와 라이브러리(libavcodec, libavformat 등) 형태로 제공된다.
OpenCV는 동영상 파일 읽기/쓰기 시 내부적으로 FFMPEG를 사용하며, 빌드 시 FFMPEG 지원 여부에 따라 처리 가능한 동영상 포맷이 달라진다.
Windows, Linux, macOS 등 다양한 플랫폼에서 사용 가능하다.

---

**DirectShow**

Microsoft가 Windows 환경에서 멀티미디어 스트리밍을 처리하기 위해 개발한 API이다.
COM(Component Object Model) 기반의 필터 그래프 구조로 동작하며, 각 필터가 파이프라인 형태로 연결되어 캡처, 디코딩, 렌더링 등을 처리한다.
OpenCV에서 Windows 환경의 카메라 입력을 처리할 때 사용할 수 있는 백엔드 중 하나이다.
현재는 MSMF로 대체되는 추세이나 여전히 레거시 장치 호환을 위해 사용된다.

---

**MSMF (Microsoft Media Foundation)**

DirectShow의 후속으로 Microsoft가 Windows Vista 이후 도입한 멀티미디어 처리 API이다.
하드웨어 가속, H.264 등 최신 코덱 지원, 저전력 처리에 최적화되어 있으며, DirectShow보다 향상된 성능과 안정성을 제공한다.
OpenCV에서 Windows 환경의 카메라 및 동영상 입력 처리 시 기본 백엔드로 사용된다.
`VideoCapture` 생성 시 `CAP_MSMF` 플래그로 명시적으로 지정할 수 있다.

---

**GStreamer**

크로스 플랫폼 멀티미디어 프레임워크로, 파이프라인 기반의 플러그인 구조로 동작한다.
오디오/비디오의 캡처, 인코딩, 디코딩, 스트리밍, 재생 등 다양한 멀티미디어 작업을 플러그인 조합으로 유연하게 처리할 수 있다.
Linux 환경에서 주로 사용되며 Windows, macOS에서도 동작한다.
OpenCV에서 `VideoCapture` 및 `VideoWriter`의 백엔드로 사용할 수 있으며, RTSP 스트림 등 네트워크 영상 처리에 유용하다.
`VideoCapture` 생성 시 `CAP_GSTREAMER` 플래그로 명시적으로 지정할 수 있다.

## 과제 2

웹캠 프레임을 실시간으로 캡처하여 원본과 밝기를 높인 프레임을 동시에 출력하는 프로그램이다. `ESC` 키를 누르면 종료된다.

---

### `main()`

웹캠 프레임을 반복 캡처하며 원본과 밝기 증가 프레임을 각각 별도 창에 출력한다.

```cpp
int main(void) {
	VideoCapture cap(0);					// 기본 웹캠(인덱스 0) 열기
	if (!cap.isOpened()) {					// 웹캠 열기 실패 시
		cerr << "Camera open failed" << endl;
		return -1;
	}
	Mat frame;
	while (true) {
		cap >> frame;						// 웹캠에서 프레임 캡처
		if (frame.empty()) {				// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		Mat bright_frame = frame + Scalar(100, 100, 100);	// BGR 각 채널에 100을 더해 밝기 증가 (255 초과 시 자동 포화 처리)
		imshow("origin", frame);			// 원본 프레임 출력
		imshow("bright", bright_frame);		// 밝기 증가된 프레임 출력
		if (waitKey(10) == 27) break;		// 10ms 대기 후 ESC(27) 입력 시 종료
	}
	return 0;
}
```

### 실행 결과
[work1](https://github.com/user-attachments/assets/8b80ccc9-6a20-4e99-bbbe-a6641fc25b13)



## 과제 3

웹캠으로부터 프레임을 실시간으로 출력하며, `s` 키를 누를 때마다 현재 프레임을 순번이 붙은 파일명으로 저장하는 프로그램이다. `q` 또는 `Q` 키를 누르면 종료된다.

---

### `main()`

웹캠 프레임을 반복 캡처하며 키 입력에 따라 파일 저장 또는 종료를 처리한다.

```cpp
int main(void) {
	VideoCapture cap(0);					// 기본 웹캠(인덱스 0) 열기
	if (!cap.isOpened()) {					// 웹캠 열기 실패 시
		cerr << "Camera open failed" << endl;
		return -1;
	}
	Mat frame;
	int saved_count = 0;					// 저장된 파일 수 (파일명 순번에 사용)
	string filename;
	while (true) {
		cap >> frame;						// 웹캠에서 프레임 캡처
		if (frame.empty()) {				// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		imshow("frame", frame);				// 현재 프레임 출력
		int key = waitKey(10);				// 10ms 대기, 그 사이 키 입력 감지
		if (key == 's') {					// 's' 키 입력 시 현재 프레임 저장
			if (saved_count < 10) filename = "frame0" + to_string(saved_count) + ".jpg";	// 한 자리 수: "frame00.jpg" ~ "frame09.jpg"
			else  filename = "frame" + to_string(saved_count) + ".jpg";						// 두 자리 수: "frame10.jpg" ~
			if (imwrite(filename, frame)) {		// 파일 저장 성공 시
				cout << "Saved : " << filename << endl;		// 저장된 파일명 콘솔 출력
				saved_count++;				// 저장 횟수 증가
			}
		}
		if (key == 'Q' || key == 'q') break;	// 'q' 또는 'Q' 입력 시 종료
	}
}
```

### 실행 결과
[work2](https://youtu.be/2xFJ8j7kVMc)

## 과제 4

웹캠으로부터 프레임을 실시간으로 읽어 화면 중앙에 빨간색 십자선을 그려 출력하는 프로그램이다. `q` 키를 누르면 종료된다.

---

### `DrawRedLine()`

프레임의 가로 중앙과 세로 중앙에 빨간색 십자선을 화소 접근 방식으로 그린다.

```cpp
void DrawRedLine(Mat &frame) {
	for (int i = 0; i < frame.rows; i++) {					// 모든 행을 순회
		frame.at<Vec3b>(i, frame.cols / 2) = Vec3b(0, 0, 255);	// 열 방향 중앙에 빨간색 세로선 그리기
	}
	for (int i = 0; i < frame.cols; i++) {					// 모든 열을 순회
		frame.at<Vec3b>(frame.rows / 2, i) = Vec3b(0, 0, 255);	// 행 방향 중앙에 빨간색 가로선 그리기
	}
}
```

---

### `main()`

웹캠을 열어 프레임을 반복 캡처하고 십자선을 그려 출력한다.

```cpp
int main(void) {
	VideoCapture cap(0);					// 기본 웹캠(인덱스 0) 열기
	if (!cap.isOpened()) {					// 웹캠 열기 실패 시
		cerr << "Camera open failed" << endl;
		return -1;
	}
	Mat frame;
	while (true) {
		cap >> frame;						// 웹캠에서 프레임 캡처
		if (frame.empty()) {				// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		DrawRedLine(frame);					// 캡처한 프레임에 빨간색 십자선 그리기
		imshow("frame", frame);				// 십자선이 그려진 프레임 출력
		if (waitKey(10) == 'q') break;		// 10ms 대기 후 'q' 입력 시 종료
	}
}
```

### 실행 결과
[work3](https://github.com/user-attachments/assets/3810a4fa-56c4-48d8-8f8f-4802b7502452)
