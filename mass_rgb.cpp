#include "mass_rgb.h"


/*как в конструктор передать параметры? какой синтаксис? если есть долбанный родитель*/
Mass_RGB::Mass_RGB(QObject *parent):QObject(parent)
{
/*присваиваю private переменным значения*/
}


void Mass_RGB::MassiveStreamLine(int x, int y, uchar* mass){

int size_mass = sizeof(mass)/sizeof(mass[0]);
if (size_mass > x * y)
qDebug()<< "количество отображаемых точек меньше переданных";
//mass_vector.clear();
//for(int i = 0; i < x*y; i++)
//mass_vector.append(i); //вектор заполнен
img = new QImage(mass, y, x, x , QImage::Format_Indexed8);
//QImage img1(mass, x, y, QImage::Format_Indexed8);



}

Mass_RGB::~Mass_RGB(){

}
