#ifndef GATE_H
#define GATE_H
#include <string>

// [클래스 설명]: 모든 논리 게이트의 기본 형태를 정의하는 추상 클래스
class Gate {
protected:
    std::string name; // [변수 설명]: 게이트를 구분하기 위한 고유 명칭
public:
    Gate(std::string n) : name(n) {} // [생성자]: 게이트 이름을 입력받아 초기화
    virtual ~Gate() {} // [소멸자]: 자식 클래스 메모리 해제를 위한 가상 소멸자

    // [함수 설명]: 하드웨어 지연을 반영하여 논리 연산을 수행하는 함수
    virtual void calculate() = 0;

    std::string getName() { return name; } // [함수 설명]: 게이트 이름을 외부로 반환
};

// [협업 지점: 엄주현 님] 영상처리 데이터는 여기서 주입됩니다.
class AndGate : public Gate {
    bool in1, in2; // [변수 설명]: AND 연산을 위해 필요한 두 개의 입력값
public:
    AndGate(std::string n) : Gate(n), in1(false), in2(false) {}
    // [함수 설명]: 영상처리 모듈에서 값을 받아와 저장하는 함수
    void setInput(bool a, bool b) { in1 = a; in2 = b; }
    void calculate() override;
};

class OrGate : public Gate {
    bool in1, in2; // [변수 설명]: OR 연산을 위한 두 개의 입력값
public:
    OrGate(std::string n) : Gate(n), in1(false), in2(false) {}
    void setInput(bool a, bool b) { in1 = a; in2 = b; }
    void calculate() override;
};

class NotGate : public Gate {
    bool in; // [변수 설명]: NOT 연산을 위한 하나의 입력값
public:
    NotGate(std::string n) : Gate(n), in(false) {}
    void setInput(bool a) { in = a; }
    void calculate() override;
};
#endif