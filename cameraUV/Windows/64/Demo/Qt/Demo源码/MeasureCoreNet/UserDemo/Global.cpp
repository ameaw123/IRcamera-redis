#include "Global.h"
#include "MeasureCoreNet.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>
  
std::string deviceTypeToStr(int nType)
{
	if (GD_MTC_IRDeviceType::OR == nType)
	{
		return "OR";
	}
	else if (GD_MTC_IRDeviceType::OR2 == nType)
	{
		return "OR2";
	}
	else if (GD_MTC_IRDeviceType::NET == nType)
	{
		return "NET";
	}
	else if (GD_MTC_IRDeviceType::NET800x600 == nType)
	{
		return "NET800x600";
	}
	else if (GD_MTC_IRDeviceType::NET384x288 == nType)
	{
		return "NET384x288";
	}
	else if (GD_MTC_IRDeviceType::NET384x288NOCLIP == nType)
	{
		return "NET384x288NOCLIP";
	}
	else if (GD_MTC_IRDeviceType::NET384x288NOCLIPFIXFOCUS == nType)
	{
		return "NET384x288NOCLIPFIXFOCUS";
	}
	else if (GD_MTC_IRDeviceType::ZU02B384x288 == nType)
	{
		return "ZU02B384x288";
	}
	else if (GD_MTC_IRDeviceType::NETHS == nType)
	{
		return "NETHS";
	}
	else if (GD_MTC_IRDeviceType::NET800x600HS == nType)
	{
		return "NET800x600HS";
	}
    else if (GD_MTC_IRDeviceType::NET640x480HS == nType)
    {
        return "NET640x480HS";
    }
	else if (GD_MTC_IRDeviceType::NET384x288NOCLIPHS == nType)
	{
		return "NET384x288NOCLIPHS";
	}
	else if (GD_MTC_IRDeviceType::ORHS == nType)
	{
		return "ORHS";
	}
	else if (GD_MTC_IRDeviceType::ZU07A384x288 == nType)
	{
		return "ZU07A384x288";
	}
	else if (GD_MTC_IRDeviceType::NET384x288HAOBOHS == nType)
	{
		return "NET384x288HAOBOHS";
	}
	else if (GD_MTC_IRDeviceType::NET640x480HAOBOHS == nType)
	{
		return "NET640x480HAOBOHS";
	}
	else if (GD_MTC_IRDeviceType::ZU02C384x288HS == nType)
	{
		return "ZU02C384x288HS";
	}
	else if (GD_MTC_IRDeviceType::ZS02B640x480HS == nType)
	{
		return "ZS02B640x480HS";
	}
	else
	{
		return "UNKNOWN";
	}
}

void centerWidget(QWidget * p)
{
	QDesktopWidget* desktop = QApplication::desktop();
	p->move((desktop->width() - p->width()) / 2, (desktop->height() - p->height()) / 2);
}
