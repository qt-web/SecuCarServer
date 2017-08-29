#ifndef TRACKARRAY_H
#define TRACKARRAY_H

#include "trackrecord.h"
#include <QList>
#include "dbmanager.h"

class CTrackArray : public IDBManager
{
public:
    CTrackArray();

    static CTrackArray* GetInstance();

    int Insert(Record &record);

    bool Delete(int recordId);

    QList<Record> Select(int recordId = -1);

    QList<CTrackRecord> SelectAllByDevice(int idDevice);

    bool Update(Record& record);

private:
    std::string m_columnNames;
};

#endif // TRACKARRAY_H
