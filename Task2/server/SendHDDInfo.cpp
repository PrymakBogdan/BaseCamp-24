#include "SendHDDInfo.h"

cHddInfo::cHddInfo(){}
cHddInfo::~cHddInfo(){}

#ifdef _WIN32

bool cHddInfo::setName()
{
    // GetDiskFreeSpaceEx(NULL, &Free, &Total, &TotalFree);

    // qDebug() << "\nFree: " << (double) Free.QuadPart / GB;
    // qDebug() << "\nTotal: " << (double) Total.QuadPart / GB;

    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    if (GetComputerNameA(computerName, &size))
    {
        QString str(computerName);
        this->pcName = str;
        return true;
    }
    else
    {
        qDebug() << "Error getting computer name";
        return false;
    }
}

bool cHddInfo::setInfo()
{
    if(GetDiskFreeSpaceEx(NULL, &Free, &Total, &TotalFree))
    {
        this->freeMem = QString::number((double) Free.QuadPart / GB);
        this->allMem = QString::number((double) Total.QuadPart / GB);
        return true;
    }

    else
        return false;
}

#endif

#ifdef __linux__
bool cHddInfo::setName()
{
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        QString str (hostname);
        this->pcName = str;
    }
    else
    {
        qDebug() << "Error getting hostname";
        return false;
    }
}

bool cHddInfo::setInfo()
{
    qDebug() << "Free Mem =" << (double) vfs.f_bavail * vfs.f_frsize  / GB;
    qDebug() << "All Mem =" << (double) vfs.f_blocks * vfs.f_frsize / GB ;
}
#endif

QString cHddInfo::getPCName()
{
    return this->pcName;
}

QString cHddInfo::getAllMem()
{
    return this->allMem;
}

QString cHddInfo::getFreeMem()
{
    return this->freeMem;
}
