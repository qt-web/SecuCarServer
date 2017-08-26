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

    QList<Record> Select(int recordId = -1);

    bool Update(Record& record);

    QList<CUserRecord> Select(std::string username);

private:
    CUserArray();

    std::string m_columnNames;
};

#endif // USERARRAY_H
