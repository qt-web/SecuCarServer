#include "database.h"
#include "logger.h"
#include <QStringList>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#define DATABASE_HOST   "localhost"
#define DATABASE_PORT   3306

CDatabase::CDatabase(QObject *parent) : QObject(parent)
{
    m_sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");

//    m_sqlDatabase.setHostName(DATABASE_HOST);
    m_sqlDatabase.setDatabaseName("/home/konrad/Qt_Workspace/SecuCarServer/DB/secucar.db");
//    m_sqlDatabase.setUserName("root");
//    m_sqlDatabase.setPassword("");
//    m_sqlDatabase.setPort(DATABASE_PORT);

    QStringList databaseDrivers = m_sqlDatabase.drivers();
    int index = 0;
    while (index != databaseDrivers.size())
    {
        LOG_DBG("Detected Database driver: %s", databaseDrivers[index++].toStdString().c_str());
    }

    if (m_sqlDatabase.open())
    {
        LOG_DBG("Database successfully opened");
    }
    else
    {
        LOG_ERROR("COULD NOT OPEN THE DATABASE. Aborting...");
        LOG_ERROR("Error message: %s", m_sqlDatabase.lastError().text().toStdString().c_str());
        abort();
    }
}

CDatabase* CDatabase::GetInstance()
{
    static CDatabase s_instance;
    return &s_instance;
}

bool CDatabase::Insert(std::__cxx11::string tableName, std::__cxx11::string record)
{
    QSqlRecord fields = m_sqlDatabase.record(QString::fromStdString(tableName));

    QList<QString> params = QString::fromStdString(record).split(',');

    if (params.size() != fields.count())
    {
        LOG_ERROR("Wrong number of params");
        return false;
    }

    QString queryText = "INSERT INTO " + QString::fromStdString(tableName) + " VALUES (" + QString::fromStdString(record) +  ");";
    QSqlQuery query(m_sqlDatabase);
    LOG_DBG("Querying: %s", queryText.toStdString().c_str());

    if (!query.exec(queryText))
    {
        LOG_ERROR("Query did not succeed. Error message: %s", query.lastError().text().toStdString().c_str());
        return false;
    }

    return true;
}

bool CDatabase::Delete(std::__cxx11::string tablename, std::__cxx11::string where)
{
    QString queryText = "DELETE FROM " + QString::fromStdString(tablename) + " WHERE " + QString::fromStdString(where) + ";";
    QSqlQuery query(m_sqlDatabase);
    LOG_DBG("Querying: %s", queryText.toStdString().c_str());

    if (!query.exec(queryText))
    {
        LOG_ERROR("Query did not succeed. Error message: %s", query.lastError().text().toStdString().c_str());
        return false;
    }

    return true;
}

const QSqlQuery CDatabase::Select(std::__cxx11::string tableName, std::__cxx11::string fields, std::__cxx11::string where)
{
    QString queryText = "SELECT " + QString::fromStdString(fields) + " FROM " + QString::fromStdString(tableName);

    if (!where.empty())
    {
        queryText.append(" WHERE " + QString::fromStdString(where));
    }
    queryText.append(";");

    QSqlQuery query(m_sqlDatabase);
    LOG_DBG("Querying: %s", queryText.toStdString().c_str());

    if (!query.exec(queryText))
    {
        LOG_ERROR("Query did not succeed. Error message: %s", query.lastError().text().toStdString().c_str());
        return query;
    }

    LOG_DBG("Query Succeeded. Returning %d records", query.size());
    return query;
}
