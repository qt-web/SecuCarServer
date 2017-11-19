#include "devicerecord.h"
#include "logger.h"
#include <sstream>
#include <string>

CDeviceRecord::CDeviceRecord()
{

}

CDeviceRecord::CDeviceRecord(int deviceId, int userId, int serialNumber, std::string devicePhoneNumber, std::__cxx11::string lastLocation, std::__cxx11::string deviceName, std::string firmwareVersion)
{
    m_deviceId = deviceId;
    m_userId = userId;
    m_serialNumber = serialNumber;
    m_devPhoneNumber = devicePhoneNumber;
    m_lastLocation = lastLocation;
    m_deviceName = deviceName;
    m_firmwareVersion = firmwareVersion;

    LogRecord();
}

CDeviceRecord::CDeviceRecord(const CDeviceRecord &rec)
{
    m_deviceId = rec.GetDeviceId();
    m_userId = rec.GetUserId();
    m_serialNumber = rec.GetSerialNumber();
    m_devPhoneNumber = rec.GetDevicePhoneNum();
    m_lastLocation = rec.GetLastLocation();
    m_deviceName = rec.GetDeviceName();
    m_firmwareVersion = rec.GetFirmwareVersion();
}

int CDeviceRecord::GetDeviceId() const
{
    return m_deviceId;
}

int CDeviceRecord::GetUserId() const
{
    return m_userId;
}

int CDeviceRecord::GetSerialNumber() const
{
    return m_serialNumber;
}

std::string CDeviceRecord::GetDevicePhoneNum() const
{
    return m_devPhoneNumber;
}

std::string CDeviceRecord::GetLastLocation() const
{
    return m_lastLocation;
}

std::string CDeviceRecord::GetDeviceName() const
{
    return m_deviceName;
}

std::string CDeviceRecord::GetFirmwareVersion() const
{
    return m_firmwareVersion;
}

void CDeviceRecord::SetDeviceId(int id)
{
    m_deviceId = id;
}

void CDeviceRecord::SetUserId(int id)
{
    m_userId = id;
}

void CDeviceRecord::SetSerialNumber(int serialNumber)
{
    m_serialNumber = serialNumber;
}

void CDeviceRecord::SetLastLocation(std::string lastLocation)
{
    m_lastLocation = lastLocation;
}

void CDeviceRecord::SetDeviceName(std::string name)
{
    m_deviceName = name;
}

void CDeviceRecord::SetFirmwareVersion(std::string version)
{
    m_firmwareVersion = version;
}

void CDeviceRecord::LogRecord()
{
    LOG_INFO("idDevice: %d, idUser: %d, serialNumber: %d, phoneNumber: %s, lastLocation: %s, deviceName: %s, firmwareVersion %s",
                m_deviceId, m_userId, m_serialNumber, m_devPhoneNumber.c_str(), m_lastLocation.c_str(), m_deviceName.c_str(), m_firmwareVersion.c_str());
}

std::string CDeviceRecord::Serialize()
{
    std::ostringstream ss;

    ss << "idDevice:" << m_deviceId << "," <<
          "idUser:" << m_userId << "," <<
          "serialNumber:" << m_serialNumber << "," <<
          "phoneNumber:" << m_devPhoneNumber << "," <<
          "lastLocation:" << m_lastLocation << "," <<
          "deviceName:" << m_deviceName << "," <<
          "firmwareVersion:" << m_firmwareVersion;

    return ss.str();
}
