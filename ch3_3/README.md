# ch 3-3 OpenCV 주요 클래스

## 과제 1

다양한 자료형과 크기의 `Mat` 행렬을 직접 초기화하여 콘솔에 출력하는 프로그램이다.

---

### `main()`

서로 다른 자료형과 크기의 `Mat` 객체를 생성하고 출력한다.

```cpp
int main() {
	Mat mat1 = (Mat_<double>(2, 2) << 3.5, 2.1, -1.5, -6.5);		// 2x2 double 행렬 초기화
	Mat mat2 = (Mat_<schar>(3, 3) << 0, 2, -1, 5, 10, 8, 6, -7, 9);	// 3x3 부호 있는 8비트 정수(schar) 행렬 초기화
	Mat mat3 = (Mat_<uchar>(1, 4) << 1, 2, 3, 4);				// 1x4 부호 없는 8비트 정수(uchar) 행 벡터 초기화
	Mat mat4 = (Mat_<uchar>(4, 1) << 5, 6, 7, 8);				// 4x1 부호 없는 8비트 정수(uchar) 열 벡터 초기화
	cout << "mat1 = " << endl << mat1 << endl;				// mat1 행렬 출력
	cout << "mat2 = " << endl << mat2 << endl;				// mat2 행렬 출력
	cout << "mat3 = " << endl << mat3 << endl;				// mat3 행 벡터 출력
	cout << "mat4 = " << endl << mat4 << endl;				// mat4 열 벡터 출력
	return 0;
}
```
### 실행결과
![work1](https://github.com/user-attachments/assets/e27c69cd-7483-4f74-b155-01ee7b51f3ed)

```

## 과제 2

파란색, 초록색, 빨간색으로 채워진 이미지를 각각 생성하여 별도의 창에 출력하는 프로그램이다.

---

### `main()`

단색으로 채워진 `Mat` 이미지를 벡터에 저장한 뒤 각각의 창에 출력한다.

```cpp
int main() {
	vector<Mat> vec;
	Scalar colors[3] = { Scalar(255, 0, 0), Scalar(0, 255, 0) , Scalar(0, 0, 255) };	// BGR 순서로 파랑, 초록, 빨강 색상 정의
	string labels[3] = { "Blue", "Green", "Red" };										// 각 창의 이름 정의
	for (int i = 0; i < 3; i++) {
		Mat tmp = Mat(300, 400, CV_8UC3, colors[i]);	// 300x400 크기의 3채널 컬러 이미지를 단색으로 생성
		vec.push_back(tmp);								// 벡터에 이미지 추가
	}
	for (int i = 0; i < 3; i++) {
		imshow(labels[i], vec[i]);						// 각 색상 이름을 창 제목으로 하여 이미지 출력
	}
	waitKey(0);											// 키 입력 대기 (창 유지)
	return 0;
}
```
### 실행결과
![work2](https://github.com/user-attachments/assets/abf18da0-7ee1-4e59-8f36-a24b9cc7e7d8)

```

## 과제 3

사용자로부터 BGR 색상값을 입력받아 해당 색상으로 채워진 이미지를 생성하고 출력하는 프로그램이다.

---

### `getSafeBGR()`

B, G, R 각각의 값을 0~255 범위 내에서 유효하게 입력받아 `Scalar` 객체로 반환한다.

```cpp
Scalar getSafeBGR() {
	Scalar BGR;
	string colors[3] = { "B", "G", "R" };				// 입력 안내에 사용할 채널 이름 배열
	int temp;
	for (int i = 0; i < 3; i++) {						// B, G, R 순서로 각 채널 값 입력
		while (true) {									// 유효한 입력이 들어올 때까지 반복
			cout << colors[i] << "값을 입력하라: ";
			if (cin >> temp) {							// 숫자 입력 성공 시
				if (temp >= 0 && temp <= 255) {			// 0~255 범위 확인
					BGR[i] = temp;						// 해당 채널에 값 저장
					break;								// 다음 채널로 이동
				}
				else
				{
					cout << "오류 : (0~255) 사이의 정수값을 입력하세요." << endl;
					continue;
				}
			}
			else {
				cout << "오류 : 숫자가 아닌 값이 입력되었습니다." << endl;
				cin.clear();							// 오류 상태 플래그 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
				continue;
			}
		}
	}
	return BGR;											// 완성된 BGR 색상값 반환
}
```

---

### `main()`

입력받은 색상으로 이미지를 채워 출력한다.

```cpp
int main(void) {
	Scalar color = getSafeBGR();				// BGR 색상값 입력
	Mat tmp = Mat(300, 400, CV_8UC3);			// 300x400 크기의 3채널 컬러 이미지 생성 (초기값 없음)
	tmp.setTo(color);							// 이미지 전체를 입력받은 색상으로 채우기

	imshow("color", tmp);						// 색상 이미지 출력
	waitKey();									// 키 입력 대기 (창 유지)
	return 0;
}
```
### 실행결과
![work3](https://github.com/user-attachments/assets/e8de2959-8a7a-4e6e-8073-4f9b3a3213f2)

```

## 과제 4

파란색, 초록색, 빨간색 단색 이미지를 1초 간격으로 반복 출력하는 슬라이드쇼 프로그램이다. `q` 키를 누르면 종료된다.

---

### `main()`

단색 이미지를 벡터에 저장한 뒤, 반복문으로 1초 간격 슬라이드쇼를 구현한다.

```cpp
int main() {
	vector<Mat> vec;
	Scalar colors[3] = { Scalar(255, 0, 0), Scalar(0, 255, 0) , Scalar(0, 0, 255) };	// BGR 순서로 파랑, 초록, 빨강 색상 정의
	string labels[3] = { "Blue", "Green", "Red" };										// 각 색상의 이름 정의 (현재 코드에서는 미사용)
	for (int i = 0; i < 3; i++) {
		Mat tmp = Mat(300, 400, CV_8UC3, colors[i]);	// 300x400 크기의 3채널 이미지를 단색으로 생성
		vec.push_back(tmp);								// 벡터에 이미지 추가
	}
	while (true) {										// 무한 반복 (슬라이드쇼)
		for (auto it = vec.begin(); it != vec.end(); it++) {	// 벡터의 이미지를 순서대로 순회
			imshow("test", *it);						// 현재 이미지를 "test" 창에 출력
			int ch = waitKey(1000);						// 1초 대기, 그 사이 키 입력 감지
			if (ch == 'q') return -1;					// 'q' 키 입력 시 프로그램 종료
		}
	}
	return 0;
}
```
### 실행결과
![work4](https://github.com/user-attachments/assets/55d2cf94-e00b-42f0-9419-64a8bb77336b)

```

## 과제 5

그레이스케일 이미지의 밝기를 0에서 255까지 증가시켰다가 다시 0으로 감소시키는 것을 반복하는 애니메이션 프로그램이다. `Q` 키를 누르면 종료된다.

---

### `main()`

플래그를 활용해 밝기 증감 방향을 제어하며 이미지를 실시간으로 갱신한다.

```cpp
int main() {
	int grayscale_size = 0;								// 현재 밝기 값 (0~255)
	bool flag = 1;										// true: 밝기 증가 방향, false: 밝기 감소 방향
	Mat image = Mat(400, 400, CV_8UC1, Scalar(grayscale_size));	// 400x400 크기의 1채널(그레이스케일) 이미지 생성, 초기값 0(검정)
	while (true) {
		if (flag) {										// 밝기 증가 구간
			imshow("image", image);						// 현재 밝기의 이미지 출력
			grayscale_size++;							// 밝기 1 증가
			cout << grayscale_size << endl;				// 현재 밝기 값 콘솔 출력
			if (grayscale_size == 255) flag = 0;		// 최대 밝기(255) 도달 시 감소 방향으로 전환
			image.setTo(grayscale_size);				// 이미지 전체를 새 밝기 값으로 갱신
		}
		else {											// 밝기 감소 구간
			imshow("image", image);						// 현재 밝기의 이미지 출력
			grayscale_size--;							// 밝기 1 감소
			cout << grayscale_size << endl;				// 현재 밝기 값 콘솔 출력
			if (grayscale_size == 0) flag = 1;			// 최소 밝기(0) 도달 시 증가 방향으로 전환
			image.setTo(grayscale_size);				// 이미지 전체를 새 밝기 값으로 갱신
		}
		int ch = waitKey(5);							// 5ms 대기, 그 사이 키 입력 감지
		if (ch == 'Q') return -1;						// 'Q' 키 입력 시 프로그램 종료
	}
	return 0;
}
```
### 실행결과
![work5](https://github.com/user-attachments/assets/1953fa19-638e-4eff-8a46-5b99f2d36684)
