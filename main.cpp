#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
//прототипы функций
void  Resampling(uint32_t* data_Fin, /*Входной массив*/float* data_Fout,
    uint32_t n_in,      /*Размерность массива*/
    uint32_t F_in,      /*Частота дискретизации интерполяции входного массива*/
    uint32_t F_out);    /*частота передискритизации*/
float   linear(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    int n = 11;
    uint32_t data_Fin[n] = { 0,1,2,3,4,5,6,7,8,9,10 };
    uint32_t F_in = 10;
    uint32_t F_out =  5;
    int n_out = floor(F_in * n / F_out);
    float data_Fout[n_out];
    memset(data_Fout, 0 , sizeof(data_Fout));
    Resampling(data_Fin, data_Fout, 10, F_in, F_out);
   // return 0;


 return a.exec();
}

// Как правильно возвращать массив?
// не лучше ли создать контейнер
void  Resampling(uint32_t* data_Fin, float* data_Fout, uint32_t n_in, uint32_t F_in, uint32_t F_out) {
    uint32_t j = 1;
    uint32_t i = 1;
    for ( ; i < (n_in + 1); i++) {
        for (; (i * F_in) > (j * F_out); j++) {
            uint32_t x1 = (i-1) * F_in;
            uint32_t y1 = data_Fin[i-1];
            uint32_t x2 = (i)*F_in;
            uint32_t y2 = data_Fin [i];
            uint32_t x = (j) * F_out;
            if (x > x2 || x < x1)
               qDebug() << "Error";
            data_Fout[j] = linear(x1, y1, x2, y2, x);
        }


    }
    // return data_Fout;
}


float linear(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x) {
    float y = y1 + (float)((y2 - y1)*(x - x1)) / ((float)(x2 - x1));
    return y;

}
