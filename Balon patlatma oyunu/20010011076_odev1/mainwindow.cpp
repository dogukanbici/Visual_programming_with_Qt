#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    timer->start(150);
    connect(timer,&QTimer::timeout,this,&MainWindow::balonHareket);
    time = 0;
    QTimer *tut = new QTimer(this);
    connect(tut, SIGNAL(timeout()),this, SLOT(timeCounter()));
    tut->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::balonHareket()
{
    int sayi=buttonlist.size();
    int rsayi;
    int balonsayi;
    rsayi=rand()%(1481-1)+1;
    balonsayi=rand()%(7-0)+0;
    int vurulan=0;
    int kaçanbalon=0;
    if(time%4==0)
    {
        balon *button = new balon(this);
        button->setGeometry(rsayi,100,50,50);
        buttonlist.push_back(button);
        button->setStyleSheet("image:url(:/img/images/"+QString::number(balonsayi)+".jpg)");
        button->show();
    }
    for (int i=0;i<sayi;i++)
    {
        buttonlist[i]->setGeometry(buttonlist[i]->x(),buttonlist[i]->y()+6,buttonlist[i]->width(),buttonlist[i]->height());
        if(buttonlist[i]->clickballon)
        {
            buttonlist[i]->setStyleSheet("image:url(:/img/images/patlama.jpg)");
            QTimer::singleShot(250,[this,i]
            {
                buttonlist[i]->setVisible(0);
            });
            vurulan++;
            ui->label_3->setText("VURULAN BALON SAYISI:"+QString::number(vurulan));
        }
        if(buttonlist[i]->y()>750)
        {
            kaçanbalon++;
            buttonlist[i]->setVisible(0);
            if(buttonlist[i]->clickballon)
            {
                kaçanbalon--;
            }
            ui->label_4->setText("KAÇAN BALON SAYISI:"+QString::number(kaçanbalon));
        }
    }
}

void MainWindow::timeCounter()
{
    ui->label_2->setText("Süre:"+QString::number(time));
    time+=1;
}

