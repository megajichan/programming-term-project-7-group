#include "Simulator.h"
#include <iostream>

/**
 * [시스템 통합 실행 설명]
 * 이 파일은 프로젝트의 메인입니다.
 * AND, OR, NOT 게이트를 모두 생성하고 시뮬레이션합니다.
 */
int main() {
    // [엔진 시작] 시뮬레이션 관리자 객체 생성
    Simulator mySim;

    // 1. [협업: 게이트 생성]
    AndGate* and1 = new AndGate("AND_1");
    OrGate* or1 = new OrGate("OR_1"); // OR 게이트 생성 추가
    NotGate* not1 = new NotGate("NOT_1");

    // 2. [협업: 엄주현 님] 
    // 영상 처리 알고리즘의 결과값(0 또는 1)을 각 게이트에 입력합니다.
    and1->setInput(true, true);
    or1->setInput(false, true); // OR 게이트 입력값 설정
    not1->setInput(false);

    // 3. [협업: 엔진 등록]
    // 시뮬레이션할 모든 게이트 객체들의 주소를 엔진(mySim)에 등록합니다.
    mySim.addGate(and1);
    mySim.addGate(or1); // OR 게이트 엔진 등록
    mySim.addGate(not1);

    // 4. [협업: 권재호 님] 
    // GUI의 [시작] 버튼과 연결하십시오. runAll() 호출 시 물리 지연과 함께 연산이 수행됩니다.
    std::cout << "[System] Starting physical simulation..." << std::endl;
    mySim.runAll();

    // 5. [협업] 
    // 전체 연산 완료 후, 분석 로직을 호출하여 최적의 부품(74ACT 등)을 추천받습니다.
    mySim.runAIAnalysis();

    return 0;
}