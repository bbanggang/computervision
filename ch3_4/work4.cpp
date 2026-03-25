#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

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
