#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

Mat img;
int clicked_idx = -1;								// 현재 클릭된 버튼 인덱스 (-1: 없음)
vector<string> colors = { "Red", "Green", "Blue" };	// 버튼 레이블 목록

void on_mouse(int event, int x, int y, int flags, void* userdata);
void DrawUI(Mat& img);

int main(void) {
    namedWindow("img");
    setMouseCallback("img", on_mouse);	// 마우스 콜백 등록

    while (true) {
        img = Mat(300, 500, CV_8UC1, 255);	// 매 프레임 흰색 이미지 새로 생성
        DrawUI(img);						// UI 버튼 그리기
        imshow("img", img);
        if (waitKey(10) == 'q') break; 		// 'q': 종료
    }

    destroyAllWindows();
    return 0;
}

int GetButtonIndex(int x, int y) {
    if (x >= 0 && x <= 200) {				// x 좌표가 버튼 영역(0~200) 내에 있는 경우
        if (y >= 0 && y < 100) return 0;	// 첫 번째 버튼 (Red)
        if (y >= 100 && y < 200) return 1;	// 두 번째 버튼 (Green)
        if (y >= 200 && y < 300) return 2;	// 세 번째 버튼 (Blue)
    }
    return -1;								// 버튼 영역 외 클릭
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        clicked_idx = GetButtonIndex(x, y);	// 좌클릭: 해당 버튼 인덱스 저장
    }
    else if (event == EVENT_LBUTTONUP) {
        clicked_idx = -1;					// 좌클릭 해제: 선택 해제
    }
}

void DrawUI(Mat& img) {
    for (int i = 0; i < 3; i++) {
        Rect rc(0, 100 * i, 200, 100);		// i번째 버튼 영역 (높이 100씩)

        if (i == clicked_idx) {				// 클릭된 버튼: 반전 표시
            rectangle(img, rc, 0, -1); 		// 검은색으로 채우기 (반전)
            putText(img, colors[i], Point(40, 60 + 100 * i), FONT_HERSHEY_COMPLEX, 1, 255, 2);
            // 흰색 텍스트로 버튼 레이블 출력

            string msg = colors[i] + " pressed";
            putText(img, msg, Point(220, 160), FONT_HERSHEY_COMPLEX, 0.7, 0, 1);
            // 오른쪽 영역에 "색상 pressed" 메시지 출력
        }
        else {								// 비클릭 버튼: 테두리만 표시
            rectangle(img, rc, 0, 2);		// 검은색 테두리 사각형
            putText(img, colors[i], Point(40, 60 + 100 * i), FONT_HERSHEY_COMPLEX, 1, 0, 2);
            // 검은색 텍스트로 버튼 레이블 출력
        }
    }
}
