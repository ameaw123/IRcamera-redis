#ifndef FTBASIC_H
#define FTBASIC_H
#include <QByteArray>
#include <QDateTime>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfoList>
#include <QDir>
#include <QUuid>
#include <vector>
#include <string>

class QPixmap;
class Log;

namespace ft
{
    void init(Log * pLog);
    void log(const QString & s);
    void logError(const QString & s);
    void logWarning(const QString & s);

    bool makePath(const QString & strPath);
    bool removePath(const QString & strPath);
    bool renameFolder(const QString & strPathOld, const QString & strPathNew);
    QByteArray pixmapToByteArray(const QPixmap & pixmap, const char * format);
    QByteArray imageToByteArray(const QImage & pixmap, const char * format);
    QString byteArrayToString(const QByteArray & ba);
	std::string byteArrayToString(void * pData, int nDataLen);
	std::vector<unsigned char> stringToByteArray(const std::string & s);
    QString dateTimeToString(const QDateTime & dt);
    QString dateTimeToStringMs(const QDateTime & dt);
    QString currentDateTimeString();
    QString currentDateTimeStringMs();
    QDateTime stringToDateTime(const QString & strDt);
    QDateTime stringMsToDateTime(const QString & strDt);
    bool writeFile(const QString & strPath, const QByteArray & ba);
    bool readFile(const QString & strPath, QByteArray & ba);
    bool removeFile(const QString & strPath);
    bool checkDirExist(const QString & strPath, int nCheckMs = 2000);
    bool checkDirNotExist(const QString & strPath, int nCheckMs = 2000);
    QByteArray toJson(const QJsonObject & jo, QJsonDocument::JsonFormat format = QJsonDocument::Indented);
    bool saveToJsonFile(const QString & strPath, const QJsonObject & jo, QJsonDocument::JsonFormat format = QJsonDocument::Indented);
    bool copyDirToDir(const QString & strDir1, const QString & strDir2);
    bool copyDirToDir_FileSuffix(const QString & strDirFrom, const QString & strDirTo, const QString & strFileSuffix);

    QString exeDir();

    QString uuid();
    QFileInfoList getAllFilesAndFolders(const QString & strDir, QDir::Filters filter = QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDir::SortFlags sort = QDir::Type);
    QFileInfoList getAllFolders(const QString & strDir);
    QFileInfoList getAllFiles(const QString & strDir);

    template<class T1>
    bool parseJsonFile(const QString & strJsonFilepath, T1 fun)
    {
        QByteArray ba;
        if(true == readFile(strJsonFilepath, ba))
        {
            QJsonParseError jsnErr;
            QJsonDocument doc = QJsonDocument::fromJson(ba, &jsnErr);
            if(jsnErr.error == QJsonParseError::NoError && doc.isObject())
            {
                QJsonObject obj = doc.object();

                return fun(obj);
            }
            else
            {
                logError(QString("Parse json file %1 failed.").arg(strJsonFilepath));
            }
        }
        else
        {
            logError(QString("Open file %1 failed.").arg(strJsonFilepath));
        }

        return false;
    }
}

#endif // FTBASIC_H
