#ifndef OGRENCI_H
#define OGRENCI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class ogrenci;
}

class ogrenci : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenci(QWidget *parent = nullptr);
    ~ogrenci();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ogrenci *ui;
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    QSqlTableModel *model_1;
    QSqlTableModel *model_3;
    QSqlQueryModel *model_2;
};

#endif // OGRENCI_H
