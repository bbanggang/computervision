#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

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
