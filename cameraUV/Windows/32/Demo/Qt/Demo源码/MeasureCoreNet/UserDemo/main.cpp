#include "UserDemo.h"
#include <QtWidgets/QApplication>
#include "NetWidget.h"

#include "FileLog.h"
#include "ftBasic.h"

#include "Global.h"
   
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QString strLogDir = QString("%1\\Log").arg(ft::exeDir());
	ft::init(new ft::FileLog(strLogDir, ""));

    //UserDemo w;
	NetWidget w;
    w.show();
	centerWidget(&w);

	a.installEventFilter(&w);

    return a.exec();
}
