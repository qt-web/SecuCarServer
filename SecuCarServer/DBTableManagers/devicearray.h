#ifndef DEVICEARRAY_H
#define DEVICEARRAY_H

#include "dbmanager.h"
#include "devicerecord.h"

class CDeviceArray
{
public:
    CDeviceArray();

    static CDeviceArray* GetInstance();

    int Insert(Record &record);

    bool Delete(int recordId);

    QList<CDeviceRecord> Select(int recordId = -1);

    bool Update(Record& record);

    QList<CDeviceRecord> Select(std::string deviceName);

    QList<CDeviceRecord> SelectAllByUser(int idUser);

private:
    std::string m_columnNames;
};

#endif // DEVICEARRAY_H
