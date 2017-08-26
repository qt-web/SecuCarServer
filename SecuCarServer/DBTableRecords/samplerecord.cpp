#include "samplerecord.h"
#include "logger.h"
#include <sstream>
#include <string>

CSampleRecord::CSampleRecord()
{

}

CSampleRecord::CSampleRecord(int sampleId, int trackId, int timestamp, std::__cxx11::string coordinates, int speed, int acceleration, int azimuth)
{
    m_sampleId = sampleId;
    m_trackId = trackId;
    m_timestamp = timestamp;
    m_coordinates = coordinates;
    m_speed = speed;
    m_acceleration = acceleration;
    m_azimuth = azimuth;

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
    LOG_INFO("idSample: %d, idTrack: %d, timestamp: %d, coordinates: %s, speed: %d(%f), acceleration: %d(%d), azimuth: %d",
             m_sampleId, m_trackId, m_timestamp, m_coordinates.c_str(), m_speed, (float)m_speed/100, m_acceleration, (float)m_acceleration/100, m_azimuth);
}

std::__cxx11::string CSampleRecord::Serialize()
{
    std::ostringstream ss;

    ss << "idSample: " << m_sampleId << ", " <<
          "idTrack: " << m_trackId << ", " <<
          "timestamp: " << m_timestamp << ", " <<
          "coordinates: " << m_coordinates << ", " <<
          "speed: " << m_speed << ", " <<
          "acceleration: " << m_acceleration << ", " <<
          "azimuth: " << m_azimuth;

    return ss.str();
}
