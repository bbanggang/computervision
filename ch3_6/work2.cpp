#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

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
