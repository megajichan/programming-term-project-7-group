#include "mainwindow.h"
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. 순수 C++ 클래스로 이미지 로드
    myCppImage.load("dummy_path.jpg");

    // 2. UI 위젯 생성
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    
    processButton = new QPushButton("C++ 클래스로 색상 반전하기", this);

    // 3. 레이아웃 배치 (여백 설정)
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(20, 20, 20, 20); // 상하좌우 여백 20px
    layout->addWidget(imageLabel);
    layout->addWidget(processButton);
    setCentralWidget(centralWidget);

    // 4. 시그널-슬롯 연결
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);

    // 5. 초기 이미지 표시
    displayCustomImage();

    this->resize(500, 450);
    this->setWindowTitle("C++ 클래스 QT 연동 예제");
}

MainWindow::~MainWindow() {}

// [핵심] 순수 C++ 이미지 데이터를 QT 위젯에 맞게 변환하여 띄우는 함수
void MainWindow::displayCustomImage()
{
    if (myCppImage.data.empty()) return;

    // 순수 C++ 바이트 배열(data.data())을 기반으로 QImage 객체를 생성합니다.
    // Format_RGB888은 가로 세로 채널당 1바이트씩 RGB 순서로 배열되어 있을 때 사용합니다.
    QImage qImage(
        myCppImage.data.data(),            // 픽셀 데이터 시작 주소 (unsigned char*)
        myCppImage.width,                  // 가로 크기
        myCppImage.height,                 // 세로 크기
        myCppImage.width * myCppImage.channels, // 한 줄의 바이트 수 (Stride / BytesPerLine)
        QImage::Format_RGB888              // QT 이미지 포맷
    );

    // QLabel에 띄우기 위해 QPixmap으로 변환 후 전달
    imageLabel->setPixmap(QPixmap::fromImage(qImage));
}

// 버튼 클릭 시 작동하는 슬롯 함수
void MainWindow::onProcessButtonClicked()
{
    // 1. 순수 C++ 클래스 내부의 연산 알고리즘 호출 (QT 기능 아님)
    myCppImage.invertColors();

    // 2. 연산이 끝난 후 변경된 데이터를 QT 화면에 다시 반영
    displayCustomImage();
