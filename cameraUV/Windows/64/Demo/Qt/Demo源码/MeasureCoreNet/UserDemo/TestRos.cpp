#include "MeasureCoreNet.h"
#include <string>


PULL_DATA_TYPE m_nPullDataType;
int m_nSessionId;
int m_nLoginId;
bool m_bDataStreamIsOpen = false;
GD_MTC_IRDeviceInfo m_deviceInfo;
static GD_MTC_TempPointInfo g_ptHigh;


static int CALLBACK y16CbFun(const GD_MTC_CALLBACK_Y16Info * pY16Info, void *pUser)
{
// 	if (true == g_bInY16Cb)
// 	{
// 		ft::log("In Y16 callback, new data ignored");
// 		return 0;
// 	}

	// 	{
	// 		ft::log(QString("fCurrentShutterTemp=%1").arg(pY16Info->y16OutputInfo.fCurrentShutterTemp));
	// 	}

	int nW = pY16Info->ImgWidth;
	int nH = pY16Info->ImgHeight;

	void * pOpque = pY16Info->pOpque;
// 	if (0 == GD_MTC_SDK_GetPointTemp(pOpque, &g_ptCursor))
// 	{
// 		;
// 	}

// 	{
// 		ft::log(QString("g_ptCursor.PointX=%1, g_ptCursor.PointY=%2").arg(g_ptCursor.PointX).arg(g_ptCursor.PointY));
// 	}

// 	g_ptCursorAd = pY16Info->Y16Data[nW * g_ptCursor.PointY + g_ptCursor.PointX];
// 
// 	g_ptCenter.PointX = pY16Info->ImgWidth / 2;
// 	g_ptCenter.PointY = pY16Info->ImgHeight / 2;
// 	if (0 == GD_MTC_SDK_GetPointTemp(pOpque, &g_ptCenter))
// 	{
// 		;
// 	}
// 
// 	g_ptCenterAd = pY16Info->Y16Data[nW * g_ptCenter.PointY + g_ptCenter.PointX];

// 	float *pTempMatrix = new float[pY16Info->ImgWidth * pY16Info->ImgHeight];
// 	if (0 == GD_MTC_SDK_GetTempMatrix(pY16Info->pOpque, pTempMatrix))
// 	{
// 		int n1 = 0;
// 	}
// 	else
// 	{
// 		int n1 = 0;
// 	}
// 
// 	delete[] pTempMatrix;
// 	pTempMatrix = 0;


	if (0 == GD_MTC_SDK_GetHighTemp(pOpque, &g_ptHigh))
	{
		g_ptHigh.PointX;
		g_ptHigh.PointY;
		g_ptHigh.PointTemp
		;
	}
// 	if (0 == GD_MTC_SDK_GetLowTemp(pOpque, &g_ptLow))
// 	{
// 		;
// 	}
// 	if (0 == GD_MTC_SDK_GetAvegTemp(pOpque, &g_ptAvg))
// 	{
// 		;
// 	}

	//g_ptHighAd = pY16Info->Y16Data[nW * g_ptHigh.PointY + g_ptHigh.PointX];
	//g_ptLowAd = pY16Info->Y16Data[nW * g_ptLow.PointY + g_ptLow.PointX];



// 	g_Rect.X = 50;
// 	g_Rect.Y = 50;
// 	g_Rect.Width = 100;
// 	g_Rect.Height = 100;
// 	if (0 == GD_MTC_SDK_GetRectHighTemp(pOpque, g_Rect, &g_ptRectHigh))
// 	{
// 		;
// 	}
// 	if (0 == GD_MTC_SDK_GetRectLowTemp(pOpque, g_Rect, &g_ptRectLow))
// 	{
// 		;
// 	}
// 	if (0 == GD_MTC_SDK_GetRectAvegTemp(pOpque, g_Rect, &g_ptRectAvg))
// 	{
// 		;
// 	}

	return 0;
}

void OnBnClickedButtonCloseStream()
{
	// TODO: 在此添加控件通知处理程序代码

	int n1 = GD_MTC_SDK_CloseStream(m_nSessionId);
	m_nSessionId = -1;
	n1 = GD_MTC_SDK_Logout(m_nLoginId);
	m_nLoginId = -1;
	//GD_MTC_SDK_Release();
	n1 = n1;
	m_bDataStreamIsOpen = false;

// 	this->updataControlState();
// 
// 	this->onLinkStateChange(2);

	//QThread::msleep(1000);
	GD_MTC_LogMemInfo();
}


