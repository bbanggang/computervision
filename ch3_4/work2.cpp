#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat img1 = (Mat_<int>(3, 5) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);	// 3x5 int 행렬 초기화 (값 1~15)
	cout << img1 << endl;																	// 전체 행렬 출력
	Mat img2 = img1(Rect(Point(2, 1), Size(3, 2))).clone();	// 좌측 상단 (2, 1)에서 3x2 크기의 영역을 ROI로 지정 후 독립 복사
	cout << img2 << endl;								// 추출된 부분 행렬 출력
	return 0;
}
