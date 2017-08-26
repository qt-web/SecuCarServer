#ifndef TRACKRECORD_H
#define TRACKRECORD_H

#include <string>
#include "crecord.h"

class CTrackRecord : public Record
{
public:

    CTrackRecord(int trackId, int deviceId, int startTimestmap, std::string startLocation, int endTimestamp, std::string endLocation, int distance, int maneouverAssessment);

    CTrackRecord(const CTrackRecord& rec);

    int GetTrackId() const;

    int GetDeviceId() const;

    int GetStartTimestmap() const;

    std::string GetStartLocation() const;

    int GetEndTimestamp() const;

    std::string GetEndLocation() const;

    int GetDistance() const;

    int GetManeouverAssessment() const;

    void SetTrackId(int id);

    void SetDeviceId(int id);

    void SetStartTimestamp(int timestamp);

    void SetStartLocation(std::string location);

    void SetEndTimestamp(int timestamp);

    void SetEndLocation(std::string endLocation);

    void SetDistance(int distance);

    void SetManeouverAssessment(int assessment);

    void LogRecord();

    const char* Serialize();
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
