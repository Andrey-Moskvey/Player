#include "selectfilewindow.h"
#include "ui_selectfilewindow.h"

selectFileWindow::selectFileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectFileWindow)
{
    ui->setupUi(this);

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    fileLeftName = settings.value("settings/left", "PathL").toString();
    fileRightName = settings.value("settings/right", "PathR").toString();
    ui->labelPathLeft->setText(fileLeftName);
    ui->labelPathRight->setText(fileRightName);
}

selectFileWindow::~selectFileWindow()
{
    delete ui;
    fileLeftName.~QString();
    fileRightName.~QString();
}

void selectFileWindow::on_pushButtonSelectLeft_clicked()
{
    fileLeftName = QFileDialog::getOpenFileName(this, "Left half", QDir::homePath());
    ui->labelPathLeft->setText(fileLeftName);
}

void selectFileWindow::on_pushButtonSelectRight_clicked()
{
    fileRightName = QFileDialog::getOpenFileName(this, "Right half", QDir::homePath());
    ui->labelPathRight->setText(fileRightName);
}


void selectFileWindow::on_pushButtonPlay_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(settingsPathToLeft, fileLeftName);
    settings.setValue(settingsPathToRight, fileRightName);
    ui->labelPathLeft->setText(fileLeftName);
    ui->labelPathRight->setText(fileRightName);
    if (not(fileLeftName == "" || fileRightName == "")) {
        flagChoice = true;
    }
}


void selectFileWindow::on_pushButtonExit_clicked()
{
    flagExit = true;
}

