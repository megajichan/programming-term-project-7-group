#include <iostream>
#include <string>
#include "termproject.h" 

using namespace std;

int main() {
    cout << "ID: 22310682" << endl;
    cout << "Name: Eom Ju-hyun" << endl;
    cout << "-----------------------------------" << endl;

    // 언더바 2개(__)짜리 정확한 파일 이름으로 타겟 지정!
    string realPath = "C:\\Temp\\term__photo.pgm";

    cout << "Bingo! Target photo: " << realPath << endl;

    termproject myImage(realPath);

    cout << "Processing Mode 2 (Left-Right Flip)..." << endl;
    myImage.imageProc(2);
    myImage.imageWrite("C:\\Temp\\result_mode2_LR.pgm");

    cout << "Processing Mode 3 (Up-Down Flip)..." << endl;
    myImage.imageProc(3);
    myImage.imageWrite("C:\\Temp\\result_mode3_UD.pgm");

    cout << "-----------------------------------" << endl;
    cout << "Success! Check C:\\Temp folder." << endl;

    return 0;
}