#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlResult>

class CDatabaseDriver : public QObject
{
    Q_OBJECT
public:
    explicit CDatabaseDriver(QObject *parent = 0);

    static CDatabaseDriver* GetInstance();

    bool Insert(std::string tableName, std::string record);

    bool Update(std::string tableName, std::string fields, std::string where);

    bool Delete(std::string tablename, std::string where = "");

    const QSqlQuery Select(std::string tableName, std::string fields, std::string where = "");

    QSqlRecord Join(std::string tableNames, std::string where = "");

signals:

public slots:

private:


    QSqlDatabase m_sqlDatabase;
};

#endif // DATABASE_H
