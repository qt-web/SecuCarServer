#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>

class CDatabase : public QObject
{
    Q_OBJECT
public:
    static CDatabase* GetInstance();

    bool Insert(std::string tableName, std::string record);

    bool Delete(std::string tablename, std::string where = "");

    QSqlRecord Select(std::string tableName, std::string fields, std::string where = "");

    QSqlRecord Join(std::string tableNames, std::string where = "");

signals:

public slots:

private:
    explicit CDatabase(QObject *parent = 0);

    QSqlDatabase m_sqlDatabase;
};

#endif // DATABASE_H
