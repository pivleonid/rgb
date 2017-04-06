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
    Mass_RGB RGB;
    uchar mas[200000];
    for(int j = 0, i = 0; j<200000; i++,j++){
    if (i > 255)
    i = 0;
    mas[j] = i;
    }
    RGB.MassiveStreamLine(10,200, mas);
    int i;
    RGB.img->save("filename.png", "PNG");

    QPixmap *pixmap = new QPixmap;
    pixmap->load("filename.png");
    ui->label->setPixmap(*pixmap);
   // ui->label->setPixmap(QPixmap::fromImage(*RGB.img));


    //connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

//    //
//QString fileName = QFileDialog::getSaveFileName(0, "Сохранить как...", QDir::currentPath(), "All types(*.*);;PNG (*.png);;JPG (*jpeg *jpg);; BMP (*.bmp)");
//    if (fileName.isNull())
//        return;
//    screen.save(fileName,0,100);
//

///ПАРСЕР
/// http://www.opengl-tutorial.org/ru/beginners-tutorials/tutorial-7-model-loading/
QString a;
    QFileInfo info("earth_my.obj");
    a = info.absoluteFilePath();
    uint b = info.size();
    qDebug() << a;
    QFile file("earth_my.obj");
        if (!file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения
            qDebug() << "открыть нельзя";
    QByteArray data = file.readAll();
    QString data_string = QString(data);
    //Разбиваю данные по строчкам
    QList<QString> list_data = data_string.split("\r\n");
    QVector<float> v_x, v_y, v_z; //v = vertex "вершина"
    QVector<float> vn_x, vn_y, vn_z; //vn = vn is the normal of one vertex "нормаль одной вершины"
    QVector<float> vt_x, vt_y ; //vt = vt is the texture coordinate of one vertex "координата текстуры одной вершины"

    QList<QString>::iterator it;
    QList<QString> masString_v_vn_vt_f;//контейнер, содержащий v vn vt
    QList<QString> masString_f;//контейнер для f- fase "грань" ; хранит строку типа 123/123/123
    for(it = list_data.begin();it != list_data.end(); ++it)
        masString_v_vn_vt_f << ((*it).split(" "));
    bool flag_parser_v = false;
    bool flag_parser_space = false;
    bool flag_parser_vn = false;
    bool flag_parser_vt = false;
    bool flag_f = false;

    int count = 0;
    //создаю отдельный контейнер f для дальнейшего парсера
    for(it = masString_v_vn_vt_f.begin();it != masString_v_vn_vt_f.end(); ++it){
        if((*it).toStdString() == "f"){
            flag_f = true;
            continue;
        }
        if(flag_f == true){
            flag_f = (count > 3) ? 0 : count++;
            masString_f.append(*it);
        }

    }
    count = 0;
    for(it = masString_v_vn_vt_f.begin();it != masString_v_vn_vt_f.end(); ++it){
        qDebug() << *it;
//-----------------------------------------------------
{
        if((*it).toStdString() == "v")
            flag_parser_v = true;

        if((*it).toStdString() == "" && flag_parser_v == true){
            flag_parser_space = true;
            flag_parser_v = false;
            continue;
        }
        if(flag_parser_space == true){

            switch (count) {
            case 0:
                v_x.append((*it).toFloat());
                count++;
                break;
            case 1:
                v_y.append((*it).toFloat());
                count++;
                break;
            case 2:
                v_z.append((*it).toFloat());
                count = 0;
                flag_parser_space = false;
                break;
            default:
                break;
            }
        }
}
//-----------------------------------------------------
{
        if((*it).toStdString() == "vn"){
            flag_parser_vn = true;
            continue;
        }
        if(flag_parser_vn == true){

            switch (count) {
            case 0:
                vn_x.append((*it).toFloat());
                count++;
                break;
            case 1:
                vn_y.append((*it).toFloat());
                count++;
                break;
            case 2:
                vn_z.append((*it).toFloat());
                count = 0;
                flag_parser_vn = false;
                break;
            default:
                break;
            }
        }
}
//-----------------------------------------------------
{
        if((*it).toStdString() == "vt"){
            flag_parser_vt = true;
            continue;
        }
        if(flag_parser_vt == true){

            switch (count) {
            case 0:
                vt_x.append((*it).toFloat());
                count++;
                break;
            case 1:
                vt_y.append((*it).toFloat());
                count++;
                count = 0;
                flag_parser_vt = false;
                break;
            default:
                break;
            }
        }
}
///ежели f , то делаю split Для следующего парсера
/// формат данных 'f''123/131/123' эти числа надо распарсить
//-----------------------------------------------------
{
        if((*it).toStdString() == "f"){
            flag_parser_vt = true;
            continue;
        }
        if(flag_parser_vt == true){

            switch (count) {
            case 0:
                vt_x.append((*it).toFloat());
                count++;
                break;
            case 1:
                vt_y.append((*it).toFloat());
                count++;
                count = 0;
                flag_parser_vt = false;
                break;
            default:
                break;
            }
        }
}


    }

//    foreach( v_found,list_data){
//       // QList<QString> it = qFind(list_data.begin(),list_data.end, "v ");
//       if(v_found == list_data.begin())
//        b1++;
//    }

  //  qDebug() << QString(data);
    ui->textEdit->setText(QString(data));
//
connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClicked(){
Mass_RGB RGB;
uchar mas[1000000];
    for(int j = 0, i = 0; j < 1000000; i++,j++){
    if (i > 255)
    i = 0;
    mas[j] = i;
    }
QString line1 = ui->lineEdit->text();
QString line2 = ui->lineEdit_2->text();
RGB.MassiveStreamLine(line1.toInt(),line2.toInt(), mas);
RGB.img->save("filename.png", "PNG");

QPixmap *pixmap = new QPixmap;
pixmap->load("filename.png");
ui->label->setPixmap(*pixmap);
}
