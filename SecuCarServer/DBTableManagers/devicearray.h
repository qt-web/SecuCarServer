#ifndef DEVICEARRAY_H
#define DEVICEARRAY_H

#include "dbmanager.h"
#include "devicerecord.h"

class CDeviceArray : public IDBManager
{
public:
    CDeviceArray();

    static CDeviceArray* GetInstance();

    bool Insert(Record &record);

    bool Delete(int recordId);

    QList<Record> Select(int recordId = -1);

    bool Update(Record& record);

    QList<CDeviceRecord> Select(std::string deviceName);

    QList<CDeviceRecord> SelectAllByUser(int idUser);
};

#endif // DEVICEARRAY_H
