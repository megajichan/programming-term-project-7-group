#include "mainwindow.h"           // MainWindow 헤더 포함
#include "./ui_mainwindow.h"      // Qt Designer가 자동 생성한 UI 헤더 포함
#include <QCoreApplication>       // applicationDirPath() 사용을 위해 포함
#include <QImage>                 // QImage 클래스 포함
#include <QPixmap>                // QPixmap 클래스 포함
#include <QDebug>                 // 디버그 출력(qDebug) 포함
#include <QMessageBox>            // 메시지 다이얼로그 포함

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)         // 부모 클래스 생성자 호출
    , ui(new Ui::MainWindow)      // UI 객체 동적 생성
{
    ui->setupUi(this);            // Qt Designer 레이아웃을 이 윈도우에 적용

    // 실행 파일 위치 기준으로 input.png 절대 경로 생성
    QString inputPath = QCoreApplication::applicationDirPath() + "/input.png";

    QMessageBox::information(this, "경로 확인", inputPath); // 경로를 팝업으로 확인
    qDebug() << "이미지 로드 시도 경로:" << inputPath;      // 디버그 콘솔에도 출력

    myTermObject = new termproject(inputPath); // 이미지 처리 객체 생성 및 파일 로드
    displayImage();                            // 프로그램 시작 시 원본 이미지 즉시 출력
}

MainWindow::~MainWindow() {
    if (myTermObject != nullptr) { // 이미지 처리 객체가 존재하면
        delete myTermObject;       // 동적 할당 해제
        myTermObject = nullptr;    // 댕글링 포인터 방지
    }
    delete ui;                     // UI 객체 해제
}

void MainWindow::displayImage() {
    // 데이터가 없으면 출력하지 않고 종료
    if (myTermObject == nullptr || myTermObject->getProcessedData() == nullptr) {
        qDebug() << "화면에 표시할 이미지 데이터가 없습니다. 경로를 확인하세요.";
        return;
    }

    // 처리된 픽셀 배열로 QImage 생성 (흑백 1채널 포맷)
    QImage qImage(
        myTermObject->getProcessedData(), // 픽셀 배열 시작 주소
        myTermObject->getWidth(),         // 이미지 가로 픽셀 수
        myTermObject->getHeight(),        // 이미지 세로 픽셀 수
        myTermObject->getWidth(),         // 한 줄당 바이트 수 (흑백은 가로와 동일)
        QImage::Format_Grayscale8         // 8비트 흑백 포맷
        );

    // 라벨 크기에 맞게 비율 유지하며 이미지 축소/확대 후 출력
    ui->label_group->setPixmap(QPixmap::fromImage(qImage).scaled(
        ui->label_group->width(),         // 라벨 너비에 맞춤
        ui->label_group->height(),        // 라벨 높이에 맞춤
        Qt::KeepAspectRatio,              // 원본 비율 유지
        Qt::SmoothTransformation          // 부드러운 보간 적용
        ));
    ui->label_group->setAlignment(Qt::AlignCenter); // 라벨 중앙 정렬
}

// 1. 이진화 버튼 클릭 시 (Mode 0)
void MainWindow::on_btnBinarize_clicked() {
    if (myTermObject != nullptr) {  // 객체가 존재할 때만 처리
        myTermObject->imageProc(0); // Mode 0: 이진화 처리
        displayImage();             // 처리 결과 화면 갱신
    }
}

// 2. 색상 반전 버튼 클릭 시 (Mode 1)
void MainWindow::on_btnInvert_clicked() {
    if (myTermObject != nullptr) {  // 객체가 존재할 때만 처리
        myTermObject->imageProc(1); // Mode 1: 색상 반전 처리
        displayImage();             // 처리 결과 화면 갱신
    }
}

// 3. 좌우 반전 버튼 클릭 시 (Mode 2)
void MainWindow::on_btnFlipLR_clicked() {
    if (myTermObject != nullptr) {  // 객체가 존재할 때만 처리
        myTermObject->imageProc(2); // Mode 2: 좌우 반전 처리
        displayImage();             // 처리 결과 화면 갱신
    }
}

// 4. 상하 반전 버튼 클릭 시 (Mode 3)
void MainWindow::on_btnFlipUD_clicked() {
    if (myTermObject != nullptr) {  // 객체가 존재할 때만 처리
        myTermObject->imageProc(3); // Mode 3: 상하 반전 처리
        displayImage();             // 처리 결과 화면 갱신
    }
}

// 5. 저장 버튼 클릭 시
void MainWindow::on_btnSave_clicked() {
    if (myTermObject != nullptr) {  // 객체가 존재할 때만 처리
        // 실행 파일 위치 기준으로 output.pgm 저장 경로 생성
        QString outputPath = QCoreApplication::applicationDirPath() + "/termproject/output.pgm";

        if (myTermObject->imageWrite(outputPath) == 0) { // 저장 성공 시 (반환값 0)
            QMessageBox::information(this, "저장 완료",
                                     "성공적으로 이미지가 저장되었습니다!\n 경로: " + outputPath);
        } else {                                          // 저장 실패 시
            QMessageBox::critical(this, "저장 실패", "파일을 저장할 수 없습니다.");
        }
    }
}

// 6. 논리회로 시뮬레이터 버튼 클릭 시
void MainWindow::on_btnLogicSim_clicked() {
    if (!simWidget) {                                      // 아직 생성되지 않았으면
        simWidget = new LogicSimWidget();                  // 시뮬레이터 위젯 새로 생성
        simWidget->setWindowTitle("논리 게이트 전파지연 시뮬레이터"); // 창 제목 설정
        simWidget->resize(900, 520);                       // 창 초기 크기 설정
    }
    simWidget->show();            // 창 표시
    simWidget->raise();           // 다른 창 위로 올림
    simWidget->activateWindow();  // 포커스 활성화
}
