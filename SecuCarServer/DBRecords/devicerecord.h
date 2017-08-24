#ifndef DEVICERECORD_H
#define DEVICERECORD_H

#include <string>
#include "crecord.h"

class CDeviceRecord : public Record
{
public:
    CDeviceRecord(int deviceId, int userId, int serialNumber, std::string lastLocation, std::string deviceName, int firmwareVersion);

    CDeviceRecord(CDeviceRecord& rec);

    int GetDeviceId();

    int GetUserId();

    int GetSerialNumber();

    std::string GetLastLocation();

    std::string GetDeviceName();

    int GetFirmwareVersion();

    void LogRecord();

private:
    CDeviceRecord();
    
    int m_deviceId;

    int m_userId;

    int m_serialNumber;

    std::string m_lastLocation;

    std::string m_deviceName;

    int m_firmwareVersion;

};

#endif // DEVICERECORD_H
