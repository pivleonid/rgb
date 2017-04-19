#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QWheelEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
public slots:
void buttonClicked();
void ZoomIn();
void ZoomOut();
virtual void wheelEvent(QWheelEvent* events);
public:
QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
