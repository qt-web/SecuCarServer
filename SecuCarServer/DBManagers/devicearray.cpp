#include "devicearray.h"
#include "databasedriver.h"
#include "devicerecord.h"
#include "logger.h"
#include <QSqlQuery>
#include <QList>

CDeviceArray::CDeviceArray()
{

}

CDeviceArray* CDeviceArray::GetInstance()
{
    static CDeviceArray s_instance;
    return &s_instance;
}

bool CDeviceArray::Insert(Record& record)
{
    CDeviceRecord* rec = dynamic_cast<CDeviceRecord*>(&record);

    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. Should be CDeviceRecord");
        return false;
    }

    QString qQuery =    "'" + QString::number(rec->GetDeviceId()) + "', " +
                        "'" + QString::number(rec->GetUserId()) + "', " +
                        "'" + QString::number(rec->GetSerialNumber()) + "', " +
                        "'" + QString::fromStdString(rec->GetLastLocation()) + "', " +
                        "'" + QString::fromStdString(rec->GetDeviceName()) + "', " +
                        "'" + QString::number(rec->GetFirmwareVersion()) + "'";


    return CDatabaseDriver::GetInstance()->Insert("DEVICES", qQuery.toStdString());
}


bool CDeviceArray::Update(Record &record)
{
    CDeviceRecord* rec = dynamic_cast<CDeviceRecord*>(&record);
    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. should be CDeviceRecord");
        return false;
    }

    QString fieldsToUpdate =    "idDevice='" + QString::number(rec->GetDeviceId()) + "', " +
                                "idUser='" + QString::number(rec->GetUserId()) + "', " +
                                "serialNumber='" + QString::number(rec->GetSerialNumber()) + "', " +
                                "currentLocation='" + QString::fromStdString(rec->GetLastLocation()) + "', " +
                                "deviceName='" + QString::fromStdString(rec->GetDeviceName()) + "', " +
                                "programVersion='" + QString::number(rec->GetFirmwareVersion()) + "'";

    return CDatabaseDriver::GetInstance()->Update("DEVICES", fieldsToUpdate.toStdString(), QString("idDevice='" + QString::number(rec->GetDeviceId()) + "'").toStdString());
}

bool CDeviceArray::Delete(int recordId)
{
    std::string where = "idDevice='" + QString::number(recordId).toStdString() + "'";
    return CDatabaseDriver::GetInstance()->Delete("DEVICES", where);
}

QList<Record> CDeviceArray::Select(int recordId)
{
    std::string where = "";
    if (recordId != -1)
    {
        where = "idDevice='" + QString::number(recordId).toStdString() + "'";
    }

    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("DEVICES", "*", where);
    QList<Record> foundRecordsList;

    while (ret.next())
    {
        CDeviceRecord record(
                            ret.value("idDevice").toInt(),
                            ret.value("idUser").toInt(),
                            ret.value("serialNumber").toInt(),
                            ret.value("currentLocation").toString().toStdString(),
                            ret.value("deviceName").toString().toStdString(),
                            ret.value("programVersion").toInt()
                            );


        foundRecordsList.append(record);
    }

    return foundRecordsList;
}

QList<CDeviceRecord> CDeviceArray::Select(std::__cxx11::string deviceName)
{
    std::string where = "deviceName='" + deviceName + "'";
    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("DEVICES", "*", where);
    QList<CDeviceRecord> foundRecordsList;

    while (ret.next())
    {
        CDeviceRecord record(
                            ret.value("idDevice").toInt(),
                            ret.value("idUser").toInt(),
                            ret.value("serialNumber").toInt(),
                            ret.value("currentLocation").toString().toStdString(),
                            ret.value("deviceName").toString().toStdString(),
                            ret.value("programVersion").toInt()
                            );

        foundRecordsList.push_back(record);
    }

    return foundRecordsList;
}