void openStreamDlg()
{
	PULL_DATA_TYPE nPullDataType = PULL_DATA_TYPE_Y16_ONLY;

	GD_MTC_IRDeviceInfo DeviceInfo;

	std::string m_strIp = "192.168.1.168";

	//auto ba = m_strIp.toLatin1();
	//strcpy(DeviceInfo.IpAddress, ba.data());
	strcpy(DeviceInfo.IpAddress, m_strIp.data());

	GD_MTC_IRDeviceType m_nDeviceType;

	//DeviceInfo.DevType = nDeviceType;
	//DeviceInfo.DevType = DEVICE_TYPE_UNKNOWN;
	DeviceInfo.DevType = m_nDeviceType;
	//DeviceInfo.DevType = GD_MTC_IRDeviceType::OR2;

	auto nLogId = GD_MTC_SDK_Login(DeviceInfo, 0);
	//ft::log(tr("nLogId=%1").arg(nLogId));
	if (GD_MTC_ERROR_CODE::ERROR_LOGIN_FAIL != nLogId)
	{
		m_nLoginId = nLogId;

		GD_MTC_IRLinkInfo IRLinkInfo;
		memset(&IRLinkInfo, 0, sizeof(IRLinkInfo));

		//IRLinkInfo.RGBCB = rgbCbFun;
		IRLinkInfo.Y16CB = y16CbFun;
		//IRLinkInfo.LinkStateCB = linkStateCbFun;

		IRLinkInfo.nPullDataType = nPullDataType;

		int nPaletteIndex = 0;
		int nFps = 15;

// 		if (m_bConfigOk)
// 		{
// 			nPaletteIndex = m_joConfig["palette"].toString().toInt();
// 			nFps = m_joConfig["fps"].toString().toInt();
// 		}

		//auto nSessionId = GD_MTC_SDK_OpenStream(nLogId, &IRLinkInfo, 0, nFps, 0);
		auto nSessionId = GD_MTC_SDK_OpenStream(nLogId, &IRLinkInfo, nPaletteIndex, nFps, (int *)0);
		//ft::log(tr("nSessionId=%1").arg(nSessionId));
		if (ERROR_OPENSTREAM_FAIL != nSessionId)
		{
			//m_nPaletteIndex = nPaletteIndex;

			m_bDataStreamIsOpen = true;
			//m_bSetSpanInitValue = false;
			m_nPullDataType = nPullDataType;
			m_nSessionId = nSessionId;


// 			ui.radioButton->setChecked(true);
// 			this->onRaioBtnAdjustLightMode();
// 			ui.comboBox->setCurrentIndex(nPaletteIndex);
// 			ui.comboBox_4->setCurrentIndex(nFps - 1);

			// Test
			// 			{
			// 				m_nSessionId = nSessionId;
			// 				return;
			// 			}

			GD_MTC_IRDeviceInfo deviceInfo;
			//ft::log("GD_MTC_SDK_GetDeviceInfo");
			int nRtn = GD_MTC_SDK_GetDeviceInfo(m_nLoginId, &deviceInfo, 0);
			if (GD_MTC_ERROR_CODE::ERROR_GETDEVICEINFO_FAIL != nRtn)
			{
				m_deviceInfo = deviceInfo;

				m_nDeviceType = deviceInfo.DevType;
				//this->updataControlState();
// 				{
// 					ft::log(QString("deviceInfo.DevType=%1").arg(deviceInfo.DevType));
// 				}
				//this->setWindowTitle(QString::fromStdString(deviceTypeToStr(deviceInfo.DevType)));
// 				int n1 = 0;
// 				m_nResizeCount = 2;

// 				m_joConfig["ip"] = m_strIp;
// 				m_joConfig["mode"] = QString::number((int)nPullDataType);
// 				m_joConfig["fps"] = QString::number(nFps);
// 				m_joConfig["palette"] = QString::number(nPaletteIndex);
// 				this->writeConfigFile();



				// 获取色带信息
				//this->getPaletteData();	

				m_nPullDataType = nPullDataType;
// 				this->updataControlState();
// 				{
// 					ft::log(QString("deviceInfo.DevType=%1").arg(m_nDeviceType));
// 				}
// 				this->setWindowTitle(QString::fromStdString(deviceTypeToStr(m_nDeviceType)));
// 				m_nResizeCount = 2;

				//m_nSessionId = nSessionId;
			}
			else
			{
				//ft::log("GD_MTC_SDK_GetDeviceInfo failed.");
				int n1 = 0;
				//this->tip(QString(u8"获取设备信息失败"));


				OnBnClickedButtonCloseStream();
			}
		}
		else
		{
			//ft::logError("openStream failed.");

			GD_MTC_SDK_Logout(m_nLoginId);
		}
	}
	else
	{
		//ft::logError("Login failed.");
	}
}


