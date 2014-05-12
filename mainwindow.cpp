#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "main1.cpp"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


int f=0,f1=0,Row=-1,Column=-1;
int r1,r2,c1,c2;
bool is_possible(int r1,int c1,int r2,int c2,int b[8][8])
{
    if(b[r1][c1]==1&&b[r2][c2]==-1)
    {
        int x=r2-r1,y=c2-c1;
        if(x==y||x==-y)
        {
            if(x<-2||x>=0)
                return false;
            if(y>2||y==0||y<-2)
                return false;
            if(x==-2&&y==-2&&b[r1-1][c1-1]!=0)
                return false;
            if(x==-2&&y==2&&b[r1-1][c1+1]!=0)
                return false;
            return true;
        }
        else return false;
    }
    else return false;
}

int b[8][8]={{0,-1,0,-1,0,-1,0,-1},
            {-1,0,-1,0,-1,0,-1,0},
            {0,-1,0,-1,0,-1,0,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,1,-1,1,-1,1,-1,1},
            {1,-1,1,-1,1,-1,1,-1},
            {-1,1,-1,1,-1,1,-1,1}};
//when start button is clicked
void MainWindow::on_pushButton_clicked()
{
    //cout<<"abc";
    f=0;

    //system("gnome-terminal -x sh -c './a.out; exec bash'");
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(b[i][j]==0)
            {
                QTableWidgetItem *itab;
                itab = new QTableWidgetItem;
                itab->setBackground(Qt::black);
                ui->tableWidget->setItem(i, j, itab);
            }
            else if(b[i][j]==1)
            {
                QTableWidgetItem *itab;
                itab = new QTableWidgetItem;
                itab->setBackground(Qt::red);
                ui->tableWidget->setItem(i, j, itab);
            }
        }
    }
    //checkers();
}
int is_finish(int n)
{
    //int flag1=1;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(b[i][j]==n)
            {
                if(n==1)
                {
                    if(i-1>=0&&i-1<8&&j-1>=0&&j-1<8)
                    {
                        if(b[i-1][j-1]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }
                    if(i-1>=0&&i-1<8&&j+1>=0&&j+1<8)
                    {
                        if(b[i-1][j+1]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }
                    if(i-2>=0&&i-2<8&&j-2>=0&&j-2<8)
                    {
                        if(b[i-2][j-2]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }
                    if(i-2>=0&&i-2<8&&j+2>=0&&j+2<8)
                    {
                        if(b[i-2][j+2]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }

                }
               else if(n==0)
                {
                    if(i+1>=0&&i+1<8&&j-1>=0&&j-1<8)
                    {
                        if(b[i+1][j-1]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }
                    if(i+1>=0&&i+1<8&&j+1>=0&&j+1<8)
                    {
                        if(b[i+1][j+1]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }
                    if(i+2>=0&&i+2<8&&j-2>=0&&j-2<8)
                    {
                        if(b[i+2][j-2]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }
                    if(i+2>=0&&i+2<8&&j+2>=0&&j+2<8)
                    {
                        if(b[i+2][j+2]==-1)
                        {
          //                  flag1=0;
                            return 0;
                        }
                    }

                }

            }
        }
    }
    return 1;
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

    f++;
    Row=row;
    Column=column;

        if(f==1)
        {
            r1=Row;
            c1=Column;
        }
        else if(f==2)
        {
            r2=Row;
            c2=Column;
        }
    if(f==2)
    {

        f=0;


        if(is_possible(r1,c1,r2,c2,b))
        {
            int x=r2-r1,y=c2-c1;
            if(x==-1)
            {
                b[r1][c1]=-1;
                b[r2][c2]=1;
            }
            else if(x==-2)
            {
                b[r1][c1]=-1;
                while(b[r1+x][c1+y]==-1 && b[(r1+r2)/2][(c1+c2)/2]==0&&r1>=0&&r1<8&&c1>=0&&c1<8&&c2>=0&&c2<8&&r2>=0&&r2<8)
                {
                    b[(r1+r2)/2][(c1+c2)/2]=-1;
                    r1=r2;
                    c1=c2;
                    r2=r1+x;
                    c2=c1+y;
                }
                b[r1][c1]=1;
            }
            //system("./a.out");

                for(int i=0;i<8;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        if(b[i][j]==0)
                        {
                            QTableWidgetItem *itab;
                            itab = new QTableWidgetItem;
                            itab->setBackground(Qt::black);
                            ui->tableWidget->setItem(i, j, itab);
                        }
                        else if(b[i][j]==1)
                        {
                            QTableWidgetItem *itab;
                            itab = new QTableWidgetItem;
                            itab->setBackground(Qt::red);
                            ui->tableWidget->setItem(i, j, itab);
                        }
                        else
                        {
                            QTableWidgetItem *itab;
                            itab = new QTableWidgetItem;
                            itab->setBackground(Qt::white);
                            ui->tableWidget->setItem(i, j, itab);
                        }
                    }
                }
                if(is_finish(1)||is_finish(0))
                {
                    int temp=0;
                        //score=0;
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<8;j++)
                            {
                                if(b[i][j]==1)
                                    temp++;
                                else if(b[i][j]==0)
                                    temp--;
                            }
                        }
                        if(temp<0)
                            ui->label->setText("Computer Wins !!!");
                        else if(temp>0)
                            ui->label->setText("Player Wins !!!");
                        else
                            ui->label->setText("DRAW !!!");
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<8;j++)
                            {
                                if(b[i][j]==0)
                                {
                                    QTableWidgetItem *itab;
                                    itab = new QTableWidgetItem;
                                    itab->setBackground(Qt::black);
                                    ui->tableWidget->setItem(i, j, itab);
                                }
                                else if(b[i][j]==1)
                                {
                                    QTableWidgetItem *itab;
                                    itab = new QTableWidgetItem;
                                    itab->setBackground(Qt::red);
                                    ui->tableWidget->setItem(i, j, itab);
                                }
                                else
                                {
                                    QTableWidgetItem *itab;
                                    itab = new QTableWidgetItem;
                                    itab->setBackground(Qt::white);
                                    ui->tableWidget->setItem(i, j, itab);
                                }
                            }
                        }
                        return;
                }


// by yash 
//checkers();
                QFile file("in.txt");
                    file.open(QIODevice::WriteOnly | QIODevice::Text);
                    QTextStream out(&file);
                    for(int i=0;i<8;i++)
                    {
                        for(int j=0;j<8;j++)
                        {
                            out<<b[i][j]<<" ";
                        }
                        out<<"\n";
                    }
                    //out << "This file is generated by Qt\n";

                    // optional, as QFile destructor will already do it:
                    file.close();
                system("./a.out");
                QFile file1("out.txt");
                file1.open(QIODevice::ReadOnly | QIODevice::Text);
                QTextStream in(&file1);
                for(int i=0;i<8;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        in>>b[i][j];
                    }
                }
                file1.close();
                    //freopen("output.txt", "rt", stdin);
                    //for(int i=0;i<8;i++)
                           // for(int j=0;j<8;j++)
                             //   cin>>b[i][j];
                    for(int i=0;i<8;i++)
                    {
                        for(int j=0;j<8;j++)
                        {
                            if(b[i][j]==0)
                            {
                                QTableWidgetItem *itab;
                                itab = new QTableWidgetItem;
                                itab->setBackground(Qt::black);
                                ui->tableWidget->setItem(i, j, itab);
                            }
                            else if(b[i][j]==1)
                            {
                                QTableWidgetItem *itab;
                                itab = new QTableWidgetItem;
                                itab->setBackground(Qt::red);
                                ui->tableWidget->setItem(i, j, itab);
                            }
                            else
                            {
                                QTableWidgetItem *itab;
                                itab = new QTableWidgetItem;
                                itab->setBackground(Qt::white);
                                ui->tableWidget->setItem(i, j, itab);
                            }
                        }
                    }
                    if(is_finish(0)||is_finish(1))
                    {
                        int temp=0;
                            //score=0;
                            for(int i=0;i<8;i++)
                            {
                                for(int j=0;j<8;j++)
                                {
                                    if(b[i][j]==1)
                                        temp++;
                                    else if(b[i][j]==0)
                                        temp--;
                                }
                            }
                            if(temp<0)
                                ui->label->setText("Computer Wins !!!");
                            else if(temp>0)
                                ui->label->setText("Player Wins !!!");
                            else
                                ui->label->setText("DRAW !!!");
                            for(int i=0;i<8;i++)
                            {
                                for(int j=0;j<8;j++)
                                {
                                    if(b[i][j]==0)
                                    {
                                        QTableWidgetItem *itab;
                                        itab = new QTableWidgetItem;
                                        itab->setBackground(Qt::black);
                                        ui->tableWidget->setItem(i, j, itab);
                                    }
                                    else if(b[i][j]==1)
                                    {
                                        QTableWidgetItem *itab;
                                        itab = new QTableWidgetItem;
                                        itab->setBackground(Qt::red);
                                        ui->tableWidget->setItem(i, j, itab);
                                    }
                                    else
                                    {
                                        QTableWidgetItem *itab;
                                        itab = new QTableWidgetItem;
                                        itab->setBackground(Qt::white);
                                        ui->tableWidget->setItem(i, j, itab);
                                    }
                                }
                            }
                            return;
                    }
        }
    }
}


