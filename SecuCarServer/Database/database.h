#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include "databasedriver.h"
#include "userarray.h"
#include "devicearray.h"
#include "trackarray.h"
#include "samplearray.h"
#include "devicerecord.h"
#include "trackrecord.h"
#include "samplerecord.h"


class CDatabase
{
public:
    static CDatabase* GetInstance();

    int Login(std::string username, std::string passwordHash);

    int RegisterUser(
                        std::string username,
                        std::string name,
                        std::string surname,
                        std::string email,
                        int telephoneNumber,
                        std::string city,
                        std::string street,
                        int homeNumber,
                        int flatNumber,
                        std::string postalCode,
                        std::string passwordHash
                    );

    CUserRecord GetUserData(int idUser);

    int ChangeUserData(
                        int idUser,
                        std::string username,
                        std::string name,
                        std::string surname,
                        std::string email,
                        int telephoneNumber,
                        std::string city,
                        std::string street,
                        int homeNumber,
                        int flatNumber,
                        std::string postalCode,
                        std::string passwordHash
                        );

    int ChangePassword(
                        int idUser,
                        std::string oldPasswordHash,
                        std::string newPasswordHash
                      );

    int AddDevice(
                    int idUser,
                    int serialNumber,
                    std::string currentLocation,
                    std::string deviceName,
                    int firmwareVersion
                 );

    int ChangeDeviceName(
                            int idDevice,
                            std::string newName
                        );

    CDeviceRecord GetDeviceInfo(int idDevice);

    int DeleteDevice(int idDevice);

    int AddTrack(
                int idDevice,
                int startTimestamp,
                std::string startLocation,
                int endDate = 0,
                std::string endLocation = "",
                int distance = 0,
                int manouverAssessment = 0
                );

    CTrackRecord GetTrackInfo(int idTrack);

    QList<CSampleRecord> GetTrackDetails(int idTrack);

    int DeleteTrack(int idTrack);

    QList<CDeviceRecord>    GetRegisteredDevicesList(int idUser);

    QList<CTrackRecord>     GetTracksList(int idDevice);


private:
    CDatabase();

    CDatabaseDriver* m_pDatabaseDriver;

    CUserArray* m_pUserArray;

    CDeviceArray* m_pDeviceArray;

    CTrackArray* m_pTrackArray;

    CSampleArray* m_pSampleArray;

};

#endif // DATABASE_H
