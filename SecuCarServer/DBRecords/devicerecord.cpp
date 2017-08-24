#include "devicerecord.h"
#include "logger.h"

CDeviceRecord::CDeviceRecord()
{

}

CDeviceRecord::CDeviceRecord(int deviceId, int userId, int serialNumber, std::__cxx11::string lastLocation, std::__cxx11::string deviceName, int firmwareVersion)
{
    m_deviceId = deviceId;
    m_userId = userId;
    m_serialNumber = serialNumber;
    m_lastLocation = lastLocation;
    m_deviceName = deviceName;
    m_firmwareVersion = firmwareVersion;

    LogRecord();
}

int CDeviceRecord::GetDeviceId()
{
    return m_deviceId;
}

int CDeviceRecord::GetUserId()
{
    return m_userId;
}

int CDeviceRecord::GetSerialNumber()
{
    return m_serialNumber;
}

std::string CDeviceRecord::GetLastLocation()
{
    return m_lastLocation;
}

std::string CDeviceRecord::GetDeviceName()
{
    return m_deviceName;
}

int CDeviceRecord::GetFirmwareVersion()
{
    return m_firmwareVersion;
}

void CDeviceRecord::LogRecord()
{
    LOG_INFO("Record: deviceId: %d, userId: %d, serialnumber: %d, last location: %s, device name: %s, firmware version %d",
                m_deviceId, m_userId, m_serialNumber, m_lastLocation.c_str(), m_deviceName.c_str(), m_firmwareVersion);
}
