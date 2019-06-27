#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QFileDialog>

GD_MTC_TempPointInfo pTempPointhigh;
GD_MTC_TempPointInfo pTempPointlow;
int CALLBACK y16CbFun(const GD_MTC_CALLBACK_Y16Info * pY16Info, void *pUser)
{
    void * pOpque = pY16Info->pOpque;
    GD_MTC_SDK_GetHighTemp(pOpque, &pTempPointhigh);
    GD_MTC_SDK_GetLowTemp(pOpque, &pTempPointlow);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /*************************连接到redis服务器***********************/
    redis= new qRedis("127.0.0.1",6379);     //连接失败便不出现窗口的bug待修复，目测是阻塞
    if (!redis->openConnection())
    {
        qDebug() << "Redis：连接服务器失败";
        ui->textEdit_log->append("Redis：连接服务器失败");
    }
    else
    {
        qDebug() << "Redis：连接到服务器";
        ui->textEdit_log->append("Redis：连接到服务器");
    }
    redis->subscribe("Sensor");
    connect(redis, SIGNAL(returnData(qRedis::Reply)), this, SLOT(slotMessage(qRedis::Reply)));

/*************************摄像头初始化***********************/
    int32_t ret=GD_MTC_SDK_Init();
    if(ret==NO_ERROR)
    {
        qDebug()<<"SDK初始化成功";
        ui->textEdit_log->append("SDK初始化成功");
    }
    else
    {
        qDebug()<<"SDK初始化失败";
        ui->textEdit_log->append("SDK初始化失败");
    }

    GD_MTC_IRDeviceInfo DeviceInfo;
    char IpAddress1[20]="192.168.125.104";
    for(int i=0;i<20;i++)
    {
        DeviceInfo.IpAddress[i]=IpAddress1[i];
    }
    DeviceInfo.DevType=DEVICE_TYPE_UNKNOWN;
    myloginid=GD_MTC_SDK_Login(DeviceInfo,0);
    if(myloginid!=ERROR_LOGIN_FAIL)
    {
        qDebug()<<"摄像头登录成功"<<myloginid;
        ui->textEdit_log->append("摄像头登录成功");

    }
    else
    {
        myloginid=GD_MTC_SDK_Login(DeviceInfo,0);
        if(myloginid!=ERROR_LOGIN_FAIL)
        {
            qDebug()<<"摄像头登录成功"<<myloginid;
            ui->textEdit_log->append("摄像头登录成功");

        }
        else
        {
            qDebug()<<"摄像头登录失败"<<myloginid;
            ui->textEdit_log->append("摄像头登录失败");
        }

    }
    //打开数据流
    GD_MTC_IRLinkInfo pIRLinkInfo{GD_MTC_IRLinkInfo()};
    pIRLinkInfo.Y16CB=y16CbFun;
    pIRLinkInfo.nPullDataType=PULL_DATA_TYPE_Y16_ONLY;
    mysessionid=GD_MTC_SDK_OpenStream(myloginid, &pIRLinkInfo, 3, 15, 0);
    if(mysessionid!=ERROR_OPENSTREAM_FAIL)
    {
        qDebug()<<"打开数据流成功"<<mysessionid;
        //打开色带
        GD_MTC_SHOW_PALETTE_INFO showPaletteInfo{GD_MTC_SHOW_PALETTE_INFO()};
        int32_t rett = GD_MTC_SDK_SetShowPaletteInfo(mysessionid,showPaletteInfo);
        if(rett==NO_ERROR)
        {
            qDebug()<<"打开色带成功";
        }
        //设置自动温度调光
        int32_t rettt= GD_MTC_SDK_SetAdjustLightMode(mysessionid, ADJUST_LIGHT_MODE_TEMPERATURE_AUTO);
        if(rett==NO_ERROR)
        {
            qDebug()<<"设置自动温度调光成功";
        }
    }
    else
    {
        qDebug()<<"打开数据流失败"<<mysessionid;
    }
    /*************************start按钮默认点击***********************/
    ui->pushButton_satrt->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete redis;
    //关闭数据流
    int32_t ret3=GD_MTC_SDK_CloseStream(mysessionid);
    if(ret3==NO_ERROR)
    {
        qDebug()<<"关闭数据流成功";
    }
    else
    {
        qDebug()<<"关闭数据流失败";
    }
    //设备登出
    int32_t ret1=GD_MTC_SDK_Logout(myloginid);
    if(ret1==NO_ERROR)
    {
        qDebug()<<"设备登出成功";
    }
    else
    {
        qDebug()<<"设备登出失败";
    }
    //SDK释放
    int32_t ret=GD_MTC_SDK_Release();
    if(ret==NO_ERROR)
    {
        qDebug()<<"SDK释放成功";
    }
    else
    {
        qDebug()<<"SDK释放失败";
    }

    delete ui;
}



