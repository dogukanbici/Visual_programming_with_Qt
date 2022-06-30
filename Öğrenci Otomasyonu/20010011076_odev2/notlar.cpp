#include "notlar.h"
#include "ui_notlar.h"

notlar::notlar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notlar)
{
    ui->setupUi(this);
    db.setDatabaseName("C:/Users/DoğukanBici/Documents/20010011076_odev2/20010011076.db");
    model_1=new QSqlTableModel();
    model_1->setTable("ogrenci");
    model_1->select();
    ui->tableView->setModel(model_1);
    model_2=new QSqlTableModel();
    model_2->setTable("dersler");
    model_2->select();
    ui->tableView_2->setModel(model_2);
    model_3=new QSqlTableModel();
    model_3->setTable("notlar");
    model_3->select();
    ui->tableView_3->setModel(model_3);
}

notlar::~notlar()
{
    delete ui;
}
QString ogrOku;
void notlar::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit->setText(model_1->index(index.row(),0).data().toString());
    ogrOku=model_1->index(index.row(),0).data().toString();
}

QString dersOku;
void notlar::on_tableView_2_clicked(const QModelIndex &index)
{
    ui->lineEdit_2->setText(model_2->index(index.row(),0).data().toString());
    dersOku=model_2->index(index.row(),0).data().toString();
}

int gnot;
void notlar::on_pushButton_clicked()//ekleme
{
    QSqlQuery sorgu;
    QSqlQueryModel *model = new QSqlQueryModel();
    gnot=ui->lineEdit_3->text().toInt()*0.4+ui->lineEdit_4->text().toInt()*0.6;
    sorgu.prepare("Select * from notlar where ogr_no=? and ders_kodu= ?");
    sorgu.addBindValue(ui->lineEdit->text());
    sorgu.addBindValue(ui->lineEdit_2->text());
    sorgu.exec();
    model->setQuery(sorgu);
    int con=model->rowCount();
    qDebug() << con;
    if(con>0)
    {
        QMessageBox::critical(this,"UYARI","ÜZERİNE BU DERS VAR ZATEN","Ok");
    }
    else
    {
        if(ui->lineEdit_3->text()==""||ui->lineEdit_4->text()=="")
        {
            QMessageBox::critical(this,"UYARI","Gerekli alanları doldurunuz","Ok");
        }
        else
        {
            QSqlQuery qry;
            qry.prepare("insert into notlar values (:ogr_no,:ders_kodu,:vize_not,:final_not,:gecme_notu)");
            qry.bindValue(":ogr_no",ui->lineEdit->text());
            qry.bindValue(":ders_kodu",ui->lineEdit_2->text());
            qry.bindValue(":vize_not",ui->lineEdit_3->text());
            qry.bindValue(":final_not",ui->lineEdit_4->text());
            qry.bindValue(":gecme_notu",gnot);
            {
                if (qry.exec())
                {
                    QMessageBox::information(this,"Ekleme Durumu","Ders-Ögrenci Kayıt Basarı ile eklendi");
                    model_3->setTable("notlar");
                    model_3->select();
                    ui->tableView_3->setModel(model_3);
                }
                else
                {
                    qDebug() << qry.lastError().text();
                }

            }
    }

    }
}

