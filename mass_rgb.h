#ifndef MASS_RGB_H
#define MASS_RGB_H

#include <QDebug>
#include <QObject>
#include <QVector>
#include <QImage>

#pragma once

class Mass_RGB: public QObject
{
Q_OBJECT
public:
   explicit Mass_RGB(QObject *parent = 0);
   ~Mass_RGB();
public slots:

void MassiveStreamLine(int x, int y, uchar* mass);

public:
int x, y;
int *mass;
QVector<uchar> mass_vector;
public:
QImage *img;

};

#endif // MASS_RGB_H
