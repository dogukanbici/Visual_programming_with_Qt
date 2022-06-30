#include "ders.h"
#include "ui_ders.h"

ders::ders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ders)
{
    ui->setupUi(this);
    db.setDatabaseName("C:/Users/DoğukanBici/Documents/20010011076_odev2/20010011076.db");
    model_1=new QSqlTableModel();
    model_1->setTable("dersler");
    model_1->select();
    ui->tableView->setModel(model_1);
    model_3=new QSqlTableModel();
    model_3->setTable("notlar");
    model_3->select();
}

ders::~ders()
{
    delete ui;
}
void ders::on_tableView_clicked(const QModelIndex &index)
{
    QString indis = model_1->index(index.row(),0).data().toString();
    //int indis_2=indis.toInt();
    QSqlQuery sorgu;
    sorgu.prepare("select *from notlar where ders_kodu=?");
    sorgu.addBindValue(indis);
    sorgu.exec();
    model_2 = new QSqlQueryModel();
    model_2->setQuery(sorgu);
    ui->tableView_2->setModel(model_2);
    ui->lineEdit->setText(model_1->index(index.row(),0).data().toString());
    ui->lineEdit_2->setText(model_1->index(index.row(),1).data().toString());

}


void ders::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text()==""||ui->lineEdit_2->text()=="")
    {
        QMessageBox::critical(this,"UYARI","Gerekli alanları doldurunuz","Ok");

    }
    else
    {
        QSqlQuery qry;
        qry.prepare("insert into dersler values (:ders_kodu,:ders_adi)");
        qry.bindValue(":ders_kodu",ui->lineEdit->text());
        qry.bindValue(":ders_adi",ui->lineEdit_2->text());
        if (qry.exec())
        {
            QMessageBox::information(this,"Ekleme Durumu","Kayıt Basarı ile eklendi");
            model_1->setTable("dersler");
            model_1->select();
            ui->tableView->setModel(model_1);
        }
        else
        {
            QMessageBox::information(this,"Ekleme Durumu","Bu kodda başka ders vardır.Farklı kodda ders ekleyiniz!.");
            qDebug() << qry.lastError().text();
        }

    }
}


void ders::on_pushButton_clicked()//GÜNCELLEME
{
    QSqlQuery qry;
    int id = ui->lineEdit->text().toInt();
    QString ders_adi=ui->lineEdit_2->text();
    qry.prepare("UPDATE dersler SET ders_adi='"+ders_adi+"' WHERE ders_kodu="+QString::number(id));
    qry.bindValue("ders_kodu",ui->lineEdit->text().toInt());
    if (qry.exec())
    {
        QMessageBox::information(this,"Güncelleme Durumu","Ders Kayıt Basarı ile güncellendi.");
        model_1->setTable("dersler");
        model_1->select();
        ui->tableView->setModel(model_1);
    }
    else
    {
        QMessageBox::information(this,"Güncelleme Durumu","Ders Güncellenemedi!.");
        qDebug() << qry.lastError().text();
    }

}

void ders::on_pushButton_3_clicked()//SİLME
{
    QSqlQuery qry;
    int ders=0;
    int id = ui->lineEdit->text().toInt();
    int con=model_3->rowCount();
    qDebug() << con;
    for (int i=0;i<con;i++ )
    {
        if(id==model_3->index(i,1).data().toInt())
        {
            ders=1;
        }

    }
    if(ders)
    {
        QMessageBox::critical(this,"UYARI","Bu derse ait öğrenci vardır silinemez.","Ok");
    }
    else
    {
        qry.prepare("DELETE FROM dersler WHERE ders_kodu="+QString::number(id));
        qry.bindValue("ders_kodu",ui->lineEdit->text());
        qry.exec();
        QMessageBox::information(this,"Silme Durumu","Ders Kayıt Basarı ile silindi");
        model_1->setTable("dersler");
        model_1->select();
        ui->tableView->setModel(model_1);
    }

}
