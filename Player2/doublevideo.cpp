#include "doublevideo.h"

//using namespace cv;

DoubleVideo::DoubleVideo(){}

DoubleVideo::~DoubleVideo() {
    cap_left.~VideoCapture();
    cap_right.~VideoCapture();
    pic0.~QImage();
    pic1.~QPixmap();
    frame.~Mat();
    frame_left.~Mat();
    frame_right.~Mat();
}

void DoubleVideo::capConnection(std::string pathToLeft, std::string pathToRight) {
    cap_left = cv::VideoCapture(pathToLeft);
    //cap_left = cv::VideoCapture(pathToLeft, cv::CAP_FFMPEG);
    cap_right = cv::VideoCapture(pathToRight);
    //qDebug() << "fps before:" << cap_left.get(cv::CAP_PROP_FPS) << cap_right.get(cv::CAP_PROP_FPS);
}

QPixmap DoubleVideo::getNewFrame(int imageWidth, int imageHeight)
{
    bSuccess_left = cap_left.read(frame_left);
    bSuccess_right = cap_right.read(frame_right);
    if (bSuccess_left && bSuccess_right)
    {
        cv::hconcat(frame_left, frame_right, frame);
        cv::resize(frame, frame, cv::Size(imageWidth, imageHeight));
        cv::cvtColor(frame, frame,  cv::COLOR_RGB2BGR);
        pic0 = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        pic1 = QPixmap::fromImage(pic0);
        return pic1;
    }
    return pic1;
}

bool DoubleVideo::setNewFrame(int pos) {
    qDebug() <<  cap_left.get(cv::CAP_PROP_POS_FRAMES) << cap_right.get(cv::CAP_PROP_POS_FRAMES);
    bool result = cap_left.set(cv::CAP_PROP_POS_FRAMES, pos) && cap_right.set(cv::CAP_PROP_POS_FRAMES, pos);
    qDebug() <<  cap_left.get(cv::CAP_PROP_POS_FRAMES) << cap_right.get(cv::CAP_PROP_POS_FRAMES);
    return result;
}
