#include "Gate.h"
#include <iostream>
#include <chrono>
#include <thread>

// [물리 시뮬레이션] 각 게이트의 동작 속도를 구현합니다.
void AndGate::calculate() {
    // 하드웨어 특성 반영: AND 게이트 반응 속도 100ms
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "[AND] " << name << " result: " << (in1 && in2) << std::endl;
}

void OrGate::calculate() {
    // 하드웨어 특성 반영: OR 게이트 반응 속도 50ms
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "[OR] " << name << " result: " << (in1 || in2) << std::endl;
}

void NotGate::calculate() {
    // 하드웨어 특성 반영: NOT 게이트 반응 속도 20ms
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::cout << "[NOT] " << name << " result: " << (!in) << std::endl;
}