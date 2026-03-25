#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

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
