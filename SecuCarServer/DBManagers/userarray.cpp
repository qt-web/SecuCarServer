#include "userarray.h"
#include "database.h"
#include "userrecord.h"
#include "logger.h"
#include <QSqlQuery>

CUserArray::CUserArray()
{

}

CUserArray* CUserArray::GetInstance()
{
    static CUserArray s_instance;
    return &s_instance;
}

bool CUserArray::Insert(Record record)
{
    CUserRecord* rec = dynamic_cast<CUserRecord>(record);

    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. Should be CUserRecord");
        return false;
    }

    QString qQuery =    QString::number(rec->GetUserId()) + "," +
                        QString::fromStdString(rec->GetUserName()) + "," +
                        QString::fromStdString(rec->GetName()) + "," +
                        QString::fromStdString(rec->GetSurname()) + "," +
                        QString::fromStdString(rec->GetCity()) + "," +
                        QString::fromStdString(rec->GetStreet()) + "," +
                        QString::number(rec->GetHomeNumber()) + "," +
                        QString::number(rec->GetFlatNumber()) + "," +
                        QString::fromStdString(rec->GetPostalCode()) + "," +
                        QString::fromStdString(rec->GetPasswordHash());

    return CDatabase::GetInstance()->Insert("USERS", qQuery.toStdString());
}


bool CUserArray::Update(Record record)
{

}

bool CUserArray::Delete(int recordId)
{
    std::string where = "idUser=" + QString::number(recordId).toStdString();
    return CDatabase::GetInstance()->Delete("USERS", where);
}

QList<Record> CUserArray::Select(int recordId)
{
    std::string where = "idUsers=" + QString::number(recordId).toStdString();
    QSqlQuery ret = CDatabase::Select("USERS", "*", where);
    QList<Record> foundRecordsList;

    while (ret.next())
    {
        CUserRecord record( ret.value("idUser").toInt(),
                            ret.value("userName").toString().toStdString(),
                            ret.value("name").toString().toStdString(),
                            ret.value("surname").toString().toStdString(),
                            ret.value("city").toString().toStdString(),
                            ret.value("street").toString().toStdString(),
                            ret.value("homeNumber").toInt(),
                            ret.value("flatNumber").toInt(),
                            ret.value("postalCode").toString().toStdString(),
                            ret.value("passwordHash").toString().toStdString());
        foundRecordsList.append(record);
    }

    return foundRecordsList;
}

QList<CUserRecord> CUserArray::Select(std::__cxx11::string username)
{

}
