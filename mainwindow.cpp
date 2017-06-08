#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mass_rgb.h"
#include <QPixmap>
//
#include <QFile>
#include <QFileInfo>



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

//uchar* mas = new uchar [size_mas];
uchar mas[size_mas]; // заменить на new
    for(int j = 0, i = 0; j < size_mas; i++,j++){
    if (i > 255)
   i = 0;
   mas[j] = ((rand()%255)+(rand()%255)+(rand()%255)+(rand()%255)+(rand()%255))/5;
    }

    ///

   int hist[256];// массив гистограммы

   ///
   uchar b[256];
    for (int i = 0; i < 256; i++)
        b[i] = i;
    ///
    int cont = 0;
    for(int j = 0; j < 257; j++){
    hist[j-1] = cont;
    cont = 0;
        for(int i = 0; i < size_mas; i++){
            if(mas[i] == b[j])
                cont++;

        }
    }

    ///задание порога

    double porog = 2;
     int max_hist = 0;
    for(int i = 0; i < 256; i++){
        if(hist[i] > max_hist){
            max_hist = hist[i];
            }
    }
    porog = porog * max_hist;

    ///Определяю пороговые индексы Kmin и Kmax

    bool flagPorogMin = false;
    bool flagPorogMax = false;
    QVector<int> VecPorogMin, VecPorogMax;
    for(int i = 0; i < 255; i++){
        if(flagPorogMin == false){
            if(hist[i] < porog)
             VecPorogMin.append(i);
             else flagPorogMin = true;
        }
        if(flagPorogMax == false){
            if(hist[255 - i] < porog)
             VecPorogMax.append(255 - i);
             else flagPorogMax = true;
        }
     }
     ///Пробегаюсь по массиву, ищу совпадение  с векторами
     /// Если словпадение есть, то заменяю значение на 0 или на max
    for(int i = 0; i < size_mas; i++){
    if(VecPorogMin.indexOf(mas[i]) >= 0)
        mas[i] = 0;
    if(VecPorogMax.indexOf(mas[i]) >= 0)
        mas[i] = 255;
    }






//
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




