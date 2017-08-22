#include "database.h"
#include "logger.h"

#define DATABASE_HOST "Konrad-MSI"
#define DATABASE_PORT   3306

CDatabase::CDatabase(QObject *parent) : QObject(parent)
{
    m_sqlDatabase = QSqlDatabase::addDatabase("QMYSQL");
    m_sqlDatabase.setHostName(DATABASE_HOST);
    m_sqlDatabase.setDatabaseName("SecuCarDatabase");
    m_sqlDatabase.setUserName("manager");
    m_sqlDatabase.setPassword("zaq12WSX");
    m_sqlDatabase.setPort(DATABASE_PORT);

    if (m_sqlDatabase.open())
    {
        LOG_DBG("Database successfully opened");
    }
    else
    {
        LOG_FATAL("COULD NOT OPEN THE DATABASE. Aborting...");
        abort();
    }
}

CDatabase* CDatabase::GetInstance()
{
    static CDatabase s_instance;
    return &s_instance;
}
