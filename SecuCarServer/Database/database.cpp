#include "database.h"
#include "databasedriver.h"
#include "userarray.h"
#include "devicearray.h"
#include "trackarray.h"
#include "samplearray.h"
#include "userrecord.h"
#include "devicerecord.h"
#include "trackrecord.h"
#include "samplerecord.h"
#include "logger.h"
#include "databasedriver.h"

class CDatabaseDriver;

CDatabase::CDatabase()
{
    m_pDatabaseDriver = CDatabaseDriver::GetInstance();
    m_pUserArray = CUserArray::GetInstance();
    m_pDeviceArray = CDeviceArray::GetInstance();
    m_pTrackArray = CTrackArray::GetInstance();
    m_pSampleArray = CSampleArray::GetInstance();
}

CDatabase* CDatabase::GetInstance()
{
    static CDatabase s_instance;
    return &s_instance;
}

int CDatabase::Login(std::__cxx11::string username, std::__cxx11::string passwordHash)
{
    QList<CUserRecord> rec = m_pUserArray->Select(username);

    if (rec.empty())
    {
        LOG_ERROR("No user found with username; %s", username.c_str());
        return -1;
    }

    if (passwordHash.compare(rec[0].GetPasswordHash()) == 0)
        return rec[0].GetUserId();

    return -1;
}

int CDatabase::RegisterUser(std::__cxx11::string username,
                            std::__cxx11::string name,
                            std::__cxx11::string surname,
                            std::__cxx11::string email,
                            int telephoneNumber,
                            std::__cxx11::string city,
                            std::__cxx11::string street,
                            int homeNumber,
                            int flatNumber,
                            std::__cxx11::string postalCode,
                            std::__cxx11::string passwordHash)
{
    CUserRecord record(0, username, name, surname, email, telephoneNumber, city, street, homeNumber, flatNumber, postalCode, passwordHash);

    QList<CUserRecord> registeredUsersList = m_pUserArray->Select(username);

    if (!registeredUsersList.empty())
    {
        LOG_DBG("User with provided username already exists");
        return -1;
    }

    int insertedUserId = m_pUserArray->Insert(record);

    if (insertedUserId == -1)
    {
        LOG_ERROR("Could not register username: %s", username.c_str());
        return -1;
    }

    return insertedUserId;
}

CUserRecord CDatabase::GetUserData(int idUser)
{
    QList<CUserRecord> recList = m_pUserArray->Select(idUser);
    if (recList.empty())
    {
        LOG_ERROR("No user found with idUser: %d", idUser);
        return CUserRecord(-1, "", "", "", "", -1, "", "", -1, -1, "", "");
    }

    return recList[0];
}

int CDatabase::ChangeUserData(int idUser, std::__cxx11::string username, std::__cxx11::string name, std::__cxx11::string surname, std::__cxx11::string email, int telephoneNumber, std::__cxx11::string city, std::__cxx11::string street, int homeNumber, int flatNumber, std::__cxx11::string postalCode, std::__cxx11::string passwordHash)
{
    CUserRecord record(idUser,
                       username,
                       name,
                       surname,
                       email,
                       telephoneNumber,
                       city,
                       street,
                       homeNumber,
                       flatNumber,
                       postalCode,
                       passwordHash);

    bool ret = m_pUserArray->Update(record);

    if (ret)
        return 1;

    return -1;
}

int CDatabase::ChangePassword(int idUser, std::__cxx11::string oldPasswordHash, std::__cxx11::string newPasswordHash)
{
    if (oldPasswordHash.compare(newPasswordHash) == 0)
    {
        LOG_ERROR("Old password cannot be the same as the new one. Returning...");
        return -1;
    }

    QList<CUserRecord> _rec = m_pUserArray->Select(idUser);
    if (_rec.empty())
    {
        LOG_ERROR("No user found with idUser; %d", idUser);
        return -1;
    }

    CUserRecord* rec = dynamic_cast<CUserRecord*>(&(_rec[0]));

    if (!(rec->GetPasswordHash().compare(oldPasswordHash) == 0))
    {
        LOG_ERROR("Old password mismatch. Returning...");
        return -1;
    }

    rec->SetPasswordHash(newPasswordHash);

    if (m_pUserArray->Update(*rec))
    {
        return 1;
    }

    return -1;
}

