#include "samplerecord.h"
#include "logger.h"
#include <sstream>
#include <string>

CSampleRecord::CSampleRecord()
{

}

CSampleRecord::CSampleRecord(int sampleId, int trackId, int timestamp, std::__cxx11::string coordinates, int speed, int acceleration, int azimuth, int numOfSattellites, int hdop, int manouverAssessment)
{
    m_sampleId = sampleId;
    m_trackId = trackId;
    m_timestamp = timestamp;
    m_coordinates = coordinates;
    m_speed = speed;
    m_acceleration = acceleration;
    m_azimuth = azimuth;
    m_numOfSattelites = numOfSattellites;
    m_hdop = hdop;
    m_manouverAssessment = manouverAssessment;

    LogRecord();
}

CSampleRecord::CSampleRecord(const CSampleRecord &rec)
{
    m_sampleId = rec.GetSampleId();
    m_trackId = rec.GetTrackId();
    m_timestamp = rec.GetTimestamp();
    m_coordinates = rec.GetCoordinates();
    m_speed = rec.GetSpeed();
    m_acceleration = rec.GetAcceleration();
    m_azimuth = rec.GetAzimuth();
    m_numOfSattelites = rec.GetNumOfSattellites();
    m_hdop = rec.GetHdop();
    m_manouverAssessment = rec.GetManouverAssessment();
}

int CSampleRecord::GetSampleId() const
{
    return m_sampleId;
}

int CSampleRecord::GetTrackId() const
{
    return m_trackId;
}

int CSampleRecord::GetTimestamp() const
{
    return m_timestamp;
}

std::string CSampleRecord::GetCoordinates() const
{
    return m_coordinates;
}

int CSampleRecord::GetSpeed() const
{
    return m_speed;
}

int CSampleRecord::GetAcceleration() const
{
    return m_acceleration;
}

int CSampleRecord::GetAzimuth() const
{
    return m_azimuth;
}

int CSampleRecord::GetNumOfSattellites() const
{
    return m_numOfSattelites;
}

int CSampleRecord::GetHdop() const
{
    return m_hdop;
}

int CSampleRecord::GetManouverAssessment() const
{
    return m_manouverAssessment;
}

void CSampleRecord::SetSampleId(int id)
{
    m_sampleId = id;
}

void CSampleRecord::SetTrackId(int id)
{
    m_trackId = id;
}

void CSampleRecord::SetTimestamp(int timestamp)
{
    m_timestamp = timestamp;
}

void CSampleRecord::SetCoordinates(std::string coordinates)
{
    m_coordinates = coordinates;
}

void CSampleRecord::SetSpeed(int speed)
{
    m_speed = speed;
}

void CSampleRecord::SetAcceleration(int acceleration)
{
    m_acceleration = acceleration;
}

void CSampleRecord::SetAzimuth(int azimuth)
{
    m_azimuth = azimuth;
}

void CSampleRecord::LogRecord()
{
    LOG_INFO("idSample: %d, idTrack: %d, timestamp: %d, coordinates: %s, speed: %d(%f), acceleration: %d(%f), azimuth: %d, numOfSattelites: %d, hdop: %f, manouverAssessment: %d",
             m_sampleId, m_trackId, m_timestamp, m_coordinates.c_str(), m_speed, (float)m_speed/100.00, m_acceleration, (float)m_acceleration/100.00, m_azimuth, m_numOfSattelites, m_hdop/100.0, m_manouverAssessment);
}

std::__cxx11::string CSampleRecord::Serialize()
{
    std::ostringstream ss;

    int pos = m_coordinates.find(',');
    if (pos != std::string::npos)
    {
        m_coordinates[pos] = ';';
    }

    ss << "idSample:" << m_sampleId << "," <<
          "idTrack:" << m_trackId << "," <<
          "timestamp:" << m_timestamp << "," <<
          "coordinates:" << m_coordinates << "," <<
          "speed:" << m_speed << "," <<
          "acceleration:" << m_acceleration << "," <<
          "azimuth:" << m_azimuth << "," <<
          "numOfSattellites: " << m_numOfSattelites << "," <<
          "hdop: " << m_hdop << "," <<
          "manouverAssessment: " << m_manouverAssessment;
    return ss.str();
}
