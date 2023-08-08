#ifndef DOUBLEVIDEO_H
#define DOUBLEVIDEO_H

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include <string>

class DoubleVideo : public QObject
{
    Q_OBJECT
public:
    DoubleVideo();
    ~DoubleVideo();
    void capConnection(std::string pathToLeft, std::string pathToRight);
    QPixmap getNewFrame(int imageWidth, int imageHeight);
    cv::VideoCapture cap_left;
    cv::VideoCapture cap_right;
    bool setNewFrame(int pos);
private:
    QImage pic0;
    QPixmap pic1;
    cv::Mat frame, frame_left, frame_right;
    bool bSuccess_left;
    bool bSuccess_right;

};

#endif // DOUBLEVIDEO_H
