# ch 3-1 OpenCV 주요 클래스

## 과제 1

두 점의 좌표를 입력받아 두 점 사이의 거리를 계산하고 출력하는 프로그램이다.

---

### `getSafePoint()`

사용자로부터 유효한 점의 좌표를 입력받아 `Point` 객체를 반환한다.

```cpp
Point getSafePoint(string name) {
	int x, y;
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		cout << name << "의 x,y 좌표를 입력 : ";
		if (cin >> x >> y) {						// 숫자 두 개 입력 성공 시
			return Point(x, y);						// Point 객체 생성 후 반환
		}
		else {
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}
```

---

### `main()`

두 점을 입력받아 좌표를 출력하고 두 점 사이의 거리를 계산한다.

```cpp
int main(void) {
	Point pt1, pt2;
	pt1 = getSafePoint("첫번째 점");			// 첫번째 점 좌표 입력
	pt2 = getSafePoint("두번째 점");			// 두번째 점 좌표 입력
	cout << "pt1: " << pt1 << endl;				// pt1 좌표 출력
	cout << "pt2: " << pt2 << endl;				// pt2 좌표 출력
	double dist = norm(pt1 - pt2);				// 두 점의 차 벡터의 노름(norm)으로 유클리드 거리 계산
	cout << "두점사이의 거리:" << dist << endl;
	return 0;
}

![work1](https://github.com/user-attachments/assets/f02d9358-5d59-4af6-b8de-398ff540ce02)

```

## 과제 2

두 사각형의 크기를 입력받아 각 사각형의 크기와 면적을 출력하는 프로그램이다. 잘못된 입력에 대한 예외 처리를 포함한다.

---

### `getSafeSize()`

사용자로부터 유효한 사각형 크기를 입력받아 `Size` 객체를 반환한다.

```cpp
Size getSafeSize(string name) {
	int width, height;
	while (true) {										// 유효한 입력이 들어올 때까지 반복
		cout << name << "사각형의 폭, 높이 입력 : ";
		if (cin >> width >> height) {					// 숫자 두 개 입력 성공 시
			if (width >= 0 && height >= 0) {			// 폭과 높이가 양수인지 확인
				return Size(width, height);				// Size 객체 생성 후 반환
			}
			else {
				cout << "오류 : 사각형의 크기는 음수가 될 수 없습니다." << endl;
			}
		}
		else {
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다. 다시 입력하세요." << endl;
			cin.clear();								// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}
```

---

### `main()`

두 `Size` 객체를 입력받아 크기와 면적을 출력한다.

```cpp
int main(void) {
	Size s1 = getSafeSize("첫번째");		// 첫번째 사각형 크기 입력
	Size s2 = getSafeSize("두번째");		// 두번째 사각형 크기 입력
	cout << "s1 : " << s1 << endl;			// s1의 폭, 높이 출력
	cout << "s2 : " << s2 << endl;			// s2의 폭, 높이 출력
	cout << "s1의 면적 " << s1.area() << endl;		// s1의 면적(width * height) 출력
	cout << "s2의 면적 " << s2.area() << endl;;		// s2의 면적(width * height) 출력
	return 0;
}

![work2](https://github.com/user-attachments/assets/8ad003b5-19c4-4435-a196-7294296dd0a8)

```

## 과제 3

사각형과 점을 직접 정의한 뒤, 점이 사각형 내부에 존재하는지 판별하여 결과를 출력하는 프로그램이다.

---

### `main()`

`Rect`와 `Point`를 생성하고 `contains()`로 점의 위치를 판별한다.

```cpp
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main(void) {
	Rect r1(10, 10, 20, 20);		// 좌측 상단 (10,10), 폭 20, 높이 20인 사각형 생성
	Point p1(10, 10);				// 좌표 (10, 10)인 점 생성
	if (r1.contains(p1)) {			// p1이 r1 내부에 포함되는지 확인 (경계 포함)
		cout << "사각형 r1 내부에 점 p1이 존재합니다." << endl;
	}
	else {
		cout << "사각형 r1 외부에 점 p1이 존재합니다." << endl;
	}
	return 0;
}

![work3](https://github.com/user-attachments/assets/ddca46b5-6f6f-41c8-b50f-6f0cf129c146)

```

## 과제 4

사용자로부터 사각형과 점의 좌표를 입력받아, 해당 점이 사각형 내부에 있는지 여부를 판별하는 프로그램이다. 잘못된 입력에 대한 예외 처리를 포함한다.

---

### `getSafePoint()`

사용자로부터 유효한 점의 좌표를 입력받아 `Point` 객체를 반환한다.

```cpp
Point getSafePoint(string name) {
	int x, y;
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		cout << name << "의 x,y 좌표를 입력 : ";
		if (cin >> x >> y) {						// 숫자 두 개 입력 성공 시
			return Point(x, y);						// Point 객체 생성 후 반환
		}
		else {
			cout << "오류 : 숫자가 아닌 값이 입력되었습니다." << endl;
			cin.clear();							// 오류 상태 플래그 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// 입력 버퍼의 잔여 내용 제거
		}
	}
}
```

---

### `getSafeRect()`

사용자로부터 유효한 사각형 정보를 입력받아 `Rect` 객체를 반환한다.

```cpp
Rect getSafeRect() {
	int x, y, width, height;
	Point pt1; Size sz1;
	while (true) {									// 유효한 입력이 들어올 때까지 반복
		cout << "사각형의 좌측 상단의 좌표를 입력하시오(x,y) : ";
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
		cout << "사각형의 폭, 높이를 입력하시오(width, height) : ";
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

![work4](https://github.com/user-attachments/assets/95d8b6bd-9f91-4242-b94a-26beabbe46d9)

```

---

### `main()`

사각형과 점을 입력받아 점의 위치를 판별하고 결과를 출력한다.

```cpp
int main(void) {
	Rect r = getSafeRect();						// 사각형 정보 입력
	Point pt = getSafePoint("점 P");			// 점 P의 좌표 입력

	if (pt.inside(r)) {							// 점이 사각형 내부에 있는지 확인
		cout << "점 P는 사각형 안에 있다." << endl;
	}
	else {
		cout << "점 P는 사각형 밖에 있다." << endl;
	}
	return 0;
}
```

## 과제 5

예제 4를 수정한 코드로 `cv::format()`을 사용해 홀수 번호 파일명 문자열을 생성하고 콘솔에 출력하는 프로그램이다.

---

### `main()`

반복문으로 홀수 인덱스 파일명을 포맷하여 순서대로 출력한다.

```cpp
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main(void) {
	String str;								// OpenCV의 String 타입 변수 선언 (cv::String)
	for (int i = 1; i <= 15; i += 2) {		// i = 1, 3, 5, 7, 9, 11, 13, 15 (홀수만 순회)
		str = format("실행결과%d.bmp", i);	// "실행결과1.bmp" ~ "실행결과15.bmp" 형식의 문자열 생성
		cout << str << endl;				// 생성된 파일명 문자열을 콘솔에 출력
	}
	return 0;
}

![work5](https://github.com/user-attachments/assets/cab08478-62bc-4fd8-8676-1cffd7a8f5b6)

```