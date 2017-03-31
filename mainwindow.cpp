#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mass_rgb.h"
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mass_RGB RGB;
    uchar mas[256];
    for(int i = 0 ; i<256;i++)
    mas[i] = i;
    RGB.MassiveStreamLine(100,100, mas);
    int i;
    RGB.img->save("filename.png", "PNG");

    QPixmap *pixmap = new QPixmap;
    pixmap->load("filename.png");
    ui->label->setPixmap(*pixmap);
   // ui->label->setPixmap(QPixmap::fromImage(*RGB.img));




//    //
//QString fileName = QFileDialog::getSaveFileName(0, "Сохранить как...", QDir::currentPath(), "All types(*.*);;PNG (*.png);;JPG (*jpeg *jpg);; BMP (*.bmp)");
//    if (fileName.isNull())
//        return;
//    screen.save(fileName,0,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
