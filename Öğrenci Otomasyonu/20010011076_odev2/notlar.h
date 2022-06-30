#ifndef NOTLAR_H
#define NOTLAR_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class notlar;
}

class notlar : public QDialog
{
    Q_OBJECT

public:
    explicit notlar(QWidget *parent = nullptr);
    ~notlar();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::notlar *ui;
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    QSqlTableModel *model_1;
    QSqlTableModel *model_2;
    QSqlTableModel *model_3;
    QSqlQueryModel *model_4;
};

#endif // NOTLAR_H
