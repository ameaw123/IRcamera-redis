#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MeasureCoreNet.h"
#include "DeviceFunctionSupport.h"
#include "qRedis.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int32_t myloginid=-1;
    int32_t mysessionid=-1;
    qRedis *redis;
    void timerEvent(QTimerEvent *event);
    void myKillTimer(int id);
    QString order="" ;

private slots:


    void on_Button_save_clicked();

    void catch_picture();

    void on_pushButton_satrt_toggled(bool toggled);

    void slotMessage(qRedis::Reply);

    void on_pushButton_catch_clicked();

private:

    Ui::MainWindow *ui;
    int _queryTimeID = -1;
};

#endif // MAINWINDOW_H
