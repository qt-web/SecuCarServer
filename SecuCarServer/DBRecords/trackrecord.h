#ifndef TRACKRECORD_H
#define TRACKRECORD_H

#include <string>
#include "crecord.h"

class CTrackRecord : public Record
{
public:

    CTrackRecord(int trackId, int deviceId, int startTimestmap, std::string startLocation, int endTimestamp, std::string endLocation, int distance, int maneouverAssessment);

    CTrackRecord(CTrackRecord& rec);

    int GetTrackId();

    int GetDeviceId();

    int GetStartTimestmap();

    std::string GetStartLocation();

    int GetEndTimestamp();

    std::string GetEndLocation();

    int GetDistance();

    int GetManeouverAssessment();

    LogRecord();

private:

    CTrackRecord();

    int m_trackId;

    int m_deviceId;

    int m_startTimestamp;

    std::string m_startLocation;

    int m_endTimestamp;

    std::string m_endLocation;

    int m_distance;

    int m_maneouverAssessment;
};

#endif // TRACKRECORD_H