int CDatabase::DeleteUser(int idUser)
{
    QList<CDeviceRecord>devicesList = GetRegisteredDevicesList(idUser);
    {
        for (int i=0; i<devicesList.size(); ++i)
        {
            int idDevice = devicesList[i].GetDeviceId();
            int ret = DeleteDevice(idDevice);
            if (ret < 0)
            {
                LOG_ERROR("Could not delete idDevice: %d belonging to idUser: %d", idDevice, idUser);
            }
            else
            {
                LOG_DBG("Deleted idDevice: %d belonging to idUser: %d", idDevice, idUser);
            }
        }
    }

    bool ret = CUserArray::GetInstance()->Delete(idUser);

    if (!ret)
    {
        LOG_ERROR("Could not delete idUser: %d", idUser);
        return 0;
    }

    LOG_DBG("idUser: %d deleted successfully", idUser);
    return 1;
}

int CDatabase::AddDevice(int idUser, int serialNumber, std::string devPhoneNum, std::string currentLocation, std::__cxx11::string deviceName, std::string firmwareVersion)
{
    CDeviceRecord record(0, idUser, serialNumber, devPhoneNum, currentLocation, deviceName, firmwareVersion);
    int insertedDevId = CDeviceArray::GetInstance()->Insert(record);

    if (insertedDevId == -1)
    {
        LOG_ERROR("Could not add device into database");
        record.LogRecord();
        return -1;
    }

    LOG_DBG("Successfuly added device");
    return insertedDevId;
}

QList<CDeviceRecord> CDatabase::GetRegisteredDevicesList(int idUser)
{
    LOG_DBG("Get the devices list owned by idUser: %d", idUser);
    return CDeviceArray::GetInstance()->SelectAllByUser(idUser);
}

int CDatabase::ChangeDeviceName(int idDevice, std::__cxx11::string newName)
{
    QList<CDeviceRecord> recordList = CDeviceArray::GetInstance()->Select(idDevice);

    if (recordList.empty())
    {
        LOG_ERROR("Could not find idDevice: %d", idDevice);
        return 0;
    }

    CDeviceRecord& record = recordList[0];
    record.SetDeviceName(newName);

    bool ret = CDeviceArray::GetInstance()->Update(record);

    if (!ret)
    {
        LOG_ERROR("Could not change idDevice: %d name", idDevice);
        return 0;
    }

    LOG_DBG("idDevice: %d name has been changed to: %s", idDevice, newName.c_str());
    return 1;
}

int CDatabase::UpdateDeviceLocation(int idDevice, std::__cxx11::string newLocation)
{
    QList<CDeviceRecord> recordList = CDeviceArray::GetInstance()->Select(idDevice);

    if (recordList.empty())
    {
        LOG_ERROR("idDevice: %d not found", idDevice);
        return false;
    }
    CDeviceRecord record = recordList[0];
    if (record.GetDeviceId() == -1)
    {
        LOG_ERROR("Could not find the device");
        return 0;
    }


    record.SetLastLocation(newLocation);

    bool ret = CDeviceArray::GetInstance()->Update(record);

    if (!ret)
    {
        LOG_ERROR("Could not update device's: %d location", idDevice);
        return 0;
    }

    LOG_DBG("idDevice: %d location updated successfully", idDevice);
    return 1;
}

CDeviceRecord CDatabase::GetDeviceInfo(int idDevice)
{
    QList<CDeviceRecord> recordList = CDeviceArray::GetInstance()->Select(idDevice);
    if (recordList.empty())
    {
        LOG_ERROR("Could not find requested device");
        return CDeviceRecord(-1, -1, -1, "", "", "", "");
    }

    CDeviceRecord rec = static_cast<CDeviceRecord&>(recordList[0]);
    return rec;
}

int CDatabase::DeleteDevice(int idDevice)
{
    //  Delete tracks belonging to the device which is being deleted
    QList<CTrackRecord>trackList = GetTracksList(idDevice);
    for (int i=0; i<trackList.size(); ++i)
    {
        int idTrack = static_cast<CTrackRecord&>(trackList[i]).GetTrackId();
        int ret = DeleteTrack(idTrack);
        if (ret < 0)
        {
            LOG_ERROR("Could not delete idTrack: %d belonging to idDevice: %d", idTrack, idDevice);
        }
        else
        {
            LOG_DBG("Deleted idTrack: %d belonging to idDevice: %d", idTrack, idDevice);
        }
    }

    bool ret = CDeviceArray::GetInstance()->Delete(idDevice);

    if (!ret)
    {
        LOG_ERROR("Could not delete idDevice: %d", idDevice);
        return 0;
    }

    LOG_DBG("idDevice: %d deleted successfully", idDevice);
    return 1;
}

