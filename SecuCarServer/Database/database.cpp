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

    bool retval = m_pUserArray->Insert(record);

    if (retval)
        return 1;

    return -1;
}

CUserRecord CDatabase::GetUserData(int idUser)
{
    QList<Record> recList = m_pUserArray->Select(idUser);
    if (recList.empty())
    {
        LOG_ERROR("No user found with idUser: %d", idUser);
        return CUserRecord(-1, "", "", "", "", -1, "", "", -1, -1, "", "");
    }

    CUserRecord c = static_cast<CUserRecord&>(recList[0]);
    return c;
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

    QList<Record> _rec = m_pUserArray->Select(idUser);
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
