#ifndef DATABASEDRIVER_H
#define DATABASEDRIVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlResult>

/**
 * @brief The CDatabaseDriver class - This is a singleton class responsible for the lowest level communication with database.
 *                  It should be never used directly, only through Arrays managers
 */
class CDatabaseDriver : public QObject
{
    Q_OBJECT
public:
    explicit CDatabaseDriver(QObject *parent = 0);

    static CDatabaseDriver* GetInstance();

    /**
     * @brief Insert - Inserts record in the database
     * @param tableName[in] - name of the table where the record should be put
     * @param columnNames[in] - names of columns (in order as the record fields)
     * @param record[in] - record which should be put
     * @return idRecord - id of the record if put successfully. -1 otherwise
     */
    int Insert(std::string tableName, std::__cxx11::string columnNames, std::string record);

    /**
     * @brief Update - Updates the record (in where statement)
     * @param tableName[in] - table name where the record to be updated lies.
     * @param fields[in] - values which will be updated
     * @param where[in] - the condition allowing to 'select' the correct record to be updated
     * @return true if success, false otherwise
     */
    bool Update(std::string tableName, std::string fields, std::string where);

    /**
     * @brief Delete - Deletes the record
     * @param tablename[in] - Table name where the record to be deleted lies
     * @param where[in] - condition which allows to 'select' the record to be deleted
     * @return true - if success, false otherwise
     */
    bool Delete(std::string tablename, std::string where = "");

    /**
     * @brief Select - Searches for the records which meet the condition(where statement)
     * @param tableName[in] - Name of the table in which the records are to be searched
     * @param fields[in] - fields which interest us
     * @param where[in] - condition selecting the records
     * @return
     */
    const QSqlQuery Select(std::string tableName, std::string fields, std::string where = "");

    /**
     * @brief Join - TO BE IMPLEMENTED
     * @param tableNames
     * @param where
     * @return
     */
    QSqlRecord Join(std::string tableNames, std::string where = "");

signals:

public slots:

private:

    //  Sql Database connector
    QSqlDatabase m_sqlDatabase;
};

#endif // DATABASEDRIVER_H
