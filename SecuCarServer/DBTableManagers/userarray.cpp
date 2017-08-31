#include "userarray.h"
#include "databasedriver.h"
#include "userrecord.h"
#include "logger.h"
#include <QSqlQuery>

CUserArray::CUserArray()
{
    m_columnNames = "userName, name, surname, email, telephone, city, street, homeNumber, flatNumber, postalCode, passwordHash";
}

CUserArray* CUserArray::GetInstance()
{
    static CUserArray s_instance;
    return &s_instance;
}

int CUserArray::Insert(Record& record)
{
    CUserRecord* rec = dynamic_cast<CUserRecord*>(&record);

    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. Should be CUserRecord");
        return false;
    }
    QString fields = "userName, name, surname, email, telephone, city, street, homeNumber, flatNumber, postalCode, passwordHash";
    QString qQuery =    //"'" + QString::number(rec->GetUserId()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetUserName()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetName()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetSurname()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetEmail()) + "'" + ", " +
                        "'" + QString::number(rec->GetTelephone()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetCity()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetStreet()) + "'" + ", " +
                        "'" + QString::number(rec->GetHomeNumber()) + "'" + ", " +
                        "'" + QString::number(rec->GetFlatNumber()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetPostalCode()) + "'" + ", " +
                        "'" + QString::fromStdString(rec->GetPasswordHash()) + "'" ;

    return CDatabaseDriver::GetInstance()->Insert("USERS", m_columnNames, qQuery.toStdString());
}


bool CUserArray::Update(Record &record)
{
    CUserRecord* rec = dynamic_cast<CUserRecord*>(&record);
    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. should be CUserRecord");
        return false;
    }

    QString fieldsToUpdate =    //"idUser='" + QString::number(rec->GetUserId()) + "', " +
                                "userName='" + QString::fromStdString(rec->GetUserName()) + "', " +
                                "name='" + QString::fromStdString(rec->GetName()) + "', " +
                                "surname='" + QString::fromStdString(rec->GetSurname()) + "', " +
                                "email='" + QString::fromStdString(rec->GetEmail()) + "', " +
                                "telephone='" + QString::number(rec->GetTelephone()) + "', " +
                                "city='" + QString::fromStdString(rec->GetCity()) + "', " +
                                "street='" + QString::fromStdString(rec->GetStreet()) + "', " +
                                "homeNumber='" + QString::number(rec->GetHomeNumber()) + "', " +
                                "flatNumber='" + QString::number(rec->GetFlatNumber()) + "', " +
                                "postalCode='" + QString::fromStdString(rec->GetPostalCode()) + "', " +
                                "passwordHash='" + QString::fromStdString(rec->GetPasswordHash()) + "'";

    return CDatabaseDriver::GetInstance()->Update("USERS", fieldsToUpdate.toStdString(), QString("idUser='" + QString::number(rec->GetUserId()) + "'").toStdString());
}

bool CUserArray::Delete(int recordId)
{
    std::string where = "idUser='" + QString::number(recordId).toStdString() + "'";
    return CDatabaseDriver::GetInstance()->Delete("USERS", where);
}

QList<CUserRecord> CUserArray::Select(int recordId)
{
    std::string where = "";
    if (recordId != -1)
    {
        where = "idUser='" + QString::number(recordId).toStdString() + "'";
    }

    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("USERS", "*", where);
    QList<CUserRecord> foundRecordsList;

    while (ret.next())
    {
        CUserRecord record(
                            ret.value("idUser").toInt(),
                            ret.value("userName").toString().toStdString(),
                            ret.value("name").toString().toStdString(),
                            ret.value("surname").toString().toStdString(),
                            ret.value("email").toString().toStdString(),
                            ret.value("telephone").toInt(),
                            ret.value("city").toString().toStdString(),
                            ret.value("street").toString().toStdString(),
                            ret.value("homeNumber").toInt(),
                            ret.value("flatNumber").toInt(),
                            ret.value("postalCode").toString().toStdString(),
                            ret.value("passwordHash").toString().toStdString()
                        );

        foundRecordsList.append(record);
    }

    return foundRecordsList;
}

QList<CUserRecord> CUserArray::Select(std::__cxx11::string username)
{
    std::string where = "username='" + username + "'";
    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("USERS", "*", where);
    QList<CUserRecord> foundRecordsList;

    while (ret.next())
    {
        const CUserRecord record(
                                    ret.value("idUser").toInt(),
                                    ret.value("userName").toString().toStdString(),
                                    ret.value("name").toString().toStdString(),
                                    ret.value("surname").toString().toStdString(),
                                    ret.value("email").toString().toStdString(),
                                    ret.value("telephone").toInt(),
                                    ret.value("city").toString().toStdString(),
                                    ret.value("street").toString().toStdString(),
                                    ret.value("homeNumber").toInt(),
                                    ret.value("flatNumber").toInt(),
                                    ret.value("postalCode").toString().toStdString(),
                                    ret.value("passwordHash").toString().toStdString()
                                );

        foundRecordsList.push_back(record);
    }

    return foundRecordsList;
}