void MainWindow::slotMessage(qRedis::Reply reply)
{
    QTime time;
    qDebug() << time.currentTime();
    qDebug() << "Channel:" << reply.channel << "Pattern:" << reply.pattern;
    order=reply.value.toString();
    qDebug() << reply.value.toString();
}

void MainWindow::catch_picture()
{

    //自动调焦
    int32_t ret1=GD_MTC_SDK_FocusAuto(mysessionid, 0);
    //延时6s，用于调焦
    QTime dieTime = QTime::currentTime().addMSecs(6000);
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    if(ret1!=NO_ERROR)
    {
        qDebug()<<"自动调焦失败"<<mysessionid;
    }
    else
    {
        qDebug()<<"自动调焦成功"<<mysessionid;

        //抓图
        QString path=ui->directorycomboBox->currentText();
        path.append("\\");
        path.append(QString("%1").arg(pTempPointhigh.PointTemp));
        path.append("_");
        path.append(QString("%1").arg(pTempPointlow.PointTemp));
        path.append(".jpg");
        ui->textEdit_log->append(path);
        char* strFilePath;
        QByteArray ba = path.toLatin1();
        strFilePath=ba.data();
        int32_t ret2= GD_MTC_SDK_SnapPictureUniform(mysessionid, strFilePath, true, true, true, 0, 0);
        if(ret2==NO_ERROR)
        {
            qDebug()<<"抓图成功";
            ui->textEdit_log->append("抓图成功");

        }
        else
        {
            qDebug()<<"抓图失败";
            ui->textEdit_log->append("抓图失败");
        }
    }

}

void MainWindow::on_Button_save_clicked()
{
    QString directory= QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("Save path"),QDir::currentPath()));
    if(!directory.isEmpty())
    {
        if(ui->directorycomboBox->findText(directory)==-1)
        {
            ui->directorycomboBox->addItem(directory);
        }
        ui->directorycomboBox->setCurrentIndex(ui->directorycomboBox->findText(directory));
    }
}



void MainWindow::on_pushButton_satrt_toggled(bool toggled)
{
    if(toggled)
    {
        ui->pushButton_satrt->setObjectName("stop");
        _queryTimeID = this->startTimer(1000);
    }
    else
    {
        if (_queryTimeID > 0) {
           myKillTimer(_queryTimeID);
        }
    }
}
void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == _queryTimeID)
    {
        qDebug()<<"----";
        qDebug()<<"最高温度"<<pTempPointhigh.PointTemp;
        qDebug()<<"最低温度"<<pTempPointlow.PointTemp;
        QList<QString> orderlist=order.split('_');
        QString order1=orderlist.at(0);
        if(order1=="Arrive")
        {
            order="";
            catch_picture();
        }

    }
}

void MainWindow::myKillTimer(int id)
{
    killTimer(id);
    id = -1;
}


void MainWindow::on_pushButton_catch_clicked()
{
    //自动调焦
    int32_t ret1=GD_MTC_SDK_FocusAuto(mysessionid, 0);
    //延时2s，用于调焦
    QTime dieTime = QTime::currentTime().addMSecs(6000);
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    if(ret1!=NO_ERROR)
    {
        qDebug()<<"自动调焦失败"<<mysessionid;
    }
    else
    {
        qDebug()<<"自动调焦成功"<<mysessionid;

        //抓图
        QString path=ui->directorycomboBox->currentText();
        path.append("\\");
        path.append(QString("%1").arg(pTempPointhigh.PointTemp));
        path.append("_");
        path.append(QString("%1").arg(pTempPointlow.PointTemp));
        path.append(".jpg");
        ui->textEdit_log->append(path);
        char* strFilePath;
        QByteArray ba = path.toLatin1();
        strFilePath=ba.data();
        int32_t ret2= GD_MTC_SDK_SnapPictureUniform(mysessionid, strFilePath, true, true, true, 0, 0);
        if(ret2==NO_ERROR)
        {
            qDebug()<<"抓图成功";
            ui->textEdit_log->append("抓图成功");

        }
        else
        {
            qDebug()<<"抓图失败";
            ui->textEdit_log->append("抓图失败");
        }
    }

}
