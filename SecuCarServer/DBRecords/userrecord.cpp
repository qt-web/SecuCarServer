#include "userrecord.h"
#include "logger.h"

CUserRecord::CUserRecord()
{

}

CUserRecord::CUserRecord(int id, std::string username, std::__cxx11::string name, std::__cxx11::string surname, std::__cxx11::string city, std::__cxx11::string street, int homeNumber, int flatNumber, std::__cxx11::string postalCode, std::__cxx11::string passwordHash)
{
    m_userId = id;
    m_username = username;
    m_name = name;
    m_surname = surname;
    m_city = city;
    m_street = street;
    m_homeNumber = homeNumber;
    m_flatNumber = flatNumber;
    m_postalCode = postalCode;
    m_passwordHash = passwordHash;

    LogRecord();
}

int CUserRecord::GetUserId()
{
    return m_userId;
}

std::string CUserRecord::GetUserName()
{
    return m_username;
}

std::string CUserRecord::GetName()
{
    return m_name;
}

std::string CUserRecord::GetSurname()
{
    return m_surname;
}

std::string CUserRecord::GetCity()
{
    return m_city;
}

std::string CUserRecord::GetStreet()
{
    return m_street;
}

int CUserRecord::GetHomeNumber()
{
    return m_homeNumber;
}

int CUserRecord::GetFlatNumber()
{
    return m_flatNumber;
}

std::string CUserRecord::GetPostalCode()
{
    return m_postalCode;
}

std::string CUserRecord::GetPasswordHash()
{
    return m_passwordHash;
}

void CUserRecord::LogRecord()
{
    LOG_INFO("Record: userId: %d, username: %s, name: %s, surname: %s, city: %s, street: %s, homeNumber: %d, flatNumber: %d, postalCode: %s, passwordHash: %s",
             m_userId, m_username.c_str(), m_name.c_str(), m_surname.c_str(), m_city.c_str(), m_street.c_str(), m_homeNumber, m_flatNumber, m_postalCode.c_str(), m_passwordHash.c_str());
}
