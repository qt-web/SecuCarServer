#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlResult>

class CDatabase : public QObject
{
    Q_OBJECT
public:
    explicit CDatabase(QObject *parent = 0);

    static CDatabase* GetInstance();

    bool Insert(std::string tableName, std::string record);

    bool Delete(std::string tablename, std::string where = "");

    const QSqlQuery Select(std::string tableName, std::string fields, std::string where = "");

    QSqlRecord Join(std::string tableNames, std::string where = "");

signals:

public slots:

private:


    QSqlDatabase m_sqlDatabase;
};

#endif // DATABASE_H
