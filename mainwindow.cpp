#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 실행 파일 위치 기준으로 'termproject' 폴더 안의 'input.pgm' 절대 경로를 생성
    QString inputPath = QCoreApplication::applicationDirPath() + "/input.png";
    QMessageBox::information(this, "경로 확인", inputPath);
    qDebug() << "이미지 로드 시도 경로:" << inputPath;

    // 이미지 객체 동적 할당 및 파일 읽기
    myTermObject = new termproject(inputPath);

    // 프로그램이 켜지자마자 원본 이미지를 라벨에 즉시 출력
    displayImage();
}

MainWindow::~MainWindow()
{
    // 소멸자에서 동적 할당 해제하여 메모리 누수 방지
    if (myTermObject != nullptr) {
        delete myTermObject;
        myTermObject = nullptr;
    }
    delete ui;
}

// 픽셀 버퍼 데이터를 가져와 QLabel에 맞게 그려주는 함수
void MainWindow::displayImage()
{
    // 데이터가 제대로 로드되지 않았으면 처리하지 않음
    if (myTermObject == nullptr || myTermObject->getProcessedData() == nullptr) {
        qDebug() << "화면에 표시할 이미지 데이터가 없습니다. 경로를 확인하세요.";
        return;
    }

    // P5 PGM은 1채널 흑백 이미지이므로 Format_Grayscale8을 사용합니다.
    QImage qImage(
        myTermObject->getProcessedData(), // 픽셀 배열 시작 주소
        myTermObject->getWidth(),         // 가로 크기
        myTermObject->getHeight(),        // 세로 크기
        myTermObject->getWidth(),         // 한 줄당 바이트 수 (흑백은 가로 크기와 동일)
        QImage::Format_Grayscale8
        );

    // ui의 label_group 크기에 맞추어 비율을 유지(KeepAspectRatio)하며 깔끔하게 출력
    ui->label_group->setPixmap(QPixmap::fromImage(qImage).scaled(
        ui->label_group->width(),
        ui->label_group->height(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        ));

    ui->label_group->setAlignment(Qt::AlignCenter);
}

// 1. 이진화 버튼 클릭 시 (Mode 0)
void MainWindow::on_btnBinarize_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(0);
        displayImage(); // 화면 갱신
    }
}

// 2. 색상 반전 버튼 클릭 시 (Mode 1)
void MainWindow::on_btnInvert_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(1);
        displayImage(); // 화면 갱신
    }
}

// 3. 좌우 반전 버튼 클릭 시 (Mode 2)
void MainWindow::on_btnFlipLR_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(2);
        displayImage(); // 화면 갱신
    }
}

// 4. 상하 반전 버튼 클릭 시 (Mode 3)
void MainWindow::on_btnFlipUD_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(3);
        displayImage(); // 화면 갱신
    }
}

// 5. 결과 저장 버튼 클릭 시
void MainWindow::on_btnSave_clicked()
{
    if (myTermObject != nullptr) {
        // 읽어왔던 폴더와 동일하게 'termproject' 폴더 안에 'output.pgm'으로 저장
        QString outputPath = QCoreApplication::applicationDirPath() + "/termproject/output.pgm";

        if (myTermObject->imageWrite(outputPath) == 0) {
            QMessageBox::information(this, "저장 완료", "성공적으로 이미지가 저장되었습니다!\n 경로: " + outputPath);
        } else {
            QMessageBox::critical(this, "저장 실패", "파일을 저장할 수 없습니다.");
        }
    }
}
