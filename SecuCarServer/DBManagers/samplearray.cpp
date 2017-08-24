#include "samplearray.h"
#include "databasedriver.h"
#include "samplerecord.h"
#include "logger.h"
#include <QSqlQuery>
#include <QList>

CSampleArray::CSampleArray()
{

}

CSampleArray* CSampleArray::GetInstance()
{
    static CSampleArray s_instance;
    return &s_instance;
}

bool CSampleArray::Insert(Record& record)
{
    CSampleRecord* rec = dynamic_cast<CSampleRecord*>(&record);

    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. Should be CSampleRecord");
        return false;
    }

    QString qQuery =    "'" + QString::number(rec->GetSampleId()) + "', " +
                        "'" + QString::number(rec->GetTrackId()) + "', " +
                        "'" + QString::number(rec->GetTimestamp()) + "', " +
                        "'" + QString::fromStdString(rec->GetCoordinates()) + "', " +
                        "'" + QString::number(rec->GetSpeed()) + "', " +
                        "'" + QString::number(rec->GetAcceleration()) + "', " +
                        "'" + QString::number(rec->GetAzimuth()) + "'";


    return CDatabaseDriver::GetInstance()->Insert("SAMPLES", qQuery.toStdString());
}


bool CSampleArray::Update(Record &record)
{
    CSampleRecord* rec = dynamic_cast<CSampleRecord*>(&record);
    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. should be CSampleRecord");
        return false;
    }

    QString fieldsToUpdate =    "idSample='" + QString::number(rec->GetSampleId()) + "', " +
                                "idTrack='" + QString::number(rec->GetTrackId()) + "', " +
                                "timestamp='" + QString::number(rec->GetTimestamp()) + "', " +
                                "coordinates='" + QString::fromStdString(rec->GetCoordinates()) + "', " +
                                "speed='" + QString::number(rec->GetSpeed()) + "', " +
                                "acceleration='" + QString::number(rec->GetAcceleration()) + "'" +
                                "azimuth='" + QString::number(rec->GetAzimuth()) + "'" ;

    return CDatabaseDriver::GetInstance()->Update("SAMPLES", fieldsToUpdate.toStdString(), QString("idSample='" + QString::number(rec->GetSampleId()) + "'").toStdString());
}

bool CSampleArray::Delete(int recordId)
{
    std::string where = "idSample='" + QString::number(recordId).toStdString() + "'";
    return CDatabaseDriver::GetInstance()->Delete("SAMPLES", where);
}

QList<Record> CSampleArray::Select(int recordId)
{
    std::string where = "";
    if (recordId != -1)
    {
        where = "idSample='" + QString::number(recordId).toStdString() + "'";
    }

    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("SAMPLES", "*", where);
    QList<Record> foundRecordsList;

    while (ret.next())
    {
        CSampleRecord record(
                            ret.value("idSample").toInt(),
                            ret.value("idTrack").toInt(),
                            ret.value("timestamp").toInt(),
                            ret.value("coordinates").toString().toStdString(),
                            ret.value("speed").toInt(),
                            ret.value("acceleration").toInt(),
                            ret.value("azimuth").toInt()
                            );


        foundRecordsList.append(record);
    }

    return foundRecordsList;
}