#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mass_rgb.h"
#include <QPixmap>
//
#include <QFile>
#include <QFileInfo>

//прототипы функций
 uint32_t*  Resampling(uint32_t* data_Fin, /*Входной массив*/
                       uint32_t n_in,      /*Размерность массива*/
                       uint32_t F_in,      /*Частота дискретизации интерполяции входного массива*/
                       uint32_t F_out);    /*частота передискритизации*/
uint32_t   linear(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    //вход 0..4 294 967 295 => делитель 16843009
{

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(ZoomIn()));
connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(ZoomOut()));
   // ui->label->setPixmap(QPixmap::fromImage(*RGB.img));


    //connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

//    //
//QString fileName = QFileDialog::getSaveFileName(0, "Сохранить как...", QDir::currentPath(), "All types(*.*);;PNG (*.png);;JPG (*jpeg *jpg);; BMP (*.bmp)");
//    if (fileName.isNull())
//        return;
//    screen.save(fileName,0,100);
//


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::buttonClicked(){

QString line1 = ui->lineEdit->text();
QString line2 = ui->lineEdit_2->text();
int size_mas = (line1.toInt())* (line2.toInt());
uchar* mas = new uchar [size_mas];
//QVector <uchar> mas_ushar;
//for(int i = 0; i < size_mas; i++)
//     mas_ushar.push_back(qrand()%256);
    for(int j = 0, i = 0; j < size_mas; i++,j++){
    if (i > 255)
   i = 0;
   mas[j] = qrand()%255;
//    mas[j] = qrand()%255;
    }
QImage img(mas, line1.toInt(), line2.toInt(),  QImage::Format_Indexed8);
//qpixmap  в роли промежуточного буфера
 QPixmap *pixmap = new QPixmap(QPixmap::fromImage(img));
 scene->addPixmap(QPixmap::fromImage(img));
   pixmap->save("filename.png", "PNG");
}

    void MainWindow::ZoomIn(){
     ui->graphicsView->scale(1.1, 1.1);
    }

    void  MainWindow::ZoomOut(){
        ui->graphicsView->scale(1 / 1.1, 1 / 1.1);
    }

void MainWindow::wheelEvent(QWheelEvent* events) {
    if(events->modifiers() & Qt::CTRL){
        if(events->delta() > 0)
            ZoomIn();
        if(events->delta() < 0)
            ZoomOut();
    }
}

 uint32_t data_Fout[10000000];
 //uint32_t* data_Fin[]
 uint32_t* Resampling(uint32_t* data_Fin, uint32_t n_in, uint32_t F_in, uint32_t F_out){
     uint32_t j = 0;
     for(uint32_t i = 0; i < n_in; i++, F_in += F_in)
         for( ; F_in > F_out; j++, F_out += F_out){
             data_Fout[j] = linear(i * F_in, data_Fin[i], (i++)* F_in, data_Fin[++i], j*F_out );
         }

     return data_Fout;
 }


uint32_t linear(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x){
    uint32_t y = y1 + (y2 - y1)*(x - x1)/(x2 - x1);
    return y;

}
