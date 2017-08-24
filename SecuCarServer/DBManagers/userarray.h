#ifndef USERARRAY_H
#define USERARRAY_H

#include <QList>
#include "crecord.h"
#include "dbmanager.h"
#include "userrecord.h"

class CUserArray : public IDBManager
{
public:
    static CUserArray* GetInstance();

    bool Insert(Record &record);

    bool Delete(int recordId);

    QList<Record> Select(int recordId);

    bool Update(Record& record);

    QList<CUserRecord> Select(std::string username);

private:
    CUserArray();
};

#endif // USERARRAY_H
