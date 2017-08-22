#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class CDatabase : public QObject
{
    Q_OBJECT
public:
    static CDatabase* GetInstance();


signals:

public slots:

private:
    explicit CDatabase(QObject *parent = 0);

    QSqlDatabase m_sqlDatabase;
};

#endif // DATABASE_H
