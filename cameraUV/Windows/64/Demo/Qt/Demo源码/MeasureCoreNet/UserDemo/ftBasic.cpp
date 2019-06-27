#include "ftBasic.h"
#include <QBuffer>
#include <QFile>
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>
#include <QThread>
#include "Log.h"

namespace ft
{
    Log * m_pLog = NULL;

    void init(Log * pLog)
    {
        m_pLog = pLog;
    }

    void log(const QString & s)
    {
        if(NULL != m_pLog)
        {
            m_pLog->log(s);
        }
    }

    void logError(const QString & s)
    {
        if(NULL != m_pLog)
        {
            m_pLog->logError(s);
        }
    }

    void logWarning(const QString & s)
    {
        if(NULL != m_pLog)
        {
            m_pLog->logWarning(s);
        }
    }

    QByteArray pixmapToByteArray(const QPixmap & pixmap, const char * format)
    {
        QByteArray ba;
        QBuffer buffer(&ba);
        if(true == buffer.open(QIODevice::WriteOnly))
        {
            if(pixmap.save(&buffer, format))
            {
                return ba;
            }
            else
            {
                logError(QString("Save data to buffer failed."));
            }
        }
        else
        {
            logError(QString("Open buffer failed."));
        }
        return QByteArray();
    }

    QByteArray imageToByteArray(const QImage & pixmap, const char * format)
    {
        QByteArray ba;
        QBuffer buffer(&ba);
        if(true == buffer.open(QIODevice::WriteOnly))
        {
            if(pixmap.save(&buffer, format))
            {
                return ba;
            }
            else
            {
                logError(QString("Save data to buffer failed."));
            }
        }
        else
        {
            logError(QString("Open buffer failed."));
        }
        return QByteArray();
    }

    QString byteArrayToString(const QByteArray & ba)
    {
        QString strMsg;
        int nSize = ba.size();
        for (int i = 0; i < nSize; ++i)
        {
            if(i > 0)
            {
                strMsg.append(", ");
            }
            strMsg.append(QString::asprintf("0x%02X", (unsigned char)ba[i]));
        }
        return strMsg;
    }

	std::string byteArrayToString(void * pData, int nDataLen)
	{
		std::string s1;

		char cBuf[50] = { 0 };

		for (int i = 0; i < nDataLen; i++)
		{
			if (i > 0)
			{
				s1 += ",";
			}

			unsigned char ch = *((unsigned char *)pData + i);
			sprintf(cBuf, "%d", ch);
			s1 += cBuf;
		}

		return s1;
	}

	std::vector<unsigned char> stringToByteArray(const std::string & s)
	{
		std::vector<unsigned char> v;
		int ch;
		int nOff = 0;

		while (1)
		{
			auto nPos = s.find(',', nOff);
			if (-1 != nPos)
			{
				auto strNum = s.substr(nOff, nPos - nOff);
				sscanf(strNum.data(), "%d", &ch);
				v.push_back(ch);

				nOff = nPos + 1;
			}
			else
			{
				auto strNum = s.substr(nOff);
				sscanf(strNum.data(), "%d", &ch);
				v.push_back(ch);
				break;
			}
		}
		return v;
	}

	QString dateTimeToString(const QDateTime & dt)
    {
        return dt.toString("yyyyMMddHHmmss");
    }

    QString dateTimeToStringMs(const QDateTime & dt)
    {
        return dt.toString("yyyyMMddHHmmsszzz");
    }

    QString currentDateTimeString()
    {
        return dateTimeToString(QDateTime::currentDateTime());
    }

    QString currentDateTimeStringMs()
    {
        return QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz");
    }

    QDateTime stringToDateTime(const QString & strDt)
    {
        return QDateTime::fromString(strDt, "yyyyMMddHHmmss");
    }

    QDateTime stringMsToDateTime(const QString & strDt)
    {
        return QDateTime::fromString(strDt, "yyyyMMddHHmmsszzz");
    }

    bool writeFile(const QString & strPath, const QByteArray & ba)
    {
        QFile File(strPath);
        if(true == File.open(QIODevice::WriteOnly))
        {
            File.write(ba);
            File.flush();
            File.close();
            return true;
        }
        else
        {
            logError(QString("Open file %1 failed.").arg(strPath));
        }
        logError(QString("Write file %1 failed.").arg(strPath));
        return false;
    }

    bool readFile(const QString & strPath, QByteArray & ba)
    {
        QFile File(strPath);
        if(true == File.open(QIODevice::ReadOnly))
        {
            ba = File.readAll();
            File.close();
            return true;
        }
        else
        {
            logError(QString("Open file %1 failed.").arg(strPath));
        }
        logError(QString("Read file %1 failed.").arg(strPath));
        return false;
    }

    bool checkDirExist(const QString & strPath, int nCheckMs)
    {
        QDateTime dtCur = QDateTime::currentDateTime();

        while(1)
        {
            QDir dir2(strPath);
            if(true == dir2.exists())
            {
                return true;
            }

            QThread::msleep(5);

            if(dtCur.msecsTo(QDateTime::currentDateTime()) > nCheckMs)
            {
                break;
            }
        }
        return false;
    }

    bool checkDirNotExist(const QString & strPath, int nCheckMs)
    {
        QDateTime dtCur = QDateTime::currentDateTime();

        while(1)
        {
            QDir dir2(strPath);
            if(false == dir2.exists())
            {
                return true;
            }

            QThread::msleep(5);

            if(dtCur.msecsTo(QDateTime::currentDateTime()) > nCheckMs)
            {
                break;
            }
        }
        return false;
    }

