#include "mainwindow.h"
#include "./ui_mainwindow.h"

std::string timeFormat(int nn) {
    if (nn < 10) {
        return "0" + std::to_string(nn);
    } else {
        return std::to_string(nn);
    }
}

MainWindow::MainWindow(std::string pathToLeftVid, std::string pathToRightVid, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tmr = new QTimer();
    SliderTime = new QSlider(Qt::Horizontal);
    ui->SliderTime->setMinimum(0);
    ui->SliderTime->setMaximum(lengthInS);
    SliderTime->setSingleStep(1);
    length = "/" + timeFormat(lengthInS / 3600) + ":" + timeFormat((lengthInS % 3600) / 60) + ":" + timeFormat(lengthInS % 60);
    tmr->setInterval(900/FPS);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateFrame()));
    tmr->start();
    pathToLeftVideo = pathToLeftVid;
    pathToRightVideo = pathToRightVid;
    ui->groupBoxSpeed->setVisible(flagSpeed);
    ui->groupBoxSize->setVisible(flagSize);
}

MainWindow::~MainWindow()
{
    delete ui;
    tmr->~QTimer();
    SliderTime->~QSlider();
}

void MainWindow::updateFrame()
{
    if (!flagCapConnection) {
        IKI.DoubleVideo::capConnection(pathToLeftVideo, pathToRightVideo);
        flagCapConnection = true;
        //FPS_orig = IKI.cap_left.get(cv::CAP_PROP_FPS);
        //qDebug() << "fps:" << IKI.cap_left.get(cv::CAP_PROP_FPS);
        //FPS = FPS_orig;

        //lengthInS = IKI.cap_left.get(cv::CAP_PROP_FRAME_COUNT) / FPS_orig;
        ui->SliderTime->setMaximum(lengthInS);
        length = "/" + timeFormat(lengthInS / 3600) + ":" + timeFormat((lengthInS % 3600) / 60) + ":" + timeFormat(lengthInS % 60);
        MainWindow::changeSize(1, "1/2 FHD");
    }
    if (flagPlay && hh * 3600 + mm * 60 + ss < lengthInS) {
        ui->labelFrameImg->setPixmap(IKI.DoubleVideo::getNewFrame(imageWidth, imageHeight));
    }
}

void MainWindow::updateTime()
{
    if (flagPlay && hh * 3600 + mm * 60 + ss < lengthInS) {
        c++;
    }
    if (c >= FPS_orig) {
        ss += 1;
        c = 0;
    }
    if (ss == 60) {
        mm++;
        ss = 0;
    }
    if (mm == 60) {
        hh++;
        mm = 0;
    }
    counter = hh * 3600 + mm * 60 + ss;
    ui->SliderTime->setSliderPosition(counter);
    //ui->SliderTime->setValue(counter);
    timer = timeFormat(hh) + ":" + timeFormat(mm) + ":" + timeFormat(ss) + length;
    ui->labelTimeViewer->setText(QString::fromStdString(timer));
}

void MainWindow::on_pushButtonPlay_clicked()
{
    if (flagPlay) {
        flagPlay = false;
    } else {
        flagPlay = true;
    }
}

void MainWindow::on_pushButtonSpeed_clicked()
{
    if (flagSpeed) {
        flagSpeed = false;
    } else {
        flagSpeed = true;
    }
    ui->groupBoxSpeed->setVisible(flagSpeed);
}

void MainWindow::on_pushButtonSize_clicked()
{
    if (flagSize) {
        flagSize = false;
    } else {
        flagSize = true;
    }
    ui->groupBoxSize->setVisible(flagSize);
}


void MainWindow::on_SliderTime_sliderPressed()
{
    flagPlayFreeze = flagPlay;
    flagPlay = false;
}

void MainWindow::on_SliderTime_sliderReleased()
{
    flagPlay = flagPlayFreeze;
    qDebug() << (ui->SliderTime->value()) * FPS_orig;
    bSuccessSetNewFrame = IKI.DoubleVideo::setNewFrame((100) * FPS_orig);
    qDebug() << "after";
}

void MainWindow::on_SliderTime_valueChanged(int value)
{
    hh = value / 3600;
    mm = (value % 3600) / 60;
    ss = value % 60;
}


void MainWindow::changeSpeed(float k, QString speedName)
{
    FPS = FPS_orig * k;
    ui->pushButtonSpeed->setText(speedName);
    tmr->setInterval(900/FPS);
}

void MainWindow::on_radioButtonSpeed_0_toggled(bool checked)
{
    if (checked) {
        changeSpeed(0.5, "0.5");
    }
}
void MainWindow::on_radioButtonSpeed_1_toggled(bool checked)
{
    if (checked) {
        changeSpeed(1, "1.0");
    }
}
void MainWindow::on_radioButtonSpeed_2_toggled(bool checked)
{
    if (checked) {
        changeSpeed(2, "2.0");
    }
}
void MainWindow::on_radioButtonSpeed_3_toggled(bool checked)
{
    if (checked) {
        changeSpeed(5, "5.0");
    }
}
void MainWindow::on_radioButtonSpeed_4_toggled(bool checked)
{
    if (checked) {
        changeSpeed(10, "10.0");
    }
}


void MainWindow::changeSize(double k, QString sizeName) {
    int k_imgW = 425, k_imgH = 340;
    int k_sliW = 750;
    int k_winW = 760;
    imageWidth = k_imgW * k;
    imageHeight = k_imgH * k;

    ui->pushButtonSize->setText("Размер: " + sizeName);
    ui->pushButtonPlay->setGeometry(k_sliW * k / 2 - 40, imageHeight + 60, 80, 30);
    ui->SliderTime->setGeometry(10, imageHeight + 40, k_sliW * k, 18);

    ui->pushButtonSize->setGeometry(k_winW * k - 95, 0, 95, 30);
    ui->pushButtonSpeed->setGeometry(0, 0, 100, 30);
    ui->groupBoxSize->setGeometry(k_winW * k - 95, 30, 95, 150);
    ui->groupBoxSpeed->setGeometry(0, 30, 100, 140);

    ui->labelTimeViewer->setGeometry(10, imageHeight + 70, 100, 20);
    ui->labelFrameImg->setGeometry((k_winW * k - k_imgW * k) / 2, 10, imageWidth, imageHeight);

    //QWidget::setFixedSize(k_winW * k, imageHeight + 120);
}

void MainWindow::on_radioButtonSize_0_toggled(bool checked) {
    if (checked) {
        MainWindow::changeSize(11.75, "Orig");
    }
}
void MainWindow::on_radioButtonSize_1_toggled(bool checked) {
    if (checked) {
        MainWindow::changeSize(9.6, "4K");
    }
}
void MainWindow::on_radioButtonSize_2_toggled(bool checked) {
    if (checked) {
        MainWindow::changeSize(6, "1/2 Orig");
    }
}
void MainWindow::on_radioButtonSize_3_toggled(bool checked) {
    if (checked) {
        MainWindow::changeSize(2, "FHD");
    }
}
void MainWindow::on_radioButtonSize_4_toggled(bool checked) {
    if (checked) {
        MainWindow::changeSize(1, "1/2 FHD");
    }
}
