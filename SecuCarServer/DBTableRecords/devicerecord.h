#ifndef DEVICERECORD_H
#define DEVICERECORD_H

#include <string>
#include "crecord.h"

class CDeviceRecord : public Record
{
public:
    CDeviceRecord(int deviceId, int userId, int serialNumber, std::string lastLocation, std::string deviceName, int firmwareVersion);

    CDeviceRecord(const CDeviceRecord& rec);

    int GetDeviceId() const;

    int GetUserId() const;

    int GetSerialNumber() const;

    std::string GetLastLocation() const;

    std::string GetDeviceName() const;

    int GetFirmwareVersion() const;

    void SetDeviceId(int id);

    void SetUserId(int id);

    void SetSerialNumber(int serialNumber);

    void SetLastLocation(std::string lastLocation);

    void SetDeviceName(std::string name);

    void SetFirmwareVersion(int version);


    void LogRecord();

    std::string Serialize();

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
