#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QSplitter>
#include <QPainter>          // 배경 이미지 그리기 위해 추가

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 배경 이미지 로드 (실행 파일과 같은 폴더에 background.png 넣어두세요)
    bgImage.load(QCoreApplication::applicationDirPath() + "/background.png");

    QString inputPath = QCoreApplication::applicationDirPath() + "/input.png";
    QMessageBox::information(this, "경로 확인", inputPath);
    qDebug() << "이미지 로드 시도 경로:" << inputPath;
    myTermObject = new termproject(inputPath);

    // 기존 이미지 처리 UI(centralwidget)를 메인윈도우에서 삭제 없이 분리
    QWidget *imageSide = takeCentralWidget();

    // 현재 크기로 고정 → Qt가 자동으로 줄이거나 0으로 접지 못하게 함
    imageSide->setMinimumSize(imageSide->width(), imageSide->height());

    // 논리회로 시뮬레이터 위젯 생성 (항상 화면에 표시)
    simWidget = new LogicSimWidget();
    simWidget->setMinimumSize(400, 350); // 시뮬레이터도 최소 크기 보장

    // 좌우 분할 컨테이너 생성: 왼쪽 이미지 / 오른쪽 시뮬레이터
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(imageSide);
    splitter->addWidget(simWidget);

    splitter->setCollapsible(0, false); // 왼쪽(이미지) 영역 접힘 금지
    splitter->setCollapsible(1, false); // 오른쪽(시뮬레이터) 영역 접힘 금지

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    splitter->setSizes({imageSide->width(), 300});

    setCentralWidget(splitter);
    resize(imageSide->width() + 900, qMax(imageSide->height(), 700));

    displayImage();
}

MainWindow::~MainWindow()
{
    if (myTermObject != nullptr) {
        delete myTermObject;
        myTermObject = nullptr;
    }
    delete ui;
}

// 창 배경에 이미지를 창 크기에 맞춰 꽉 채워서 그리는 함수
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!bgImage.isNull()) {
        painter.drawPixmap(rect(), bgImage.scaled(
                                       size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    QMainWindow::paintEvent(event);
}

void MainWindow::displayImage()
{
    if (myTermObject == nullptr || myTermObject->getProcessedData() == nullptr) {
        qDebug() << "화면에 표시할 이미지 데이터가 없습니다. 경로를 확인하세요.";
        return;
    }
    QImage qImage(
        myTermObject->getProcessedData(),
        myTermObject->getWidth(),
        myTermObject->getHeight(),
        myTermObject->getWidth(),
        QImage::Format_Grayscale8
        );
    ui->label_group->setPixmap(QPixmap::fromImage(qImage).scaled(
        ui->label_group->width(),
        ui->label_group->height(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        ));
    ui->label_group->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_btnBinarize_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(0);
        displayImage();
    }
}

void MainWindow::on_btnInvert_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(1);
        displayImage();
    }
}

void MainWindow::on_btnFlipLR_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(2);
        displayImage();
    }
}

void MainWindow::on_btnFlipUD_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageProc(3);
        displayImage();
    }
}

void MainWindow::on_btnSave_clicked()
{
    if (myTermObject != nullptr) {
        QString outputPath = QCoreApplication::applicationDirPath() + "/termproject/output.pgm";
        if (myTermObject->imageWrite(outputPath) == 0) {
            QMessageBox::information(this, "저장 완료", "성공적으로 이미지가 저장되었습니다!\n 경로: " + outputPath);
        } else {
            QMessageBox::critical(this, "저장 실패", "파일을 저장할 수 없습니다.");
        }
    }
}

void MainWindow::on_btnReset_clicked()
{
    if (myTermObject != nullptr) {
        myTermObject->imageReset();
        displayImage();
    }
}
