# ch 7-1 필터링

## 과제 1

`rose.bmp`를 그레이스케일로 읽고 3×3 평균 블러링 필터를 적용하여 결과를 출력하는 프로그램이다.

---

### 필터 마스크의 역할

```
1/9  1/9  1/9
1/9  1/9  1/9
1/9  1/9  1/9
```

모든 계수가 1/9로 동일하여 중심 픽셀과 주변 8개 픽셀의 평균값으로 해당 위치를 대체한다. 이 **평균 블러링(Mean Blur)** 마스크는 고주파 성분(노이즈, 경계선)을 억제하고 영상을 전체적으로 부드럽게(흐릿하게) 만드는 저역 통과 필터(Low-Pass Filter) 역할을 수행한다.

---

### main()

`filter2D()`에 평균 블러링 마스크를 전달하여 영상을 평활화하고 원본과 결과를 출력한다.

```cpp
int main(void)
{
    Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    float data[] = { 1.0/9.0, 1.0/9.0, 1.0/9.0,
                     1.0/9.0, 1.0/9.0, 1.0/9.0,
                     1.0/9.0, 1.0/9.0, 1.0/9.0 };
    Mat emboss(3, 3, CV_32FC1, data);
    Mat dst;
    filter2D(src, dst, -1, emboss, Point(-1, -1), 0);
    imshow("src", src);
    imshow("dst", dst);
    waitKey();
    return 0;
}
```

### 실행 결과

![image1](https://github.com/user-attachments/assets/35a0c7b7-6506-436a-a73a-77c6ce402f89)


## 과제 2

`rose.bmp`를 그레이스케일로 읽고 3×3 샤프닝 필터를 적용하여 결과를 출력하는 프로그램이다.

---

### 필터 마스크의 역할

```
-1  -1  -1
-1   9  -1
-1  -1  -1
```

중심 계수가 9이고 주변 8개 계수가 모두 -1이다. 이 **언샤프 마스킹(Unsharp Masking) 기반 샤프닝** 마스크는 중심 픽셀을 강하게 강조하면서 주변 픽셀 값을 빼는 방식으로, 픽셀 간 밝기 차이가 큰 경계(에지) 부분을 두드러지게 만든다. 고주파 성분을 증폭시키는 고역 통과 필터(High-Pass Filter) 역할을 수행한다.

---

### main()

`filter2D()`에 샤프닝 마스크를 전달하여 영상의 경계를 강조하고 원본과 결과를 출력한다.

```cpp
int main(void)
{
    Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    float data[] = { -1.0, -1.0, -1.0,
                     -1.0,  9.0, -1.0,
                     -1.0, -1.0, -1.0 };
    Mat emboss(3, 3, CV_32FC1, data);
    Mat dst;
    filter2D(src, dst, -1, emboss, Point(-1, -1), 0);
    imshow("src", src);
    imshow("dst", dst);
    waitKey();
    return 0;
}
```

### 실행 결과
![image2](https://github.com/user-attachments/assets/991f5efe-d111-4fe5-b952-93bc6f2889b1)



## 과제 3

`rose.bmp`를 그레이스케일로 읽고 3×3 소벨 x방향 필터를 적용하여 수직 에지를 검출하는 프로그램이다.

---

### 필터 마스크의 역할

```
-1   0   1
-2   0   2
-1   0   1
```

좌측 열은 음수(-1, -2, -1), 우측 열은 양수(1, 2, 2), 중앙 열은 0으로 구성된 **소벨 x방향(Sobel-x) 에지 검출** 마스크이다. 픽셀의 좌우 밝기 차이(수평 기울기)를 계산하여 밝기가 급격히 변화하는 수직 방향 경계선을 강조한다. 중앙 행의 계수(-2, 0, 2)에 가중치가 부여되어 노이즈에 대한 강인성이 높다.

---

### main()

`filter2D()`에 소벨 x방향 마스크를 전달하여 수직 에지를 검출하고 원본과 결과를 출력한다.

```cpp
int main(void)
{
    Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    float data[] = { -1.0, 0, 1.0,
                     -2.0, 0, 2.0,
                     -1.0, 0, 1.0 };
    Mat emboss(3, 3, CV_32FC1, data);
    Mat dst;
    filter2D(src, dst, -1, emboss, Point(-1, -1), 0);
    imshow("src", src);
    imshow("dst", dst);
    waitKey();
    return 0;
}
```

### 실행 결과
- delta가 128 일 때
![image3_1](https://github.com/user-attachments/assets/45d59c06-6517-44b2-89a6-81ba8ccdd927)
- delta가 0 일 때
![image3_2](https://github.com/user-attachments/assets/2a9c7300-d245-4ba2-bbf6-082db5037f56)



## 과제 4

마우스 이벤트에 따라 과제 1·2·3의 필터 결과를 전환하여 출력하는 프로그램이다.

- **왼쪽 버튼 클릭**: 과제 1 결과 (평균 블러링)
- **오른쪽 버튼 클릭**: 과제 2 결과 (샤프닝)
- **왼쪽 버튼 더블 클릭**: 과제 3 결과 (소벨 x방향 에지 검출)

---

### onMouse()

마우스 이벤트 종류에 따라 해당 필터 마스크를 선택하고 `filter2D()`를 호출하여 결과를 `dst` 창에 갱신한다.

```cpp
void onMouse(int event, int x, int y, int flags, void* userdata)
{
    Mat dst;

    if (event == EVENT_LBUTTONDBLCLK) {
        // 왼쪽 더블 클릭: 과제 3 소벨 x방향 에지 검출
        float data3[] = { -1.0, 0, 1.0, -2.0, 0, 2.0, -1.0, 0, 1.0 };
        Mat kernel3(3, 3, CV_32FC1, data3);
        filter2D(src, dst, -1, kernel3, Point(-1, -1), 0);
        imshow("dst", dst);
    }
    else if (event == EVENT_LBUTTONDOWN) {
        // 왼쪽 클릭: 과제 1 평균 블러링
        float data1[] = { 1.0/9.0, 1.0/9.0, 1.0/9.0,
                          1.0/9.0, 1.0/9.0, 1.0/9.0,
                          1.0/9.0, 1.0/9.0, 1.0/9.0 };
        Mat kernel1(3, 3, CV_32FC1, data1);
        filter2D(src, dst, -1, kernel1, Point(-1, -1), 0);
        imshow("dst", dst);
    }
    else if (event == EVENT_RBUTTONDOWN) {
        // 오른쪽 클릭: 과제 2 샤프닝
        float data2[] = { -1.0, -1.0, -1.0, -1.0, 9.0, -1.0, -1.0, -1.0, -1.0 };
        Mat kernel2(3, 3, CV_32FC1, data2);
        filter2D(src, dst, -1, kernel2, Point(-1, -1), 0);
        imshow("dst", dst);
    }
}
```

---

### main()

`src` 창에 마우스 콜백을 등록하고 원본 영상을 출력하며 이벤트를 대기한다.

```cpp
int main(void)
{
    src = imread("rose.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }

    namedWindow("src");
    namedWindow("dst");
    setMouseCallback("src", onMouse);

    imshow("src", src);
    imshow("dst", src);
    waitKey();
    return 0;
}
```

### 실행 결과

[video](https://github.com/user-attachments/assets/62a7f9df-ada7-47da-9470-4e4efa918aee)
