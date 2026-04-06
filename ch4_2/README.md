# ch 4-2 OpenCV 주요 기능

## 과제 1

**MPEG4**

ISO/IEC 산하 MPEG(Moving Picture Experts Group)이 제정한 디지털 멀티미디어 압축 표준이다.
영상, 음성, 그래픽 등을 효율적으로 압축하기 위한 다양한 프로파일과 레벨을 정의하며, 인터넷 스트리밍과 모바일 환경에 최적화되어 있다.
MPEG4 Part 2는 기존 동영상 압축 기술이고, MPEG4 Part 10은 H.264(AVC)로 발전하였다.
OpenCV에서 `VideoWriter`로 동영상 저장 시 FourCC 코드 `MP4V`로 지정하여 사용할 수 있다.

---

**DivX**

MPEG4 Part 2 기반의 상용 비디오 코덱으로, 2000년대 초반 고화질 영상을 작은 용량으로 압축하는 기술로 널리 보급되었다.
DVD 수준의 화질을 인터넷으로 배포 가능한 크기로 압축할 수 있어 당시 큰 인기를 끌었다.
현재는 H.264, H.265 등 더 효율적인 코덱에 밀려 사용이 줄었으나, DivX Pro 등 상용 제품으로 여전히 유지되고 있다.
OpenCV에서 FourCC 코드 `DIVX`로 지정하여 사용할 수 있다.

---

**Xvid**

DivX와 동일하게 MPEG4 Part 2 기반의 오픈소스 비디오 코덱이다.
DivX가 상용화되자 이에 대응하여 개발된 무료 오픈소스 대안으로, DivX와 높은 호환성을 가진다.
라이선스 비용 없이 사용 가능하여 리눅스 환경 등에서 널리 활용되었다.
OpenCV에서 FourCC 코드 `XVID`로 지정하여 사용할 수 있다.

---

**H.264 (AVC, Advanced Video Coding)**

ITU-T와 ISO/IEC가 공동으로 제정한 고효율 비디오 압축 표준으로, MPEG4 Part 10이라고도 불린다.
MPEG4 Part 2 대비 동일 화질에서 약 50% 더 높은 압축 효율을 제공하며, Full HD 및 4K 영상 압축에 널리 사용된다.
유튜브, 넷플릭스 등 대부분의 스트리밍 서비스와 블루레이 디스크의 표준 코덱으로 채택되어 현재까지 가장 범용적으로 사용된다.
OpenCV에서 FourCC 코드 `avc1` 또는 `X264`로 지정하여 사용할 수 있다.

---

**H.265 (HEVC, High Efficiency Video Coding)**

H.264의 후속 표준으로 ITU-T와 ISO/IEC가 공동 제정하였으며, MPEG-H Part 2라고도 불린다.
H.264 대비 동일 화질에서 약 40~50% 더 높은 압축 효율을 제공하여 4K, 8K 초고화질 영상 처리에 적합하다.
압축 효율이 높은 반면 인코딩/디코딩 연산량이 많아 하드웨어 가속 지원이 중요하다.
넷플릭스, 애플 등이 4K 콘텐츠 배포에 적극 채택하고 있으며, OpenCV에서 FourCC 코드 `HEVC`로 지정하여 사용할 수 있다.

## 과제 2

동영상 파일을 읽어 각 프레임의 밝기를 높인 뒤 원본과 함께 화면에 출력하고, 밝기가 조정된 동영상을 새 파일로 저장하는 프로그램이다.

---

### `main()`

동영상을 프레임 단위로 읽어 밝기를 조정하고 `VideoWriter`로 저장한다.

