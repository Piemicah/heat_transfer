#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "displaywindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnCompute_clicked()
{
    double length=ui->lengthEdit->text().toDouble();
    double height=ui->heightEdit->text().toDouble();
    double k=ui->kEdit->text().toDouble();
    double g=ui->gEdit->text().toDouble();
    double top_temp=ui->topEdit->text().toDouble();
    double bottom_temp=ui->bottomEdit->text().toDouble();
    double right_temp=ui->rightEdit->text().toDouble();
    double left_temp=ui->leftEdit->text().toDouble();
    int x_div=ui->xDivEdit->text().toInt();
    int y_div=ui->yDivEdit->text().toInt();

    int row=x_div+1;
    int column=y_div+1;

    double dx = length / x_div; /*finite difference along x*/
    double dy = height / y_div; /*finite difference along y*/
    double dx2 = dx*dx;
    double dy2 = dy*dy;
    double lambda=1/(2*(dx2+dy2));
    double C = (g*dx2*dy2)/k;
    double** T = new double*[row];

        for (int i = 0;i < row;i++) T[i] = new double[column];

        /*Compute Boundary conditions*/

        /*Top nodes temperatures*/
        for (int i = 0;i <row;i++)
        {
            T[i][column-1]=top_temp;
        }

        /*Bottom nodes temperatures*/
        for (int i = 0;i <row;i++)
        {
            T[i][0]=bottom_temp;
        }

        for (int i = 1;i<column-1;i++)
        {
            T[row-1][i]=right_temp;
        }


        for (int i = 1;i<column-1;i++)
        {
            T[0][i]=left_temp;
        }


        /*initialise inner nodes*/
        for (int i = 1;i<x_div;i++)
            for (int j = 1;j<y_div;j++)
            {
                T[i][j] = 30;
            }

        /*compute inner nodes using Jacobian iteration*/
        for (int k = 1;k <= 10000;k++)
            for (int i = 1;i<x_div;i++)
                for (int j = 1;j<y_div;j++)

                {
                    T[i][j] = lambda*(dy2*(T[i-1][j]+T[i+1][j])+dx2*(T[i][j-1]+T[i][j+1]) + C);
                }

        DisplayWindow* dw = new DisplayWindow(T,row,column);
        dw->setVisible(true);
}

