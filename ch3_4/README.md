# ch 3-4 OpenCV 주요 클래스

## 과제 1

### 얕은 복사(Shallow Copy)

얕은 복사는 실제 데이터를 복제하기 않고 데이터가 저장된 메모리 주소만 복사하는 방식으로 대입 연산자 사용 시 기본적으로 발생

- 장점 :
    - 주소 값만 복사하므로 연산 시간이 거의 제로
    - 동일 데이터를 여러 변수가 공유하므로 메모리 점유율 감소
    - 대용량 이미지를 함수로 보낼 때 성능 저하 없이 구조체 정보만 전송
- 단점 :
    - 한 변수에서 데이터 수정 시 데이터 오염 문제
    - 원본 데이터에서 메모리 해제 시 복사본이 참조하는 경우 프로그램 충돌

---

### 깊은 복사 (Deep Copy)

새로운 메모리 공간을 할당하고, 원본의 실제 데이터를 물리적으로 모두 복제하는 방식으로 `.clone()` , `.copyTo()` 함수 사용 시 발생

- 장점 :
    - 복사본을 수정해도 원본 데이터에 영향이 없어 원본 데이터 보존이 가능
    - 각 객체가 자신의 메모리를 관리하여 한 객체 소멸 시 다른 객체는 데이터 유지
- 단점 :
    - 데이터를 일일이 옮기는 시간 소요
    - 메모리 낭비

## 과제 2

정수 행렬을 직접 초기화한 뒤, 특정 영역을 ROI로 지정하여 복사하고 출력하는 프로그램이다.

---

### `main()`

`Mat_<int>`로 행렬을 생성하고 `Rect`로 부분 영역을 추출하여 출력한다.

```cpp
int main(void) {
	Mat img1 = (Mat_<int>(3, 5) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);	// 3x5 int 행렬 초기화 (값 1~15)
	cout << img1 << endl;																	// 전체 행렬 출력
	Mat img2 = img1(Rect(Point(2,1), Size(3,2))).clone();	// 좌측 상단 (2, 1)에서 3x2 크기의 영역을 ROI로 지정 후 독립 복사
															// → 추출되는 값: [8, 9, 10 / 13, 14, 15]
	cout << img2 << endl;								// 추출된 부분 행렬 출력
	return 0;
}
```

