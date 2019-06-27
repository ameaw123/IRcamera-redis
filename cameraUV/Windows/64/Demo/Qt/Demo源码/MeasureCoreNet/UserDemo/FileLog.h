#ifndef FILELOG_H
#define FILELOG_H
#include <QReadWriteLock>
#include <QWriteLocker>
#include <QDate>
#include "Log.h"

class QFile;

namespace ft
{
    class FileLog : public Log
    {
    public:
        FileLog(const QString & strLogFileDir, const QString & strFileNameMark);
        ~FileLog();

        void log(const QString & s);
        void logWarning(const QString & s);
        void logError(const QString & s);

    private:
        bool createLogFile(QFile * & pFile);
        void writeLogFile(int nLevel, const QString & s);

    private:
        QReadWriteLock m_LogReadWriteLock;

        QString m_strLogFileDir;
        QString m_strMark;

        QDate m_ExeStartDate;
        QFile * m_pFile;
    };
}

#endif // FILELOG_H
