#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
}

DisplayWindow::DisplayWindow(double** t,int r, int c){
    this->setFixedSize(800,800);
    this->t=t;
    row=r;
    column=c;
    if(r>c){
        w=600;
        h=400;
    }
    else if(r<c){
        w=400;
        h=600;
    }
    else w=h=600;

    nx=w/(r-1);
    ny=h/(c-1);

    update();
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *event)
{

    QPen pen;
    pen.setWidth(6);
    QPainter *painter=new QPainter(this);
    painter->drawRect(startX,startY,w,h);
    painter->setPen(pen);
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            int x=startX+i*w/(row-1);
            int y=startY+h-j*h/(column-1);
            painter->drawPoint(x,y);
            painter->drawText(x+2,y-5,QString::number(t[i][j]));
        }
    painter->end();

    // horizontal lines
    QPainter *linePainter=new QPainter(this);
    for(int i=1;i<column-1;i++){
        int y=startY+h-i*h/(column-1);
        linePainter->drawLine(QPoint(startX,y),QPoint(startX+w,y));
    }
    linePainter->end();

    // vertical lines
    QPainter *vert_linePainter=new QPainter(this);
    for(int i=1;i<row-1;i++){
        int x=startX+i*w/(row-1);
        vert_linePainter->drawLine(QPoint(x,startY),QPoint(x,startY+h));
    }
    vert_linePainter->end();
}



