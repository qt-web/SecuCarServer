#include "samplearray.h"
#include "databasedriver.h"
#include "samplerecord.h"
#include "logger.h"
#include <QSqlQuery>
#include <QList>

CSampleArray::CSampleArray()
{
    m_columnNames = "idTrack, timestamp, coordinates, speed, acceleration, azimuth, numOfSats, hdop, manouverAssessment, fixStatus";
}

CSampleArray* CSampleArray::GetInstance()
{
    static CSampleArray s_instance;
    return &s_instance;
}

int CSampleArray::Insert(Record& record)
{
    CSampleRecord* rec = dynamic_cast<CSampleRecord*>(&record);

    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. Should be CSampleRecord");
        return false;
    }

    QString fields = "idTrack, timestamp, coordinates, speed, acceleration, azimuth, numOfSats, hdop, manouverAssessment, fixStatus";
    QString qQuery =    //"'" + QString::number(rec->GetSampleId()) + "', " +
                        "'" + QString::number(rec->GetTrackId()) + "', " +
                        "'" + QString::number(rec->GetTimestamp()) + "', " +
                        "'" + QString::fromStdString(rec->GetCoordinates()) + "', " +
                        "'" + QString::number(rec->GetSpeed()) + "', " +
                        "'" + QString::number(rec->GetAcceleration()) + "', " +
                        "'" + QString::number(rec->GetAzimuth()) + "', " +
                        "'" + QString::number(rec->GetNumOfSattellites()) + "', " +
                        "'" + QString::number(rec->GetHdop())  + "', " +
                        "'" + QString::number(rec->GetManouverAssessment())  + "', " +
                        "'" + QString::number(rec->GetFixStatus()) + "'";


    return CDatabaseDriver::GetInstance()->Insert("SAMPLES", m_columnNames, qQuery.toStdString());
}


bool CSampleArray::Update(Record &record)
{
    CSampleRecord* rec = dynamic_cast<CSampleRecord*>(&record);
    if (rec == nullptr)
    {
        LOG_ERROR("Wrong record type given. should be CSampleRecord");
        return false;
    }

    QString fieldsToUpdate =    //"idSample='" + QString::number(rec->GetSampleId()) + "', " +
                                "idTrack='" + QString::number(rec->GetTrackId()) + "', " +
                                "timestamp='" + QString::number(rec->GetTimestamp()) + "', " +
                                "coordinates='" + QString::fromStdString(rec->GetCoordinates()) + "', " +
                                "speed='" + QString::number(rec->GetSpeed()) + "', " +
                                "acceleration='" + QString::number(rec->GetAcceleration()) + "', " +
                                "azimuth='" + QString::number(rec->GetAzimuth()) + "', " +
                                "numOfSats='" + QString::number(rec->GetNumOfSattellites()) + "', " +
                                "hdop='" + QString::number(rec->GetHdop()) + "', " +
                                "manouverAssessment='" + QString::number(rec->GetManouverAssessment())  + "', " +
                                "fixStatus='" + QString::number(rec->GetFixStatus()) + "'";

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
                            ret.value("azimuth").toInt(),
                            ret.value("numOfSats").toInt(),
                            ret.value("hdop").toInt(),
                            ret.value("manouverAssessment").toInt(),
                            ret.value("fixStatus").toInt()
                            );


        foundRecordsList.append(record);
    }

    return foundRecordsList;
}

QList<CSampleRecord> CSampleArray::SelectAllByTrack(int idTrack)
{
    std::string where = "";
    if (idTrack != -1)
    {
        where = "idTrack='" + QString::number(idTrack).toStdString() + "'";
    }

    QSqlQuery ret = CDatabaseDriver::GetInstance()->Select("SAMPLES", "*", where);
    QList<CSampleRecord> foundRecordsList;

    while (ret.next())
    {
        CSampleRecord record(
                            ret.value("idSample").toInt(),
                            ret.value("idTrack").toInt(),
                            ret.value("timestamp").toInt(),
                            ret.value("coordinates").toString().toStdString(),
                            ret.value("speed").toInt(),
                            ret.value("acceleration").toInt(),
                            ret.value("azimuth").toInt(),
                            ret.value("numOfSats").toInt(),
                            ret.value("hdop").toInt(),
                            ret.value("manouverAssessment").toInt(),
                            ret.value("fixStatus").toInt()
                            );


        foundRecordsList.append(record);
    }

    return foundRecordsList;
}