    bool removeFile(const QString & strPath)
    {
        if(false == QFile::remove(strPath))
        {
            logError(QString("Remove file %1 failed.").arg(strPath));
            return false;
        }
        return true;
    }

    bool makePath(const QString & strPath)
    {
        QDir dir(strPath);
        if(false == dir.exists())
        {
            if(false == dir.mkpath(dir.path()))
            {
                logError(QString("Make path %1 failed.").arg(strPath));
                return false;
            }
        }
        return true;
    }

    bool removePath(const QString & strPath)
    {
        QDir dir(strPath);
        if(true == dir.exists())
        {
            if(false == dir.removeRecursively())
            {
                logError(QString("Remove path %1 failed.").arg(strPath));
                return false;
            }
        }
        return true;
    }


    QByteArray toJson(const QJsonObject & jo, QJsonDocument::JsonFormat format)
    {
        QJsonDocument document;
        document.setObject(jo);

        return document.toJson(format);
    }

    bool saveToJsonFile(const QString & strPath, const QJsonObject & jo, QJsonDocument::JsonFormat format)
    {
        auto ba = ft::toJson(jo, format);
        return ft::writeFile(strPath, ba);
    }

    bool copyDirToDir(const QString & strDirFrom, const QString & strDirTo)
    {
        QDir dirFrom(strDirFrom);
        if(true == dirFrom.exists())
        {
            if(true == ft::makePath(strDirTo))
            {
                auto fiFiles = getAllFiles(strDirFrom);
                auto fiFloders = getAllFolders(strDirFrom);

                // 将文件复制到目的目录
                for(auto & v1 : fiFiles)
                {
                    if(false == QFile::copy(v1.absoluteFilePath(), strDirTo + "/" + v1.fileName()))
                    {
                        logError(QString("Copy file from %1 to %2 failed.").arg(v1.absoluteFilePath()).arg(strDirTo + "/" + v1.fileName()));
                        return false;
                    }
                }

                // 将所有的文件夹及其内容复制到目的目录
                for(auto & v1 : fiFloders)
                {
                    if(false == copyDirToDir(v1.absoluteFilePath(), strDirTo + "/" + v1.fileName()))
                    {
                        return false;
                    }
                }

                return true;
            }
        }


        logError(QString("Copy dir from %1 to %2 failed.").arg(strDirFrom).arg(strDirTo));
        return false;
    }

    bool copyDirToDir_FileSuffix(const QString & strDirFrom, const QString & strDirTo, const QString & strFileSuffix)
    {
        QString strSuffixLower = strFileSuffix.toLower();

        QDir dirFrom(strDirFrom);
        if(true == dirFrom.exists())
        {
            if(true == ft::makePath(strDirTo))
            {
                auto fiFiles = getAllFiles(strDirFrom);
                auto fiFloders = getAllFolders(strDirFrom);

                // 将文件复制到目的目录
                for(auto & v1 : fiFiles)
                {
                    if(strSuffixLower == v1.suffix().toLower())
                    {
                        if(false == QFile::copy(v1.absoluteFilePath(), strDirTo + "/" + v1.fileName()))
                        {
                            logError(QString("Copy file from %1 to %2 failed.").arg(v1.absoluteFilePath()).arg(strDirTo + "/" + v1.fileName()));
                            return false;
                        }
                        else
                        {
                            ft::log(QString("Copy file from %1 to %2").arg(v1.absoluteFilePath()).arg(strDirTo + "/" + v1.fileName()));
                        }
                    }
                }

                // 将所有的文件夹及其内容复制到目的目录
                for(auto & v1 : fiFloders)
                {
                    if(false == copyDirToDir_FileSuffix(v1.absoluteFilePath(), strDirTo + "/" + v1.fileName(), strSuffixLower))
                    {
                        return false;
                    }
                }

                return true;
            }
        }

        logError(QString("Copy dir from %1 to %2 failed.").arg(strDirFrom).arg(strDirTo));
        return false;
    }

    QString exeDir()
    {
        return QCoreApplication::applicationDirPath();
    }

    QString uuid()
    {
        return QUuid::createUuid().toString();
    }

    QFileInfoList getAllFilesAndFolders(const QString & strDir, QDir::Filters filter, QDir::SortFlags sort)
    {
        QDir dir(strDir);
        dir.setFilter(filter);
        dir.setSorting(sort);

        return dir.entryInfoList();
    }

    QFileInfoList getAllFolders(const QString & strDir)
    {
        QFileInfoList fiRtn;

        QDir dir(strDir);
        dir.setFilter(QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        dir.setSorting(QDir::Type);

        QFileInfoList fi = dir.entryInfoList();
        for(auto & v1 : fi)
        {
            if(true == v1.isDir())
            {
                fiRtn.push_back(v1);
            }
        }

        return fiRtn;
    }

    QFileInfoList getAllFiles(const QString & strDir)
    {
        QFileInfoList fiRtn;

        QDir dir(strDir);
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        dir.setSorting(QDir::Type);

        QFileInfoList fi = dir.entryInfoList();
        for(auto & v1 : fi)
        {
            if(true == v1.isFile())
            {
                fiRtn.push_back(v1);
            }
        }

        return fiRtn;
    }

    bool renameFolder(const QString & strPathOld, const QString & strPathNew)
    {
        QDir d;
        if(true == d.rename(strPathOld, strPathNew))
        {
            return true;
        }
        else
        {
            logError(QString("Rename folder %1 to %2 failed.").arg(strPathOld).arg(strPathNew));
            return false;
        }
    }

}
