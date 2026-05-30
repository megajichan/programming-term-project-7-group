#include "Simulator.h"      // Simulator 클래스를 사용하기 위해 헤더 파일을 가져옵니다.
#include <iostream>         // 콘솔에 글자를 출력하기 위한 표준 입출력 라이브러리입니다.
#include <map>              // 이름과 값을 짝지어 저장하는 '사전' 같은 자료구조를 사용합니다.
#include <string>           // 문자열 처리를 위한 표준 라이브러리입니다.

// [소멸자]: 시뮬레이터가 종료될 때 리스트에 담긴 모든 게이트 메모리를 삭제합니다.
Simulator::~Simulator() { for (auto g : circuit) delete g; }

// [함수]: 새로운 게이트의 주소를 받아서 circuit 리스트에 추가합니다.
void Simulator::addGate(Gate* g) { circuit.push_back(g); }

// [함수]: 리스트에 저장된 모든 게이트를 하나씩 꺼내어 계산을 시작합니다.
void Simulator::runAll() { for (auto g : circuit) g->calculate(); }

// [함수]: AI 알고리즘을 이용해 현재 회로의 병목을 찾고 더 나은 부품을 추천합니다.
void Simulator::runAIAnalysis() {
    // 콘솔에 분석 시작을 알리는 구분선을 출력합니다.
    std::cout << "\n--- [Advanced AI Optimization Analysis] ---" << std::endl;

    // [현재 게이트 데이터베이스]: 실제 회로에 사용된 게이트들의 이름과 지연 시간(ns)을 저장합니다.
    std::map<std::string, int> currentDelay = { {"AND_1", 100}, {"OR_1", 50}, {"NOT_1", 20} };

    // [구조체]: 칩의 이름과 지연 시간을 묶어서 관리하기 위한 작은 틀을 만듭니다.
    struct ChipOption { std::string name; int delay; };

    // [교체 후보군 데이터베이스]: 성능이 더 좋은 칩들의 목록을 저장합니다.
    std::map<std::string, ChipOption> candidates = {
        {"74LS", {"74LS Series", 20}},
        {"74HC", {"74HC Series", 10}},
        {"74ACT", {"74ACT Series", 5}}
    };

    // [목표 설정]: 지연 시간이 30ns를 넘으면 문제가 있다고 판단하는 기준값입니다.
    int targetThreshold = 30;

    // [반복문]: circuit 리스트에 있는 모든 게이트를 하나씩 확인합니다.
    for (auto const& [name, delay] : currentDelay) {
        // 현재 확인 중인 게이트의 이름과 지연 시간을 출력합니다.
        std::cout << "[Analysis] Checking " << name << " (Current: " << delay << "ns)..." << std::endl;

        // [조건문]: 현재 게이트의 지연 시간이 목표치(30ns)보다 큰지 확인합니다.
        if (delay > targetThreshold) {
            // 문제가 발견되면 경고 메시지를 출력합니다.
            std::cout << ">> [Status] Critical Bottleneck Detected!" << std::endl;

            // [중첩 반복문]: 더 빠른 칩이 있는지 후보군 목록을 차례대로 살펴봅니다.
            for (auto const& [key, chip] : candidates) {
                // 후보 칩의 지연 시간이 현재 게이트보다 작으면 교체를 추천합니다.
                if (chip.delay < delay) {
                    // 추천할 칩의 이름을 출력하고 반복문을 멈춥니다(가장 빠른 칩만 추천).
                    std::cout << "   -> Recommendation: Upgrade to " << chip.name << " (" << chip.delay << "ns)" << std::endl;
                    break;
                }
            }
        }
        else {
            // 성능이 목표치 이내라면 최적 상태라고 출력합니다.
            std::cout << ">> [Status] Performance Optimal." << std::endl;
        }
    }
}