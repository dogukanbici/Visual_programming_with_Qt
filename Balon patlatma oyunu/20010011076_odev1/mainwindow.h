#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "balon.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void balonHareket();
private slots:
    void timeCounter();
private:
    Ui::MainWindow *ui;
    QList <balon*>buttonlist;
    int time, vurulan, kacan;
    QTimer *timer_time;
};


#endif // MAINWINDOW_H