```cpp
int main(void) {
	VideoCapture cap("stopwatch.avi");				// 동영상 파일 열기
	if (!cap.isOpened()) {							// 동영상 열기 실패 시
		cerr << "video open failed" << endl;
		return -1;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));		// 원본 동영상의 프레임 너비 가져오기
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));	// 원본 동영상의 프레임 높이 가져오기
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');	// 출력 동영상 코덱을 DIVX로 설정
	VideoWriter outputVideo("output.avi", fourcc, 30, Size(w, h));	// 30fps, 원본과 동일한 해상도로 출력 파일 생성
	if (!outputVideo.isOpened()) {					// 출력 파일 생성 실패 시
		cout << "File open failed!" << endl;
		return -1;
	}
	Mat frame, bright;
	while (true) {
		cap >> frame;								// 동영상에서 프레임 읽기
		if (frame.empty()) {						// 프레임 읽기 실패 또는 영상 종료 시
			cerr << "frame empty" << endl;
			break;
		}
		bright = frame + Scalar(100, 100, 100);		// BGR 각 채널에 100을 더해 밝기 증가 (255 초과 시 자동 포화 처리)
		outputVideo << bright;						// 밝기 조정된 프레임을 출력 파일에 저장
		imshow("frame", frame);						// 원본 프레임 출력
		imshow("bright", bright);					// 밝기 조정된 프레임 출력
		int key = waitKey(33);						// 약 30fps에 맞춰 33ms 대기, 키 입력 감지
		if (key == 'q' || key == 'Q') break;		// 'q' 또는 'Q' 입력 시 종료
	}
	return 0;
}
```

