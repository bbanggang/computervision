# ch 3-6 OpenCV 주요 클래스

## 과제 1

## 전체 프로그램 동작 설명

이미지를 불러와 행/열 수, 채널 수, 데이터 타입 정보를 콘솔에 출력하는 프로그램이다.

---

### `getDepthStr()`

`Mat`의 depth 값을 받아 해당하는 타입 문자열을 반환한다.

```cpp
string getDepthStr(int depth) {
	switch (depth) {
	case CV_8U:  return "CV_8U";	// 부호 없는 8비트 정수
	case CV_8S:  return "CV_8S";	// 부호 있는 8비트 정수
	case CV_16U: return "CV_16U";	// 부호 없는 16비트 정수
	case CV_16S: return "CV_16S";	// 부호 있는 16비트 정수
	case CV_32S: return "CV_32S";	// 부호 있는 32비트 정수
	case CV_32F: return "CV_32F";	// 32비트 부동소수점
	case CV_64F: return "CV_64F";	// 64비트 부동소수점
	default:     return "Unknown";	// 알 수 없는 타입
	}
}
```

---

### `main()`

이미지를 불러와 `getDepthStr()`을 활용하여 행렬 정보를 출력한다.

```cpp
int main(void) {
	Mat img = imread("photo.jpg", IMREAD_COLOR);	// photo.jpg를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed." << endl;
		return -1;
	}
	cout << "행의 수 : " << img.rows << endl;					// 이미지의 세로 픽셀 수 출력
	cout << "열의 수 : " << img.cols << endl;					// 이미지의 가로 픽셀 수 출력
	cout << "채널 수 : " << img.channels() << endl;			// 채널 수 출력 (컬러: 3, 그레이스케일: 1)
	cout << "Type: " << getDepthStr(img.depth()) << "C" << img.channels() << endl;	// depth 문자열과 채널 수를 조합하여 타입 출력 (예: CV_8UC3)
	return 0;
}
```

### 실행 결과

![work1](https://github.com/user-attachments/assets/bf5ff56b-d81c-411a-82c9-d57e75f5990f)

## 과제 2

세 개의 2x2 행렬을 정의하고 스칼라 연산, 역행렬, 행렬 합산을 조합한 수식으로 결과 행렬을 계산하여 출력하는 프로그램이다.

---

### `main()`

행렬 A, B, C를 초기화하고 `X = 3A + B⁻¹ + 10C - 5` 를 계산한다.

```cpp
int main(void) {
	Mat A = (Mat_<double>(2, 2) << 1, 3, -4, 2);		// 2x2 double 행렬 A 초기화
	Mat B = (Mat_<double>(2, 2) << 2, 3, 0, 5);		// 2x2 double 행렬 B 초기화
	Mat C = (Mat_<double>(2, 2) << -2, -2, -2, -3);	// 2x2 double 행렬 C 초기화
	cout << "matrix A" << endl << A << endl;
	cout << "matrix B" << endl << B << endl;
	cout << "matrix C" << endl << C << endl;
	Mat X = (3 * A) + (B.inv()) + (10 * C) - 5;	// 3A: A의 모든 원소에 3을 곱함
													// B.inv(): B의 역행렬 계산
													// 10C: C의 모든 원소에 10을 곱함
													// -5: 모든 원소에서 5를 뺌 (스칼라 연산)
	cout << "matrix X" << endl << X << endl;		// 계산된 결과 행렬 X 출력
	return 0;
}
```

### 실행 결과

![work2](https://github.com/user-attachments/assets/a31a485d-fd7c-46ce-95fc-eba742087066)

## 과제 3

사용자로부터 밝기 변화량을 입력받아 이미지의 전체 밝기를 조정하고 출력하는 프로그램이다.

---

### `main()`

이미지를 불러와 입력된 밝기 변화량을 모든 채널에 더해 밝기를 조정한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	int brightness;
	cout << "밝기 변화량을 입력 : ";
	cin >> brightness;								// 밝기 변화량 입력 (양수: 밝게, 음수: 어둡게)
	img += Scalar(brightness, brightness, brightness);	// BGR 각 채널에 변화량을 더해 밝기 조정 (255 초과 시 자동 포화 처리)
	imshow("image", img);							// 밝기가 조정된 이미지 출력
	waitKey();										// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행 결과

![work3](https://github.com/user-attachments/assets/47b499d8-b4a2-4c60-980b-239d3f3d56bb)
