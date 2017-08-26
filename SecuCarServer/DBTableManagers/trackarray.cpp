#include "trackarray.h"
#include "databasedriver.h"
#include "trackrecord.h"
#include "logger.h"
#include <QSqlQuery>
#include <QList>

CTrackArray::CTrackArray()
{
    m_columnNames = "idDevice, startDate, startLocation, endDate, endLocation, distance, manouverAssessment";
}

CTrackArray* CTrackArray::GetInstance()
{
    static CTrackArray s_instance;
    return &s_instance;
}

bool CTrackArray::Insert(Record& record)
{
    CTrackRecord* rec = dynamic_cast<CTrackRecord*>(&record);

    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. Should be CTrackRecord");
        return false;
    }
    QString fields = "idDevice, startDate, startLocation, endDate, endLocation, distance, manouverAssessment";
    QString qQuery =    //"'" + QString::number(rec->GetTrackId()) + "', " +
                        "'" + QString::number(rec->GetDeviceId()) + "', " +
                        "'" + QString::number(rec->GetStartTimestmap()) + "', " +
                        "'" + QString::fromStdString(rec->GetStartLocation()) + "', " +
                        "'" + QString::number(rec->GetEndTimestamp()) + "', " +
                        "'" + QString::fromStdString(rec->GetEndLocation()) + "', " +
                        "'" + QString::number(rec->GetDistance()) + "', " +
                        "'" + QString::number(rec->GetManeouverAssessment()) + "'";


    return CDatabaseDriver::GetInstance()->Insert("TRACKS (" + fields.toStdString() + ")", m_columnNames, qQuery.toStdString());
}


bool CTrackArray::Update(Record &record)
{
    CTrackRecord* rec = dynamic_cast<CTrackRecord*>(&record);
    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. should be CTrackRecord");
        return false;
    }

    QString fieldsToUpdate =        //"idTrack='" + QString::number(rec->GetTrackId()) + "', " +
                                    "idDevice='" + QString::number(rec->GetDeviceId()) + "', " +
                                    "startDate='" + QString::number(rec->GetStartTimestmap()) + "', " +
                                    "startLocation='" + QString::fromStdString(rec->GetStartLocation()) + "', " +
                                    "endDate='" + QString::number(rec->GetEndTimestamp()) + "', " +
                                    "endLocation='" + QString::fromStdString(rec->GetEndLocation()) + "', " +
                                    "distance='" + QString::number(rec->GetDistance()) + "', " +
                                    "manouverAssessment='" + QString::number(rec->GetManeouverAssessment()) + "'";

    return CDatabaseDriver::GetInstance()->Update("TRACKS", fieldsToUpdate.toStdString(), QString("idTrack='" + QString::number(rec->GetTrackId()) + "'").toStdString());
}

bool CTrackArray::Delete(int recordId)
{
    std::string where = "idTrack='" + QString::number(recordId).toStdString() + "'";
    return CDatabaseDriver::GetInstance()->Delete("TRACKS", where);
}

QList<Record> CTrackArray::Select(int recordId)
{
    std::string where = "";
    if (recordId != -1)
    {
        where = "idTrack='" + QString::number(recordId).toStdString() + "'";
    }

    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("TRACKS", "*", where);
    QList<Record> foundRecordsList;

    while (ret.next())
    {
        CTrackRecord record(
                            ret.value("idTrack").toInt(),
                            ret.value("idDevice").toInt(),
                            ret.value("startDate").toInt(),
                            ret.value("startLocation").toString().toStdString(),
                            ret.value("endDate").toInt(),
                            ret.value("endLocation").toString().toStdString(),
                            ret.value("distance").toInt(),
                            ret.value("manouverAssessment").toInt()
                            );


        foundRecordsList.append(record);
    }

    return foundRecordsList;
}

QList<Record> CTrackArray::SelectAllByDevice(int idDevice)
{
    std::string where = "";
    if (idDevice != -1)
    {
        where = "idDevice='" + QString::number(idDevice).toStdString() + "'";
    }

    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("TRACKS", "*", where);
    QList<Record> foundRecordsList;

    while (ret.next())
    {
        CTrackRecord record(
                            ret.value("idTrack").toInt(),
                            ret.value("idDevice").toInt(),
                            ret.value("startDate").toInt(),
                            ret.value("startLocation").toString().toStdString(),
                            ret.value("endDate").toInt(),
                            ret.value("endLocation").toString().toStdString(),
                            ret.value("distance").toInt(),
                            ret.value("manouverAssessment").toInt()
                            );


        foundRecordsList.append(record);
    }

    return foundRecordsList;
}
