#include "trackrecord.h"
#include "logger.h"

CTrackRecord::CTrackRecord()
{

}

CTrackRecord::CTrackRecord(int trackId, int deviceId, int startTimestmap, std::__cxx11::string startLocation, int endTimestamp, std::__cxx11::string endLocation, int distance, int maneouverAssessment)
{
    m_trackId = trackId;
    m_deviceId = deviceId;
    m_startTimestamp = startTimestmap;
    m_startLocation = startLocation;
    m_endTimestamp = endTimestamp;
    m_endLocation = endLocation;
    m_distance = distance;
    m_maneouverAssessment = maneouverAssessment;

    LogRecord();
}

CTrackRecord::CTrackRecord(CTrackRecord &rec)
{
    m_trackId = rec.GetTrackId();
    m_deviceId = rec.GetDeviceId();
    m_startTimestamp = rec.GetStartTimestmap();
    m_startLocation = rec.GetStartLocation();
    m_endTimestamp = rec.GetEndTimestamp();
    m_endLocation = rec.GetEndLocation();
    m_distance = rec.GetDistance();
    m_maneouverAssessment = rec.GetManeouverAssessment();
}

int CTrackRecord::GetTrackId()
{
    return m_trackId;
}

int CTrackRecord::GetDeviceId()
{
    return m_deviceId;
}

int CTrackRecord::GetStartTimestmap()
{
    return m_startTimestamp;
}

std::string CTrackRecord::GetStartLocation()
{
    return m_startLocation;
}

int CTrackRecord::GetEndTimestamp()
{
    return m_endTimestamp;
}

std::string CTrackRecord::GetEndLocation()
{
    return m_endLocation;
}
int CTrackRecord::GetDistance()
{
    return m_distance;
}

int CTrackRecord::GetManeouverAssessment()
{
    return m_maneouverAssessment;
}

void CTrackRecord::LogRecord()
{
    LOG_INFO("Record: trackId: %d, deviceId: %d, startDate: %d, startLocation: %s, endDate: %d, endLocation: %s, distance: %d, maneouver assessment: %d",
             m_trackId, m_deviceId, m_startTimestamp, m_startLocation.c_str(), m_endTimestamp, m_endLocation.c_str(), m_distance, m_maneouverAssessment);
}

