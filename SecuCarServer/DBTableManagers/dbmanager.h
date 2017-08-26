#ifndef IDBMANAGER_H
#define IDBMANAGER_H
#include <QList>
#include "crecord.h"

class IDBManager
{
public:

    virtual int Insert(Record& record) = 0;

    virtual bool Delete(int recordId) = 0;

    virtual QList<Record> Select(int recordId) = 0;

    virtual bool Update(Record& record) = 0;

};

#endif // IDBMANAGER_H
