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
    uchar mas[2000];
    for(int j = 0, i = 0; j<2000; i++,j++){
    if (i > 257)
    i = 0;
    mas[j] = i;
    }
    RGB.MassiveStreamLine(200,200, mas);
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
