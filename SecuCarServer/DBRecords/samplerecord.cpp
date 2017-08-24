#include "samplerecord.h"
#include "logger.h"

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

CSampleRecord::CSampleRecord(CSampleRecord &rec)
{
    m_sampleId = rec.GetSampleId();
    m_trackId = rec.GetTrackId();
    m_timestamp = rec.GetTimestamp();
    m_coordinates = rec.GetCoordinates();
    m_speed = rec.GetSpeed();
    m_acceleration = rec.GetAcceleration();
    m_azimuth = rec.GetAzimuth();
}

int CSampleRecord::GetSampleId()
{
    return m_sampleId;
}

int CSampleRecord::GetTrackId()
{
    return m_trackId;
}

int CSampleRecord::GetTimestamp()
{
    return m_timestamp;
}

std::string CSampleRecord::GetCoordinates()
{
    return m_coordinates;
}

int CSampleRecord::GetSpeed()
{
    return m_speed;
}

int CSampleRecord::GetAcceleration()
{
    return m_acceleration;
}

int CSampleRecord::GetAzimuth()
{
    return m_azimuth;
}

void CSampleRecord::LogRecord()
{
    LOG_INFO("Record: sampleId: %d, trackId: %d, timestamp: %d, coordinates: %s, speed: %d(%f), acceleration: %d(%d), azimuth: %d",
             m_sampleId, m_trackId, m_timestamp, m_coordinates.c_str(), m_speed, (float)m_speed/100, m_acceleration, (float)m_acceleration/100, m_azimuth);
}
