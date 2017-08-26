#ifndef SAMPLEARRAY_H
#define SAMPLEARRAY_H

#include "samplerecord.h"
#include "dbmanager.h"
#include <QList>

class CSampleArray : public IDBManager
{
public:
    CSampleArray();

    static CSampleArray* GetInstance();

    bool Insert(Record &record);

    bool Delete(int recordId);

    QList<Record> Select(int recordId = -1);

    bool Update(Record& record);

private:
    std::string m_columnNames;
};

#endif // SAMPLEARRAY_H
