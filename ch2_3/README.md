# ch 2-3 OpenCV 설치와 기초 사용법

## 과제 1

그레이스케일 이미지를 불러와 밝기를 높인 뒤 화면에 출력하고 파일로 저장하는 프로그램

---

### 함수 설명 `main()`

이미지 로드, 밝기 조정, 출력, 저장의 전체 흐름을 처리

```cpp
int main() {
	int count = 0;
	Mat img;
	img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed!" << endl;		// 에러 메시지 출력
		return -1;									// 프로그램 종료
	}
	Mat bright_img = img + 100;						// 픽셀 값에 100을 더해 밝기 증가 (255 초과 시 자동 포화 처리)
	imshow("gray image", img);						// 원본 그레이스케일 이미지 출력
	imshow("bright image", bright_img);				// 밝기 증가된 이미지 출력

	imwrite("bright.jpg", bright_img);				// 밝기 증가된 이미지를 파일로 저장
	waitKey();										// 키 입력 대기 
	return 0;
}
```

## 과제 2

여러 이미지 파일을 순서대로 불러와 1초 간격으로 반복 슬라이드쇼처럼 출력하는 프로그램으로 `q` 키를 누르면 종료

---

### `main()`

이미지 파일을 벡터에 저장한 뒤, 반복문으로 순차 출력

```cpp
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace cv;
int main() {
	vector<Mat> vec;							// 이미지를 저장할 Mat 벡터 선언
	for (int i = 0; i < 3;i++) {
		string filename = "test" + to_string(i + 1) + ".jpg";	// "test1.jpg", "test2.jpg", "test3.jpg" 파일명 생성
		Mat tmp = imread(filename, IMREAD_COLOR);				// 컬러 모드로 이미지 읽기
		vec.push_back(tmp);										// 벡터에 이미지 추가
	}
	while (true) {												// 무한 반복 (슬라이드쇼)
		for (auto it = vec.begin(); it != vec.end(); it++) {	// 벡터의 이미지를 순서대로 순회
			imshow("test", *it);								// 현재 이미지를 "test" 창에 출력
			int ch = waitKey(1000);								// 1초 대기, 그 사이 키 입력 감지
			if (ch == 'q') return -1;							// 'q' 키 입력 시 프로그램 종료
		}
	}
	return 0;
}
```

- [test2_video](https://github.com/user-attachments/assets/17964d1e-c762-45f3-b4bd-602af325f2ec)

## 과제 3

숫자 이미지 파일(0~9)을 순서대로 불러와 1초 간격으로 반복 출력하는 슬라이드쇼 프로그램으로  `q` 키를 누르면 종료

---

### `main()`

숫자 이미지 파일을 벡터에 저장한 뒤, 반복문으로 순차 출력

```cpp
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace cv;
int main() {
	vector<Mat> vec;							// 이미지를 저장할 Mat 벡터 선언
	for (int i = 0; i < 10; i++) {
		string filename = "number" + to_string(i) + ".png";	// "number0.png" ~ "number9.png" 파일명 생성
		Mat tmp = imread(filename, IMREAD_COLOR);			// 컬러 모드로 이미지 읽기
		vec.push_back(tmp);									// 벡터에 이미지 추가
	}
	while (true) {											// 무한 반복 
		for (auto it = vec.begin(); it != vec.end(); it++) {	// 벡터의 이미지를 순서대로 순회
			imshow("test", *it);							// 현재 이미지를 "test" 창에 출력
			int ch = waitKey(1000);							// 1초 대기, 그 사이 키 입력 감지
			if (ch == 'q') return -1;						// 'q' 키 입력 시 프로그램 종료
		}
	}
	return 0;
}
```

- [test3_video](https://github.com/user-attachments/assets/9effbb87-f776-47b9-8376-0cd8ebe898c7)
