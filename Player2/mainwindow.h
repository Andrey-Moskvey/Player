#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>

#include "doublevideo.h"


#include <QObject>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QSlider>
#include <QString>

void displayFrame(QPixmap picture);

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::string pathToLeftVid, std::string pathToRightVid, QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    ~MainWindow();
    int FPS = 4;
    int FPS_orig = FPS;
    int counter = 0;
    int frames = 0;
    std::string timer = "00:00:00";
    std::string length = "/00:00:00";
    std::string pathToLeftVideo;
    std::string pathToRightVideo;
    int hh = 0, mm = 0, ss = 0;
    double c = 0;
    int lengthInS = 8587;
    bool flagPlay = true;
    bool flagPlayFreeze;
    bool flagSpeed = false;
    bool flagSize = false;
    bool bSuccessSetNewFrame;
    bool flagCapConnection = false;
    int imageWidth = 850, imageHeight = 680;
    DoubleVideo IKI;


private:
    QTimer *tmr;
    QSlider *SliderTime;



private slots:
    void updateTime();
    void updateFrame();
    void on_pushButtonPlay_clicked();
    void on_pushButtonSpeed_clicked();
    void on_pushButtonSize_clicked();
    void on_SliderTime_sliderPressed();
    void on_SliderTime_sliderReleased();
    void on_SliderTime_valueChanged(int value);
    void changeSpeed(float k, QString speedName);
    void on_radioButtonSpeed_0_toggled(bool checked);
    void on_radioButtonSpeed_1_toggled(bool checked);
    void on_radioButtonSpeed_2_toggled(bool checked);
    void on_radioButtonSpeed_3_toggled(bool checked);
    void on_radioButtonSpeed_4_toggled(bool checked);
    void changeSize(double k, QString sizeName);
    void on_radioButtonSize_0_toggled(bool checked);
    void on_radioButtonSize_1_toggled(bool checked);
    void on_radioButtonSize_2_toggled(bool checked);
    void on_radioButtonSize_3_toggled(bool checked);
    void on_radioButtonSize_4_toggled(bool checked);
};

#endif // MAINWINDOW_H
