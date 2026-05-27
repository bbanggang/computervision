#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) { cerr << "Camera open failed!" << endl; return -1; }

	int mode = 1;		// 1: 정상, 2: 2배 확대, 3: 1/2 축소
	int prevMode = 0;	// 이전 모드 (0으로 초기화하여 시작 시 행렬 출력 유도)

	Mat frame, dst;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		int cols = frame.cols;
		int rows = frame.rows;

		Point2f srcPts[3];
		srcPts[0] = Point2f(0, 0);			// 좌측상단
		srcPts[1] = Point2f(cols - 1, 0);		// 우측상단
		srcPts[2] = Point2f(cols - 1, rows - 1);	// 우측하단

		Point2f dstPts[3];
		Size dsize;

		if (mode == 2) {
			// a키: 2배 확대 → 각 점의 x, y 좌표를 2배
			dstPts[0] = Point2f(0, 0);
			dstPts[1] = Point2f(2 * (cols - 1), 0);
			dstPts[2] = Point2f(2 * (cols - 1), 2 * (rows - 1));
			dsize = Size(cols * 2, rows * 2);	// 결과영상 크기 2배
		} else if (mode == 3) {
			// b키: 1/2 축소 → 각 점의 x, y 좌표를 1/2배
			dstPts[0] = Point2f(0, 0);
			dstPts[1] = Point2f((cols - 1) / 2.0f, 0);
			dstPts[2] = Point2f((cols - 1) / 2.0f, (rows - 1) / 2.0f);
			dsize = Size(cols / 2, rows / 2);	// 결과영상 크기 1/2배
		} else {
			// c키 또는 초기: 정상 크기 → 좌표 변환 없음 (항등 변환)
			dstPts[0] = Point2f(0, 0);
			dstPts[1] = Point2f(cols - 1, 0);
			dstPts[2] = Point2f(cols - 1, rows - 1);
			dsize = Size(cols, rows);		// 결과영상 크기 동일
		}

		Mat M = getAffineTransform(srcPts, dstPts);	// 아핀 변환 행렬 계산

		// 모드가 바뀐 경우에만 변환 행렬을 터미널에 출력
		if (mode != prevMode) {
			string label;
			if      (mode == 2) label = "[a] 2배 확대";
			else if (mode == 3) label = "[b] 1/2 축소";
			else                label = "[c] 정상 크기";
			cout << label << " M = " << endl << M << endl;
			prevMode = mode;
		}

		warpAffine(frame, dst, M, dsize);		// 아핀 변환 적용
		imshow("dst", dst);

		int key = waitKey(30);
		if      (key == 'q') break;		// q: 종료
		else if (key == 'a') mode = 2;	// a: 2배 확대
		else if (key == 'b') mode = 3;	// b: 1/2 축소
		else if (key == 'c') mode = 1;	// c: 정상 크기
	}

	return 0;
}
