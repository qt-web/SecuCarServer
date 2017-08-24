#ifndef SAMPLERECORD_H
#define SAMPLERECORD_H

#include <string>
#include "crecord.h"

class CSampleRecord : public Record
{
public:
    CSampleRecord(int sampleId, int trackId, int timestamp, std::string coordinates, int speed, int acceleration, int azimuth);

    CSampleRecord(const CSampleRecord& rec);

    int GetSampleId() const;

    int GetTrackId() const;

    int GetTimestamp() const;

    std::string GetCoordinates() const;

    int GetSpeed() const;

    int GetAcceleration() const;

    int GetAzimuth() const;

    void SetSampleId(int id);

    void SetTrackId(int id);

    void SetTimestamp(int timestamp);

    void SetCoordinates(std::string coordinates);

    void SetSpeed(int speed);

    void SetAcceleration(int acceleration);

    void SetAzimuth(int azimuth);

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
