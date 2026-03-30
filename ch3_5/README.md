# ch 3-5 OpenCV 주요 클래스

## 과제 1

컬러 이미지에서 특정 좌표의 BGR 화소값을 읽어 콘솔에 출력하는 프로그램이다.

---

### `main()`

이미지를 불러와 세 좌표의 화소값을 `at<Vec3b>()`로 접근하여 출력한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	cout << "좌표 (50, 50)의 화소값(B, G, R) : " << img.at<Vec3b>(50, 50) << endl;		// (행 50, 열 50) 위치의 BGR 화소값 출력
	cout << "좌표 (100, 100)의 화소값(B, G, R) : " << img.at<Vec3b>(100, 100) << endl;	// (행 100, 열 100) 위치의 BGR 화소값 출력
	cout << "좌표 (150, 150)의 화소값(B, G, R) : " << img.at<Vec3b>(150, 150) << endl;	// (행 150, 열 150) 위치의 BGR 화소값 출력
	return 0;
}
```
### 실행결과
![work1](https://github.com/user-attachments/assets/2787f67f-0a33-4c4f-956e-55901173ad2f)

## 과제 2

그레이스케일 이미지에 가로 3줄, 세로 3줄의 흰색 격자선을 화소값 직접 접근 방식으로 그려 출력하는 프로그램이다.

---

### `main()`

`at<uchar>()`로 각 화소에 직접 접근하여 이미지를 4등분하는 위치에 흰색 선을 그린다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	for (int i = 0; i < img.rows; i++) {				// 모든 행을 순회
		for (int j = 0; j < 3; j++) {					// 세로 3줄 (열 방향 1/4, 2/4, 3/4 위치)
			img.at<uchar>(i, img.cols * (j + 1) / 4) = 255;	// 해당 열의 화소값을 흰색(255)으로 설정
		}
	}
	for (int i = 0; i < img.cols; i++) {				// 모든 열을 순회
		for (int j = 0; j < 3; j++) {					// 가로 3줄 (행 방향 1/4, 2/4, 3/4 위치)
			img.at<uchar>(img.rows * (j + 1) / 4, i) = 255;	// 해당 행의 화소값을 흰색(255)으로 설정
		}
	}
	imshow("line", img);								// 격자선이 그려진 이미지 출력
	waitKey();											// 키 입력 대기 
	return 0;
}
```
### 실행결과
![work2](https://github.com/user-attachments/assets/98de2170-e9ad-4ae6-8f86-2ceedd9ca050)

## 과제 3

컬러 이미지에 가로 3줄, 세로 3줄의 흰색 격자선을 화소값 직접 접근 방식으로 그려 출력하는 프로그램이다.

---

### `main()`

`at<Vec3b>()`로 각 화소에 직접 접근하여 이미지를 4등분하는 위치에 흰색 선을 그린다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);		// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {									// 이미지 로드 실패 시
		cerr << "image load failed" << endl;
		return -1;
	}
	for (int i = 0; i < img.rows; i++) {				// 모든 행을 순회
		for (int j = 0; j < 3; j++) {					// 세로 3줄 (열 방향 1/4, 2/4, 3/4 위치)
			img.at<Vec3b>(i, img.cols * (j + 1) / 4) = Vec3b(255, 255, 255);	// 해당 열의 BGR 화소값을 흰색으로 설정
		}
	}
	for (int i = 0; i < img.cols; i++) {				// 모든 열을 순회
		for (int j = 0; j < 3; j++) {					// 가로 3줄 (행 방향 1/4, 2/4, 3/4 위치)
			img.at<Vec3b>(img.rows * (j + 1) / 4, i) = Vec3b(255, 255, 255);	// 해당 행의 BGR 화소값을 흰색으로 설정
		}
	}
	imshow("line", img);								// 격자선이 그려진 이미지 출력
	waitKey();											// 키 입력 대기
	return 0;
}
```
### 실행결과
![work3](https://github.com/user-attachments/assets/2c64ea31-0e0a-4fbf-a0b5-f9ebf3812a09)

## 과제 4

흰색 배경의 이미지에 이차함수(포물선) 그래프를 검은색 화소로 직접 그려 출력하는 프로그램이다.

---

### `main()`

x좌표를 순회하며 이차함수 공식으로 y좌표를 계산하고 해당 화소를 검은색으로 설정한다.

```cpp
int main(void) {
	Mat img(400, 400, CV_8UC1, 255);			// 400x400 크기의 흰색(255) 그레이스케일 이미지 생성
	for (int x = 0; x < img.cols; x++){			// x좌표 0~399 순회
		int y = (double)1 / 400 * x * x;		// y = x² / 400 으로 포물선의 y좌표 계산 (이미지 범위 내 스케일 조정)
		img.at<uchar>(y, x) = 0;				// (y, x) 위치의 화소를 검은색(0)으로 설정
	}
	imshow("gragh", img);						// 포물선이 그려진 이미지 출력
	waitKey();									// 키 입력 대기 
	return 0;
}
```
### 실행결과
![work4](https://github.com/user-attachments/assets/8a49c537-bd24-4cb5-a30e-d5b69e685224)