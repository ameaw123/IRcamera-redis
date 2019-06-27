#include "FileLog.h"
#include <QFile>
#include <QDir>

namespace ft
{
    FileLog::FileLog(const QString & strLogFileDir, const QString & strFileNameMark)
        : m_strLogFileDir(strLogFileDir)
        , m_strMark(strFileNameMark)
        , m_ExeStartDate(QDate::currentDate())
        , m_pFile(NULL)
    {
        // no op
    }

    FileLog::~FileLog()
    {
        if(NULL != m_pFile)
        {
            m_pFile->close();
            delete m_pFile;
            m_pFile = NULL;
        }
    }

    void FileLog::log(const QString & s)
    {
        writeLogFile(1, s);
    }

    void FileLog::logWarning(const QString & s)
    {
        writeLogFile(2, s);
    }

    void FileLog::logError(const QString & s)
    {
        writeLogFile(3, s);
    }

    bool FileLog::createLogFile(QFile *& pFile)
    {
        QString strCurLogFilePath = QString("%1/Log_%2_%3.log")
                                    .arg(m_strLogFileDir)
                                    .arg(m_strMark)
                                    .arg(QDate::currentDate().toString("yyyy-MM-dd"));

        QDir Dir(m_strLogFileDir);
        if(false == Dir.exists())
        {
            Dir.mkdir(m_strLogFileDir);
        }

        QFile * pFileTemp = new QFile(strCurLogFilePath);
        if(NULL != pFileTemp)
        {
            if(true == QFile::exists(strCurLogFilePath))
            {
                if(true == pFileTemp->open(QIODevice::WriteOnly | QIODevice::Append))
                {
                    pFile = pFileTemp;
                    return true;
                }
            }
            else
            {
                if(true == pFileTemp->open(QIODevice::WriteOnly))
                {
                    QByteArray ba;
                    ba.append((char)0xFF).append((char)0xFE);
                    pFileTemp->write(ba);
                    pFileTemp->flush();

                    pFile = pFileTemp;
                    return true;
                }
            }
            delete pFileTemp;
            pFileTemp = NULL;
        }

        return false;
    }

    void FileLog::writeLogFile(int nLevel, const QString & s)
    {
        QWriteLocker Locker(&m_LogReadWriteLock);

        if(NULL == m_pFile)
        {
            if(true == createLogFile(m_pFile))
            {
                m_ExeStartDate = QDate::currentDate();
            }
        }
        else
        {
            if(m_ExeStartDate != QDate::currentDate())
            {
                m_pFile->close();
                delete m_pFile;
                m_pFile = NULL;

                if(true == createLogFile(m_pFile))
                {
                    m_ExeStartDate = QDate::currentDate();
                }
            }
        }

        if(NULL != m_pFile)
        {
            QString strLine = QTime::currentTime().toString("[HH:mm:ss zzz]");
            if(1 == nLevel)
            {
                strLine.append(":  ");
            }
            else if(2 == nLevel)
            {
                strLine.append(":  WARNING!");
            }
            else if(3 == nLevel)
            {
                strLine.append(":  ERROR!");
            }
            strLine.append(s).append("\r\n");

            m_pFile->write((const char *)strLine.unicode(), strLine.size() * 2);
            m_pFile->flush();
        }
    }
}
