#ifndef SENDHDDINFO_H
#define SENDHDDINFO_H
#include <QTcpServer>
#include <QTcpSocket>
#include <Qvector>

#define GB 1073741824

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <sys/statvfs.h>
#include <unistd.h>
#endif

class cHddInfo
{
private:
    QString pcName;
    QString allMem;
    QString freeMem;

public:
#ifdef _WIN32
    ULARGE_INTEGER Free;
    ULARGE_INTEGER Total;
    ULARGE_INTEGER TotalFree;
#endif

#ifdef __linux__
    struct statvfs vfs;
#endif

    cHddInfo();
    ~cHddInfo();
    bool setName();
    bool setInfo();
    QString getPCName();
    QString getAllMem();
    QString getFreeMem();

};

#endif // SENDHDDINFO_H
