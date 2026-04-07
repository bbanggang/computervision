#include "opencv2/opencv.hpp"
#include <vector>
using namespace std;
using namespace cv;

void DrawShape(Mat& roi, int type) {
	int w = roi.cols;
	int h = roi.rows;
	int margin = 50; 						// 도형과 영역 경계 사이의 여백
	Scalar white(255, 255, 255); 			// 도형 색상: 흰색
	int thickness = 5;						// 도형 선 두께
	if (type == 0) { 						// type 0: 사각형
		rectangle(roi, Rect(margin, margin, w - 2 * margin, h - 2 * margin), white, thickness);
	}
	else if (type == 1) { 					// type 1: 원
		circle(roi, Point(w / 2, h / 2), min(w, h) / 2 - margin, white, thickness);	// ROI 중심에 내접하는 원
	}
	else if (type == 2) { 					// type 2: X자 대각선
		line(roi, Point(margin, margin), Point(w - margin, h - margin), white, thickness);		// 좌상 → 우하 대각선
		line(roi, Point(w - margin, margin), Point(margin, h - margin), white, thickness);		// 우상 → 좌하 대각선
	}
}

void DrawColorBox(Mat& img) {
	int num_sections = 3;								// 구역 수
	int section_w = img.cols / num_sections;			// 각 구역의 너비
	vector<Scalar> colors = { Scalar(255, 0, 0), Scalar(0, 255, 0), Scalar(0, 0, 255) };	// 파랑, 초록, 빨강
	for (int i = 0; i < num_sections; i++) {
		Rect rect_roi(i * section_w, 0, section_w, img.rows);	// i번째 구역의 ROI 정의
		Mat roi = img(rect_roi);							// 원본 이미지에서 ROI 참조
		roi.setTo(colors[i % colors.size()]);				// 해당 구역을 색상으로 채우기
		DrawShape(roi, i);									// 구역 인덱스에 맞는 도형 그리기 (0: 사각형, 1: 원, 2: X자)
	}
}

int main() {
	Mat img(200, 600, CV_8UC3, Scalar(0, 0, 0));	// 200x600 크기의 검은색 3채널 이미지 생성
	DrawColorBox(img);								// 색상 구역 및 도형 그리기
	imshow("src", img);								// 결과 이미지 출력
	waitKey(0);										// 키 입력 대기 (창 유지)
	return 0;
}
