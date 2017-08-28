#ifndef DEVICERECORD_H
#define DEVICERECORD_H

#include <string>
#include "crecord.h"

/**
 * @brief The CDeviceRecord class - This class represents the record from the Devices Table
 */
class CDeviceRecord : public Record
{
public:
    /**
     * @brief CDeviceRecord
     * @param deviceId
     * @param userId
     * @param serialNumber
     * @param lastLocation
     * @param deviceName
     * @param firmwareVersion
     */
    CDeviceRecord(int deviceId, int userId, int serialNumber, std::string lastLocation, std::string deviceName, int firmwareVersion);

    /**
     * @brief CDeviceRecord
     * @param rec
     */
    CDeviceRecord(const CDeviceRecord& rec);

    /**
     * @brief GetDeviceId
     * @return
     */
    int GetDeviceId() const;

    /**
     * @brief GetUserId
     * @return
     */
    int GetUserId() const;

    /**
     * @brief GetSerialNumber
     * @return
     */
    int GetSerialNumber() const;

    /**
     * @brief GetLastLocation
     * @return
     */
    std::string GetLastLocation() const;

    /**
     * @brief GetDeviceName
     * @return
     */
    std::string GetDeviceName() const;

    /**
     * @brief GetFirmwareVersion
     * @return
     */
    int GetFirmwareVersion() const;

    /**
     * @brief SetDeviceId
     * @param id
     */
    void SetDeviceId(int id);

    /**
     * @brief SetUserId
     * @param id
     */
    void SetUserId(int id);

    /**
     * @brief SetSerialNumber
     * @param serialNumber
     */
    void SetSerialNumber(int serialNumber);

    /**
     * @brief SetLastLocation
     * @param lastLocation
     */
    void SetLastLocation(std::string lastLocation);

    /**
     * @brief SetDeviceName
     * @param name
     */
    void SetDeviceName(std::string name);

    /**
     * @brief SetFirmwareVersion
     * @param version
     */
    void SetFirmwareVersion(int version);

    /**
     * @brief LogRecord - Allows to print the record in the logs
     */
    void LogRecord();

    /**
     * @brief Serialize - Allows to serialize the record. It is necessary to put the record in the JSON file
     * @return
     */
    std::string Serialize();

private:
    /**
     * @brief CDeviceRecord
     */
    CDeviceRecord();
    
    /**
     * @brief m_deviceId - idDevice database field
     */
    int m_deviceId;

    /**
     * @brief m_userId - idUser database field. Describes the user who is owner of the device
     */
    int m_userId;

    /**
     * @brief m_serialNumber - serialNumber database field.
     */
    int m_serialNumber;

    /**
     * @brief m_lastLocation - lastLocation database field - describes the last received location of the device
     */
    std::string m_lastLocation;

    /**
     * @brief m_deviceName - deviceName database field. Name of the device given by the owner
     */
    std::string m_deviceName;

    /**
     * @brief m_firmwareVersion - firmwareVersion database field. Firmware version of the device's software
     */
    int m_firmwareVersion;
};

#endif // DEVICERECORD_H
