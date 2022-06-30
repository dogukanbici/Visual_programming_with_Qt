#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ogrenci.h"
#include "ders.h"
#include "notlar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.setDatabaseName("C:/Users/DoğukanBici/Documents/20010011076_odev2/20010011076.db");
    if(!db.open())
    {
        ui->statusbar->showMessage("VeriTabanına bağlanılamadı.");
    }
    else
    {
        ui->statusbar->showMessage("VeriTabanına bağlanıldı.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ogrenci *ogr = new ogrenci();//db gelecek
    ogr->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    ders *drs=new ders();
    drs->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    notlar *ntlr = new notlar();
    ntlr->show();
}

