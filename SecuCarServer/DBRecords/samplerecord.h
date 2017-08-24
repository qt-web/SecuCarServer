#ifndef SAMPLERECORD_H
#define SAMPLERECORD_H

#include <string>
#include "crecord.h"

class CSampleRecord : public Record
{
public:
    CSampleRecord(int sampleId, int trackId, int timestamp, std::string coordinates, int speed, int acceleration, int azimuth);

    CSampleRecord(CSampleRecord& rec);

    int GetSampleId();

    int GetTrackId();

    int GetTimestamp();

    std::string GetCoordinates();

    int GetSpeed();

    int GetAcceleration();

    int GetAzimuth();

    void LogRecord();

private:
    CSampleRecord();

    int m_sampleId;

    int m_trackId;

    int m_timestamp;

    std::string m_coordinates;

    int m_speed;

    int m_acceleration;

    int m_azimuth;
};

#endif // SAMPLERECORD_H
