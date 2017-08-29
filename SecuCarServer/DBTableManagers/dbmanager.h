#ifndef IDBMANAGER_H
#define IDBMANAGER_H
#include <QList>
#include "crecord.h"

/**
 * @brief The IDBManager class - Interface to use basic sql queries on single tables
 */
class IDBManager
{
public:

    /**
     * @brief Insert - Insert record in the table
     * @param record[in]
     * @return
     */
    virtual int Insert(Record& record) = 0;

    /**
     * @brief Delete - Delete the record from the table
     * @param recordId[in] - id of the record to be deleted
     * @return
     */
    virtual bool Delete(int recordId) = 0;

    /**
     * @brief Select - Selects the record with the given ID
     * @param recordId[in] - list of records (single record)
     * @return - Record list if record found, empty list otherwise
     */
    virtual QList<Record> Select(int recordId) = 0;

    /**
     * @brief Update - Updates the record
     * @param record[in] - the updated record which should be pu in the database
     * @return
     */
    virtual bool Update(Record& record) = 0;

};

#endif // IDBMANAGER_H
