#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <vector>
#include "Gate.h"

// [클래스 설명]: 전체 시스템의 게이트들을 목록으로 관리하고 실행하는 엔진
class Simulator {
    // [변수 설명]: 등록된 모든 게이트 객체들의 주소를 담아두는 동적 배열
    std::vector<Gate*> circuit;
public:
    ~Simulator();
    void addGate(Gate* g); // [함수 설명]: 게이트를 회로 목록에 추가
    void runAll();         // [함수 설명]: 등록된 모든 게이트의 연산을 순차 실행
    void runAIAnalysis();  // [함수 설명]: AI 기반 성능 분석 및 최적화 추천
};
#endif