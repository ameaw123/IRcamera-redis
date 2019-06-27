#ifndef LOG_H
#define LOG_H
#include <QString>

namespace ft
{
    class Log
    {
    public:
        virtual void log(const QString & s) = 0;
        virtual void logWarning(const QString & s) = 0;
        virtual void logError(const QString & s) = 0;
    };
}

#endif // LOG_H
