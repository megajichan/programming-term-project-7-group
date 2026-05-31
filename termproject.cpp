#include "termproject.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// 1. 생성자 (P5 바이너리 읽기)
termproject::termproject(string fname) {
    ifstream fin(fname, ios::in | ios::binary);
    if (!fin.is_open()) {
        cout << "파일을 열 수 없습니다: " << fname << endl;
        return;
    }

    string magicNum;
    int maxVal;

    fin >> magicNum >> cols >> rows >> maxVal;
    fin.get(); // 공백 무시

    pixelValues = new unsigned char[rows * cols];
    pixelProcessed = new unsigned char[rows * cols];

    fin.read(reinterpret_cast<char*>(pixelValues), rows * cols * sizeof(unsigned char));
    fin.close();
}

// 2. 영상 처리 함수 (텀프 전용 4가지 모드 완벽 탑재)
int termproject::imageProc(int Mode) {
    int totalPixels = rows * cols;

    // Mode 0, 1: 픽셀을 순서대로 하나씩 처리해도 되는 경우 (1차원 루프)
    if (Mode == 0 || Mode == 1) {
        for (int i = 0; i < totalPixels; i++) {
            if (Mode == 0) {
                // Mode 0: 이진화 (100 기준)
                if (pixelValues[i] > 100) pixelProcessed[i] = 255;
                else pixelProcessed[i] = 0;
            }
            else if (Mode == 1) {
                // Mode 1: 색상 반전
                pixelProcessed[i] = 255 - pixelValues[i];
            }
        }
    }
    // Mode 2, 3: 가로(x), 세로(y) 좌표를 뒤집어야 하는 경우 (2차원 루프)
    else if (Mode == 2) {
        // Mode 2: 좌우 반전 (거울 모드)
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                int original_idx = y * cols + x;
                int flipped_idx = y * cols + (cols - 1 - x); // 가로(x)만 거꾸로 뺌
                pixelProcessed[flipped_idx] = pixelValues[original_idx];
            }
        }
    }
    else if (Mode == 3) {
        // Mode 3: 상하 반전
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                int original_idx = y * cols + x;
                int flipped_idx = (rows - 1 - y) * cols + x; // 세로(y)만 거꾸로 뺌
                pixelProcessed[flipped_idx] = pixelValues[original_idx];
            }
        }
    }
    return 0;
}

// 3. 파일 저장 함수 (P5 바이너리 쓰기)
int termproject::imageWrite(string fname) {
    ofstream fout(fname, ios::out | ios::binary);
    if (!fout.is_open()) return -1;

    fout << "P5\n" << cols << " " << rows << "\n255\n";
    fout.write(reinterpret_cast<const char*>(pixelProcessed), rows * cols * sizeof(unsigned char));
    fout.close();
    return 0;
}

// 4. 소멸자
termproject::~termproject(void) {
    if (pixelValues != NULL) delete[] pixelValues;
    if (pixelProcessed != NULL) delete[] pixelProcessed;
}