### 실행결과
![work2](https://github.com/user-attachments/assets/955f6e0b-71df-4b41-814c-4779953b9cec)


## 과제 3

이미지의 특정 영역을 파란색으로 채워 출력하는 프로그램이다.

---

### `main()`

이미지를 불러와 ROI 영역을 파란색으로 채운 뒤 출력한다.

```cpp
int main(void) {
	Mat	img1 = imread("dog.bmp", IMREAD_COLOR);		// dog.bmp를 컬러 모드로 읽기
	if (img1.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed!" << endl;
		return -1;
	}
	Mat img2 = img1(Rect(100, 40, 75, 75)).setTo(Scalar(255, 0, 0));	// 좌측 상단 (100, 40), 크기 75x75 영역을 파란색으로 채우기
																		// setTo()는 원본 이미지와 메모리를 공유하므로 img1에도 반영됨
	imshow("img1", img1);							// 파란색 영역이 적용된 이미지 출력
	waitKey();										// 키 입력 대기 (창 유지)
	return 0;
}
```
### 실행결과
![work3](https://github.com/user-attachments/assets/c0bde069-2257-4c49-b013-898ed16579a9)

## 과제 4

이미지의 특정 영역이 원본과 파란색으로 1초 간격으로 번갈아 표시되는 깜빡임 효과를 구현한 프로그램이다. `q` 키를 누르면 종료된다.

---

### `main()`

ROI 영역의 원본을 복사해 두고, 파란색 채우기와 원본 복원을 반복하여 깜빡임 효과를 구현한다.

```cpp
int main(void) {
	Mat	img1 = imread("dog.bmp", IMREAD_COLOR);		// dog.bmp를 컬러 모드로 읽기
	if (img1.empty()) {									// 이미지 로드 실패 시
		cerr << "Image load failed!" << endl;
		return -1;
	}
	Rect region(100, 40, 75, 75);						// 좌측 상단 (100, 40), 크기 75x75의 관심 영역 정의
	Mat img2 = img1(region).clone();					// ROI 영역을 복사하여 원본 데이터를 별도 저장 (깜빡임 복원용)
	Mat roi = img1(region);								// 원본 이미지와 메모리를 공유하는 ROI 참조 생성
	bool is_blue = 0;									// 현재 상태 플래그 (false: 원본, true: 파란색)
	while (true) {
		Mat tmp;
		if (!is_blue) {
			tmp = roi.setTo(Scalar(255, 0, 0));			// ROI 영역을 파란색으로 채우기 (원본 이미지에도 반영됨)
			is_blue = 1;								// 상태를 파란색으로 전환
		}
		else
		{
			img2.copyTo(roi);							// 저장해둔 원본 데이터를 ROI에 복사하여 복원
			is_blue = 0;								// 상태를 원본으로 전환
		}
		imshow("img1", img1);							// 현재 상태의 이미지 출력
		if (waitKey(1000) == 'q') break;				// 1초 대기 후 'q' 입력 시 반복 종료
	}
	return 0;
}
```

### 실행결과
![work4](https://github.com/user-attachments/assets/6eecdfa7-3748-4d65-844e-cfe6a2236482)

## 과제 5

흰색 배경의 이미지에서 빨간 블록이 1초 간격으로 좌→중→우 순서로 이동하는 애니메이션 프로그램이다. `q` 키를 누르면 종료된다.

---

### `main()`

매 반복마다 이미지를 흰색으로 초기화한 뒤 현재 인덱스 위치에 빨간 블록을 그려 출력한다.

```cpp
int main(void) {
	Mat img1(200, 600, CV_8UC3, Scalar(255,255,255));	// 200x600 크기의 흰색 3채널 이미지 생성
	int index = 0;										// 빨간 블록의 현재 위치 인덱스 (0: 좌, 1: 중, 2: 우)
	while (true) {
		img1.setTo(Scalar(255, 255, 255));				// 매 프레임마다 이미지 전체를 흰색으로 초기화
		Rect area(index * 200, 0, 200, 200);			// 인덱스에 따라 200x200 크기의 블록 영역 계산 (x = index * 200)
		img1(area).setTo(Scalar(0, 0, 255));			// 해당 영역을 빨간색으로 채우기
		imshow("img1", img1);							// 현재 프레임 출력
		if (waitKey(1000) == 'q') break;				// 1초 대기 후 'q' 입력 시 반복 종료
		index = (index + 1) % 3;						// 인덱스를 0→1→2→0 순으로 순환
	}
	return 0;
}
```
### 실행결과
![work5](https://github.com/user-attachments/assets/01934e09-1f4c-4dfd-8d51-466c4052b793)

## 과제 6

이미지에서 관심 영역(ROI)을 지정하고, 해당 영역의 픽셀 밝기를 사용자가 입력한 변화량만큼 조정하여 출력하는 프로그램이다.

---

### `getSafeRect()`

사용자로부터 유효한 관심 영역의 좌표와 크기를 입력받아 `Rect` 객체를 반환한다.

```cpp
Rect getSafeRect() {
	int x, y, width, height;
	Point pt1; Size sz1;
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		cout << "관심영역의 좌측상단좌표(x, y) : ";
		if (cin >> x >> y) {						// 숫자 두 개 입력 성공 시
			if (x >= 0 && y >= 0) {					// 좌표가 양수인지 확인
				pt1 = Point(x, y);					// 좌측 상단 좌표 저장
			}
			else {
				cout << "오류 : 양수의 좌표를 입력하시오. 처음부터 다시 입력하세요." << endl;
				continue;							// 처음부터 다시 입력
			}
		}
		else
		{
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다. 처음부터 다시 입력하세요." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
			continue;
		}
		cout << "관심영역의 폭, 높이(width, height) : ";
		if (cin >> width >> height) {				// 숫자 두 개 입력 성공 시
			if (width >= 0 && height >= 0) {		// 폭과 높이가 양수인지 확인
				sz1 = Size(width, height);			// 크기 저장
				return Rect(pt1, sz1);				// Rect 객체 생성 후 반환
			}
			else {
				cout << "오류 : 양수의 값을 입력하시오. 처음부터 다시 입력하세요." << endl;
				continue;							// 처음부터 다시 입력
			}
		}
		else
		{
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다. 처음부터 다시 입력하세요." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}
```

---

### `getSafeChange()`

사용자로부터 유효한 픽셀 변화량을 입력받아 반환한다.

```cpp
int getSafeChange() {
	int pixel_change;
	cout << "픽셀변화량 : ";
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		if (cin >> pixel_change) {					// 숫자 입력 성공 시
			return pixel_change;					// 입력된 변화량 반환
		}
		else
		{
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}
```

---

### `main()`

이미지를 불러와 ROI를 지정하고 해당 영역의 밝기를 조정하여 출력한다.

```cpp
int main(void) {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);	// lenna.bmp를 컬러 모드로 읽기
	if (img.empty()) {								// 이미지 로드 실패 시
		cerr << "Image load failed" << endl;
		return -1;
	}
	Mat roi = img(getSafeRect());					// 사용자가 입력한 영역을 ROI로 설정 (원본 이미지와 메모리 공유)
	roi.convertTo(roi, -1, 1, getSafeChange());		// ROI 픽셀값에 변화량을 더함 (-1: 원본 타입 유지, 1: 스케일 유지, 마지막 인자: 밝기 변화량)
	imshow("img", img);								// 변경된 원본 이미지 출력 (ROI가 원본과 메모리를 공유하므로 원본에 반영됨)
	waitKey();										// 키 입력 대기 (창 유지)
	return 0;
}
```

### 실행결과
![work6](https://github.com/user-attachments/assets/35c52535-45c2-4eeb-bb38-e875f5482c45)

![work6](https://github.com/user-attachments/assets/5af1e6ee-adaa-467b-9bb8-f23e75552577)
