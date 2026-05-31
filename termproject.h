#pragma once // 헤더 파일 중복 포함 방지
#include <string>

using namespace std;

class termproject {
private:
    int rows;
    int cols;
    unsigned char* pixelValues;    // 원본 이미지 저장용 동적 할당 포인터
    unsigned char* pixelProcessed; // 영상처리된 이미지 저장용 동적 할당 포인터

public:
    termproject(string fname);        // 생성자: 파일 읽기 및 메모리 할당
    int imageProc(int Mode);        // 영상 처리 함수
    int imageWrite(string fname);   // 파일 저장 함수
    ~termproject(void);               // 소멸자: 메모리 반납
};