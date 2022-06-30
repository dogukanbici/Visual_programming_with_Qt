#include "ogrenci.h"
#include "ui_ogrenci.h"

ogrenci::ogrenci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenci)
{
    ui->setupUi(this);
    db.setDatabaseName("C:/Users/DoğukanBici/Documents/20010011076_odev2/20010011076.db");
    model_1=new QSqlTableModel();
    model_1->setTable("ogrenci");
    model_1->select();
    ui->tableView->setModel(model_1);
    model_3=new QSqlTableModel();
    model_3->setTable("notlar");
    model_3->select();
}

ogrenci::~ogrenci()
{
    delete ui;
}

void ogrenci::on_tableView_clicked(const QModelIndex &index)
{

    ui->lineEdit->setText(model_1->index(index.row(),0).data().toString());
    ui->lineEdit_2->setText(model_1->index(index.row(),1).data().toString());
    ui->lineEdit_3->setText(model_1->index(index.row(),2).data().toString());


}


void ogrenci::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text()==""||ui->lineEdit_3->text()=="")
    {
        QMessageBox::critical(this,"UYARI","Gerekli alanları doldurunuz","Ok");

    }
    else
    {
        QSqlQuery qry;
        qry.prepare("insert into ogrenci values (:ogr_no,:ogr_ad,:ogr_soyad)");
        qry.bindValue(":ogr_ad",ui->lineEdit_2->text());
        qry.bindValue(":ogr_soyad",ui->lineEdit_3->text());
        if (qry.exec())
        {
            QMessageBox::information(this,"Ekleme Durumu","Kayıt Basarı ile eklendi");
            model_1->setTable("ogrenci");
            model_1->select();
            ui->tableView->setModel(model_1);
        }
        else
            qDebug() << qry.lastError().text();
    }

}


void ogrenci::on_pushButton_2_clicked()//Silme
{
    QSqlQuery qry;
    int ders=0;
    int id = ui->lineEdit->text().toInt();
    int con=model_3->rowCount();
    qDebug() << con;
    for (int i=0;i<con;i++ )
    {
        if(id==model_3->index(i,0).data().toInt())
        {
            ders=1;
        }
    }
    if(ders)
    {
        QMessageBox::information(this,"Silme Durumu","Bu öğrenci silinemez.Bu öğrencinin üstüne tanımlanmış dersler vardır!.");
        qDebug() << qry.lastError().text();
    }
    else
    {
        int id = ui->lineEdit->text().toInt();
        qry.prepare("DELETE FROM ogrenci WHERE ogr_no="+QString::number(id));
        qry.bindValue("ogr_no",ui->lineEdit->text().toInt());
        if (qry.exec())
        {
            QMessageBox::information(this,"Silme Durumu","Kayıt Basarı ile silindi");
            model_1->setTable("ogrenci");
            model_1->select();
            ui->tableView->setModel(model_1);
        }

    }

}


void ogrenci::on_pushButton_3_clicked()
{
    QSqlQuery qry;
    int id = ui->lineEdit->text().toInt();
    QString ogr_ad=ui->lineEdit_2->text();
    QString ogr_soyad=ui->lineEdit_3->text();
    qry.prepare("UPDATE ogrenci SET ogr_ad='"+ogr_ad+"',""ogr_soyad='"+ogr_soyad+"' WHERE ogr_no="+QString::number(id));
    qry.bindValue("ogr_no",ui->lineEdit->text().toInt());
    if (qry.exec())
    {
        QMessageBox::information(this,"Güncelleme Durumu","Kayıt Basarı ile güncellendi.");
        model_1->setTable("ogrenci");
        model_1->select();
        ui->tableView->setModel(model_1);
    }
    else
        qDebug() << qry.lastError().text();
}