int CDatabase::AddTrack(
                            int idDevice,
                            int startTimestamp,
                            std::string startLocation,
                            int endDate,
                            std::string endLocation,
                            int distance,
                            int manouverAssessment
                            )
{
    CTrackRecord record(0, idDevice, startTimestamp, startLocation, endDate, endLocation, distance, manouverAssessment);

    int insertedTrackId = CTrackArray::GetInstance()->Insert(record);

    if (insertedTrackId == -1)
    {
        LOG_ERROR("Could not add the track into the database");
        return -1;
    }

    LOG_DBG("Track successfully added");
    return insertedTrackId;
}

QList<CTrackRecord> CDatabase::GetTracksList(int idDevice)
{
    LOG_DBG(" ");
    QList<CTrackRecord> trackList = CTrackArray::GetInstance()->SelectAllByDevice(idDevice);

    if (trackList.empty())
    {
        LOG_ERROR("Could not find tracks for deviceId: %d", idDevice);
    }

    return trackList;
}

CTrackRecord CDatabase::GetTrackInfo(int idTrack)
{
    LOG_DBG(" ");
    QList<CTrackRecord> trackList = CTrackArray::GetInstance()->Select(idTrack);

    if (trackList.empty())
    {
        LOG_ERROR("Could not find tracks for idTrack: %d", idTrack);
    }

    CTrackRecord record = static_cast<CTrackRecord&>(trackList[0]);
    return record;
}

QList<CSampleRecord> CDatabase::GetTrackDetails(int idTrack)
{
    LOG_DBG(" ");

    QList<CSampleRecord> sampleList = CSampleArray::GetInstance()->SelectAllByTrack(idTrack);

    if (sampleList.empty())
    {
        LOG_ERROR("Could not find track with id: ", idTrack);
    }
    else
    {
        LOG_DBG("Returning location samples for idTrack: %d", idTrack);
    }
    return sampleList;
}

int CDatabase::EndTrack(int idTrack, int endDate, std::__cxx11::string endLocation, int distance, int manouverAssessment)
{
    QList<CTrackRecord> recordList = CTrackArray::GetInstance()->Select(idTrack);

    if (recordList.empty())
    {
        LOG_ERROR("Track not found");
        return 0;
    }

    CTrackRecord* record = (&recordList[0]);
    record->SetEndTimestamp(endDate);
    record->SetEndLocation(endLocation);
    record->SetDistance(distance);
    record->SetTrackAssessment(manouverAssessment);
    bool ret = CTrackArray::GetInstance()->Update(*record);

    if (ret)
    {
        LOG_DBG("idTrack: %d successfully ended.", idTrack);
        return 1;
    }

    LOG_ERROR("Could not update idTrack: %d", idTrack);
    return 0;
}

int CDatabase::DeleteTrack(int idTrack)
{
    QList<CSampleRecord> samplesList = CSampleArray::GetInstance()->SelectAllByTrack(idTrack);
    for(int i=0; i<samplesList.size(); ++i)
    {
       int idSample = static_cast<CSampleRecord&>(samplesList[i]).GetSampleId();
       bool ret = CSampleArray::GetInstance()->Delete(idSample);
       if (!ret)
       {
           LOG_ERROR("Could not delete track sample idSample: %d belonging to idTrack: %d", idSample, idTrack);
       }
    }
    LOG_DBG("Deleted: %d samples belonging to the idTrack: %d", samplesList.size(), idTrack);

    bool ret = CTrackArray::GetInstance()->Delete(idTrack);
    if (ret)
    {
        LOG_DBG("idTrack: %d deleted successfully", idTrack);
        return 1;
    }

    LOG_ERROR("idTrack: %d deleting failure", idTrack);
    return 0;
}

int CDatabase::AddTrackSample(int idTrack, int timestamp, std::__cxx11::string coordinates, int speed, int acceleration, int azimuth, int numOfSattellites, int hdop, int manouverAssessment, int fixStatus)
{
    CSampleRecord record(0, idTrack, timestamp, coordinates, speed, acceleration, azimuth, numOfSattellites, hdop, manouverAssessment, fixStatus);

    int insertedSampleId = CSampleArray::GetInstance()->Insert(record);

    if (insertedSampleId == -1)
    {
        LOG_ERROR("Could not add track sample to idTrack: %d", idTrack);
        return -1;
    }

    LOG_DBG("Sample added to idTrakck: %d", idTrack);
    return insertedSampleId;
}
