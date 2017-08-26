#include "trackrecord.h"
#include "logger.h"
#include <sstream>
#include <string>

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

CTrackRecord::CTrackRecord(const CTrackRecord &rec)
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

int CTrackRecord::GetTrackId() const
{
    return m_trackId;
}

int CTrackRecord::GetDeviceId() const
{
    return m_deviceId;
}

int CTrackRecord::GetStartTimestmap() const
{
    return m_startTimestamp;
}

std::string CTrackRecord::GetStartLocation() const
{
    return m_startLocation;
}

int CTrackRecord::GetEndTimestamp() const
{
    return m_endTimestamp;
}

std::string CTrackRecord::GetEndLocation() const
{
    return m_endLocation;
}
int CTrackRecord::GetDistance() const
{
    return m_distance;
}

int CTrackRecord::GetManeouverAssessment() const
{
    return m_maneouverAssessment;
}

void CTrackRecord::SetTrackId(int id)
{
    m_trackId = id;
}

void CTrackRecord::SetDeviceId(int id)
{
    m_deviceId = id;
}

void CTrackRecord::SetStartTimestamp(int timestamp)
{
    m_startTimestamp = timestamp;
}

void CTrackRecord::SetStartLocation(std::string location)
{
    m_startLocation = location;
}

void CTrackRecord::SetEndTimestamp(int timestamp)
{
    m_endTimestamp = timestamp;
}

void CTrackRecord::SetEndLocation(std::string endLocation)
{
    m_endLocation = endLocation;
}

void CTrackRecord::SetDistance(int distance)
{
    m_distance = distance;
}

void CTrackRecord::SetManeouverAssessment(int assessment)
{
    m_maneouverAssessment = assessment;
}

void CTrackRecord::LogRecord()
{
    LOG_INFO("trackId: %d, idDevice: %d, startDate: %d, startLocation: %s, endDate: %d, endLocation: %s, distance: %d, maneouverAssessment: %d",
             m_trackId, m_deviceId, m_startTimestamp, m_startLocation.c_str(), m_endTimestamp, m_endLocation.c_str(), m_distance, m_maneouverAssessment);
}

std::__cxx11::string CTrackRecord::Serialize()
{
    std::ostringstream ss;

    ss << "idTrack: " << m_trackId << ", " <<
          "idDevice: " << m_deviceId << ", " <<
          "startDate: " << m_startTimestamp << ", " <<
          "startLocation: " << m_startLocation << ", " <<
          "endDate: " << m_endTimestamp << ", " <<
          "endLocation: " << m_endLocation << ", " <<
          "distance: " << m_distance << ", " <<
          "maneouverAssessment: " << m_maneouverAssessment;

    return ss.str();
}
