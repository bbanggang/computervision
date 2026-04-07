#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void DrawGrid(Mat& img, int sections) {
    int step_w = img.cols / sections;       // 열 방향 격자 간격
    int step_h = img.rows / sections;       // 행 방향 격자 간격
    for (int i = 1; i < sections; i++) {
        line(img, Point(i * step_w, 0), Point(i * step_w, img.rows), Scalar(0, 0, 0), 1);  // 세로선 그리기
        line(img, Point(0, i * step_h), Point(img.cols, i * step_h), Scalar(0, 0, 0), 1);  // 가로선 그리기
    }
}

void SetBlueBox(Mat& img, int x, int y, int size) {
    int step_w = img.cols / 5;                              // 격자 한 칸의 너비
    int step_h = img.rows / 5;                              // 격자 한 칸의 높이
    Rect roi_rect(x * step_w, y * step_h, size * step_w, size * step_h);   // 블록 영역 계산
    Mat roi = img(roi_rect);                                // 해당 영역 ROI 참조
    roi.setTo(Scalar(255, 0, 0));                           // 파란색으로 채우기
}

int main(void) {
    int grid_cnt = 5;           // 격자 분할 수 (5x5)
    int box_size = 1;           // 블록 크기 (1칸)
    int cur_x = 2, cur_y = 2;  // 블록 초기 위치 (격자 중앙)
    while (true) {
        Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));  // 매 프레임 흰색 이미지 새로 생성
        DrawGrid(img, grid_cnt);                            // 격자선 그리기
        SetBlueBox(img, cur_x, cur_y, box_size);            // 현재 위치에 파란색 블록 그리기
        imshow("src", img);
        int key = waitKey(0);                               // 키 입력 대기
        if (key == 'q' || key == 'Q') break;               // 'q'/'Q': 종료
        int next_x = cur_x;
        int next_y = cur_y;
        if (key == 'l') next_x--;      // 'l': 좌측 이동
        else if (key == 'r') next_x++; // 'r': 우측 이동
        else if (key == 'u') next_y--; // 'u': 위쪽 이동
        else if (key == 'd') next_y++; // 'd': 아래쪽 이동
        if (next_x >= 0 && next_x <= (grid_cnt - box_size) &&
            next_y >= 0 && next_y <= (grid_cnt - box_size)) {  // 격자 경계 내에 있는지 확인
            cur_x = next_x;
            cur_y = next_y;
        }
        else {
            cout << "경계 경고: 더 이상 움직일 수 없습니다." << endl;  // 경계 초과 시 경고 출력
        }
    }
    return 0;
}
