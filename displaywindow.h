#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = nullptr);
    ~DisplayWindow();
    DisplayWindow(double** t,int r, int c);
    virtual void paintEvent(QPaintEvent* event);

private:
    Ui::DisplayWindow *ui;
    int w,h,nx,ny,row,column;
    int startX=100,startY=50;
    double** t;
};

#endif // DISPLAYWINDOW_H
