# ch 5-2 영상의 밝기와 명암비 조절

## 과제 1

픽셀 값에 상수 `s`를 곱하여 이미지 전체 밝기를 조절하는 프로그램이다.

---

### main()

lenna.bmp를 그레이스케일로 읽고 각 픽셀에 배율 `s`를 곱해 밝기를 조정한 결과를 출력한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat dst(src.rows, src.cols, src.type());	// src와 동일한 크기·타입의 출력 이미지 생성

	float s = 2.f;	// 밝기 배율 (2배)

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>((s * src.at<uchar>(j, i)));
			// 각 픽셀에 s를 곱한 값 저장 (saturate_cast로 0~255 범위 클리핑)
		}
	}

	imshow("src", src);	// 원본 이미지 출력
	imshow("dst", dst);	// 밝기 조정된 이미지 출력
	waitKey();
	return 0;
}
```

### 실행 결과

![image1](https://github.com/user-attachments/assets/fb19d0e6-d829-43be-a5f3-f9e45675e5f6)


## 과제 2

픽셀 값에서 중간값(128)을 기준으로 `alpha`를 적용하여 이미지 명암비를 조절하는 프로그램이다.

---

### main()

lenna.bmp를 그레이스케일로 읽고 `dst = src + (src - 128) * alpha` 공식으로 명암비를 조정한 결과를 출력한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat dst(src.rows, src.cols, src.type());	// src와 동일한 크기·타입의 출력 이미지 생성

	float alpha = 1.f;	// 명암비 조정 계수

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + (src.at<uchar>(j, i) - 128) * alpha);
			// dst = src + (src - 128) * alpha: 128 기준으로 밝은 픽셀은 더 밝게, 어두운 픽셀은 더 어둡게
		}
	}

	imshow("src", src);	// 원본 이미지 출력
	imshow("dst", dst);	// 명암비 조정된 이미지 출력
	waitKey();
	return 0;
}
```

### 실행 결과
![image2](https://github.com/user-attachments/assets/d70e93ec-079d-4fc5-8e90-29f9e48e163c)



## 과제 3

과제 2의 공식 `dst = src + (src - 128) * alpha`에서 `alpha` 값의 크기에 따른 결과를 분석한다.

---

### alpha가 너무 크면?

`alpha`가 매우 클 경우, 128보다 밝은 픽셀은 `(src - 128) * alpha`가 큰 양수가 되어 **255로 포화**되고, 128보다 어두운 픽셀은 큰 음수가 되어 **0으로 포화**된다.

`saturate_cast`가 0~255 범위를 벗어난 값을 클리핑하므로 중간 밝기 정보가 사라지며, 이미지가 **흑백 이진화된 것처럼** 표현된다.

### 실행 결과
![image3](https://github.com/user-attachments/assets/1ccb0a57-26dd-4575-9b38-cb18ccfb6232)


---

### alpha가 0에 가까워지면?

`alpha`가 0에 가까워지게 되면 픽셀의 밝기의 평균이 128에 수렴하게 된다.

즉 원본 영상과 **거의 차이가 없는** 영상이 출력된다.


### 실행 결과
![image4](https://github.com/user-attachments/assets/273df2c2-dc40-4649-9a44-2332d889444e)


---

### alpha가 너무 작으면? (음수)

`alpha`가 음수가 되면 128보다 밝은 픽셀은 값이 **감소**하고, 128보다 어두운 픽셀은 값이 **증가**한다.

즉 밝고 어두운 영역의 관계가 뒤집혀 **명암이 반전**된 이미지가 출력된다. `alpha = -1`이면 `dst = 256 - src`에 근접하여 네거티브 이미지에 가까운 결과가 나타난다.


### 실행 결과
![image5](https://github.com/user-attachments/assets/2215c0c0-5406-4b98-ac17-ae1d4b68197a)


---




## 과제 4

고정값 128 대신 이미지의 **실제 평균값**을 기준으로 명암비를 조절하는 프로그램이다.

---

### main()

lenna.bmp의 픽셀 평균을 구한 뒤 `dst = src + (src - avg) * alpha` 공식으로 명암비를 조정한 결과를 출력한다.

```cpp
int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);	// lenna.bmp를 그레이스케일로 읽기
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

	Mat dst(src.rows, src.cols, src.type());	// src와 동일한 크기·타입의 출력 이미지 생성

	Scalar avg = mean(src);	// 이미지 전체 픽셀의 평균값 계산
	float alpha = 1.f;		// 명암비 조정 계수

	cout << "src의 평균값 : " << avg[0] << endl;	// 평균값 출력

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + (src.at<uchar>(j, i) - avg[0]) * alpha);
			// dst = src + (src - avg) * alpha: 실제 평균을 기준으로 명암비 조정
		}
	}

	imshow("src", src);	// 원본 이미지 출력
	imshow("dst", dst);	// 명암비 조정된 이미지 출력
	waitKey();
	return 0;
}
```

### 실행 결과
![image6](https://github.com/user-attachments/assets/9af9f700-ed15-4078-9e5c-7dd345fa45de)

