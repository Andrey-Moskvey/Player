#ifndef SELECTFILEWINDOW_H
#define SELECTFILEWINDOW_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QSettings>

//#include <iostream>

#define ORGANIZATION_NAME "IKI"
#define ORGANIZATION_DOMAIN "www.iki.com"
#define APPLICATION_NAME "Player"

#define settingsPathToLeft "settings/left"
#define settingsPathToRight "settings/right"

namespace Ui {
class selectFileWindow;
}

class selectFileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit selectFileWindow(QWidget *parent = nullptr);
    ~selectFileWindow();
    QString fileLeftName = "";
    QString fileRightName = "";
    bool flagChoice = false;
    bool flagExit = false;

private slots:
    void on_pushButtonSelectLeft_clicked();
    void on_pushButtonSelectRight_clicked();
    void on_pushButtonPlay_clicked();
    void on_pushButtonExit_clicked();

private:
    Ui::selectFileWindow *ui;
};


#endif // SELECTFILEWINDOW_H