### 실행 결과
[video2](https://github.com/user-attachments/assets/a1517cda-ba03-425a-9968-aecdd5677ad4)



## 과제 3

동영상 파일을 읽어 각 프레임에 빨간색 십자선을 그린 뒤 원본과 함께 화면에 출력하고, 십자선이 추가된 동영상을 새 파일로 저장하는 프로그램이다.

---

### `DrawRedLine()`

프레임의 가로 중앙과 세로 중앙에 빨간색 십자선을 화소 접근 방식으로 그린다.

```cpp
void DrawRedLine(Mat& frame) {
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

동영상을 프레임 단위로 읽어 원본을 복사한 뒤 십자선을 그려 `VideoWriter`로 저장한다.

```cpp
int main(void) {
	VideoCapture cap("stopwatch.avi");				// 동영상 파일 열기
	if (!cap.isOpened()) {							// 동영상 열기 실패 시
		cerr << "video open failed" << endl;
		return -1;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));		// 원본 동영상의 프레임 너비 가져오기
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));	// 원본 동영상의 프레임 높이 가져오기
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');	// 출력 동영상 코덱을 DIVX로 설정
	VideoWriter outputVideo("RedLineVideo.avi", fourcc, 30, Size(w, h));	// 30fps, 원본과 동일한 해상도로 출력 파일 생성
	if (!outputVideo.isOpened()) {					// 출력 파일 생성 실패 시
		cout << "File open failed!" << endl;
		return -1;
	}
	Mat frame, RedLineVideo;
	while (true) {
		cap >> frame;								// 동영상에서 프레임 읽기
		if (frame.empty()) {						// 프레임 읽기 실패 또는 영상 종료 시
			cerr << "frame empty" << endl;
			break;
		}
		RedLineVideo = frame.clone();				// 원본 프레임을 독립 복사 (원본 보존)
		DrawRedLine(RedLineVideo);					// 복사본에 빨간색 십자선 그리기
		outputVideo << RedLineVideo;				// 십자선이 그려진 프레임을 출력 파일에 저장
		imshow("frame", frame);						// 원본 프레임 출력
		imshow("RedLineVideo", RedLineVideo);		// 십자선이 그려진 프레임 출력
		int key = waitKey(33);						// 약 30fps에 맞춰 33ms 대기, 키 입력 감지
		if (key == 'q' || key == 'Q') break;		// 'q' 또는 'Q' 입력 시 종료
	}
	return 0;
}
```

### 실행 결과
[video3](https://github.com/user-attachments/assets/5c83f3e8-04ac-456e-9e5f-cf109496a09e)


## 과제 4

웹캠으로부터 실시간으로 프레임을 캡처하여 화면에 출력하는 동시에 DIVX 코덱으로 동영상 파일에 저장하는 프로그램이다. `q` 또는 `Q` 키를 누르면 종료된다.

---

### `main()`

웹캠을 열어 프레임을 반복 캡처하며 화면 출력과 파일 저장을 동시에 수행한다.

```cpp
int main(void) {
	VideoCapture cap(0);							// 기본 웹캠(인덱스 0) 열기
	if (!cap.isOpened()) {							// 웹캠 열기 실패 시
		cerr << "Camera open failed" << endl;
		return -1;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));		// 웹캠 프레임 너비 가져오기
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));	// 웹캠 프레임 높이 가져오기
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');	// 출력 동영상 코덱을 DIVX로 설정
	VideoWriter outputVideo("camera_output.avi", fourcc, 30, Size(w, h));	// 30fps, 웹캠과 동일한 해상도로 출력 파일 생성
	if (!outputVideo.isOpened()) {					// 출력 파일 생성 실패 시
		cout << "File open failed!" << endl;
		return -1;
	}
	Mat frame;
	while (true) {
		cap >> frame;								// 웹캠에서 프레임 캡처
		if (frame.empty()) {						// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		outputVideo << frame;						// 캡처한 프레임을 출력 파일에 저장
		imshow("frame", frame);						// 현재 프레임 화면 출력
		int key = waitKey(33);						// 약 30fps에 맞춰 33ms 대기, 키 입력 감지
		if (key == 'q' || key == 'Q') break;		// 'q' 또는 'Q' 입력 시 종료
	}
	return 0;
}
```

### 실행 결과
[video4](https://github.com/user-attachments/assets/cb082ce9-4f00-4564-9c14-8341b98633da)


## 과제 5

웹캠을 열어 실시간으로 화면을 출력하다가 `s` 키를 누르는 순간부터 동영상 파일 저장을 시작하는 프로그램이다. `q` 또는 `Q` 키를 누르면 종료된다.

---

### `main()`

프레임 캡처와 화면 출력은 항상 수행하되, `isSave` 플래그로 파일 저장 여부만 제어한다.

```cpp
int main(void) {
	VideoCapture cap(0);							// 기본 웹캠(인덱스 0) 열기
	if (!cap.isOpened()) {							// 웹캠 열기 실패 시
		cerr << "Camera open failed" << endl;
		return -1;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));		// 웹캠 프레임 너비 가져오기
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));	// 웹캠 프레임 높이 가져오기
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');	// 출력 동영상 코덱을 DIVX로 설정
	VideoWriter outputVideo("press_s_output.avi", fourcc, 30, Size(w, h));	// 30fps, 웹캠과 동일한 해상도로 출력 파일 생성
	if (!outputVideo.isOpened()) {					// 출력 파일 생성 실패 시
		cout << "File open failed!" << endl;
		return -1;
	}
	Mat frame;
	bool isSave = false;							// 녹화 시작 여부 플래그
	while (true) {
		cap >> frame;								// 항상 프레임을 읽어 카메라 버퍼 누적 방지
		if (frame.empty()) {						// 프레임 캡처 실패 시
			cerr << "frame empty" << endl;
			break;
		}
		imshow("frame", frame);						// 항상 출력하여 waitKey 키 입력 감지 보장
		if (isSave) outputVideo << frame;			// 's' 키 입력 이후에만 파일 저장
		int key = waitKey(33);						// 약 30fps에 맞춰 33ms 대기, 키 입력 감지
		if (key == 's') isSave = true;				// 's' 키 입력 시 녹화 시작
		if (key == 'q' || key == 'Q') break;		// 'q' 또는 'Q' 입력 시 종료
	}
	return 0;
}
```

### 실행 결과

[video5](https://github.com/user-attachments/assets/ee24cf5f-48f1-4cf4-be07-93f9b782097c)
