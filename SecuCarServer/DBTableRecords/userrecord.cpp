#include "userrecord.h"
#include "logger.h"
#include <sstream>
#include <string>

CUserRecord::CUserRecord()
{

}

CUserRecord::CUserRecord(int id,
                         std::string username,
                         std::__cxx11::string name,
                         std::__cxx11::string surname,
                         std::string email,
                         int telephoneNumber,
                         std::__cxx11::string city,
                         std::__cxx11::string street,
                         int homeNumber,
                         int flatNumber,
                         std::__cxx11::string postalCode,
                         std::__cxx11::string passwordHash)
{
    m_userId = id;
    m_username = username;
    m_name = name;
    m_surname = surname;
    m_email = email;
    m_telephone = telephoneNumber;
    m_city = city;
    m_street = street;
    m_homeNumber = homeNumber;
    m_flatNumber = flatNumber;
    m_postalCode = postalCode;
    m_passwordHash = passwordHash;

    LogRecord();
}

CUserRecord::CUserRecord(const CUserRecord &rec)
{
    this->m_userId = rec.GetUserId();
    this->m_username = rec.GetUserName();
    this->m_name = rec.GetName();
    this->m_surname = rec.GetSurname();
    this->m_email = rec.GetEmail();
    this->m_telephone = rec.GetTelephone();
    this->m_city = rec.GetCity();
    this->m_street = rec.GetStreet();
    this->m_homeNumber = rec.GetHomeNumber();
    this->m_flatNumber = rec.GetFlatNumber();
    this->m_postalCode = rec.GetPostalCode();
    this->m_passwordHash = rec.GetPasswordHash();
}

CUserRecord::CUserRecord(CUserRecord &rec)
{
    this->m_userId = rec.GetUserId();
    this->m_username = rec.GetUserName();
    this->m_name = rec.GetName();
    this->m_surname = rec.GetSurname();
    this->m_email = rec.GetEmail();
    this->m_telephone = rec.GetTelephone();
    this->m_city = rec.GetCity();
    this->m_street = rec.GetStreet();
    this->m_homeNumber = rec.GetHomeNumber();
    this->m_flatNumber = rec.GetFlatNumber();
    this->m_postalCode = rec.GetPostalCode();
    this->m_passwordHash = rec.GetPasswordHash();
}

int CUserRecord::GetUserId() const
{
    return m_userId;
}

std::string CUserRecord::GetUserName() const
{
    return m_username;
}

std::string CUserRecord::GetName() const
{
    return m_name;
}

std::string CUserRecord::GetSurname() const
{
    return m_surname;
}

std::string CUserRecord::GetEmail() const
{
    return m_email;
}

int CUserRecord::GetTelephone() const
{
    return m_telephone;
}

std::string CUserRecord::GetCity() const
{
    return m_city;
}

std::string CUserRecord::GetStreet() const
{
    return m_street;
}

int CUserRecord::GetHomeNumber() const
{
    return m_homeNumber;
}

int CUserRecord::GetFlatNumber() const
{
    return m_flatNumber;
}

std::string CUserRecord::GetPostalCode() const
{
    return m_postalCode;
}

std::string CUserRecord::GetPasswordHash() const
{
    return m_passwordHash;
}

void CUserRecord::SetUserId(int id)
{
    m_userId = id;
}

void CUserRecord::SetUserName(std::string username)
{
    m_username = username;
}

void CUserRecord::SetName(std::string name)
{
    m_name = name;
}

void CUserRecord::SetSurname(std::__cxx11::string surname)
{
    m_surname = surname;
}

void CUserRecord::SetEmail(std::__cxx11::string email)
{
    m_email = email;
}

void CUserRecord::SetTelephone(int phoneNumber)
{
    m_telephone = phoneNumber;
}

void CUserRecord::SetCity(std::string city)
{
    m_city = city;
}

void CUserRecord::SetStreet(std::string street)
{
    m_street = street;
}

void CUserRecord::SetHomeNumber(int number)
{
    m_homeNumber = number;
}

void CUserRecord::SetFlatNumber(int number)
{
    m_flatNumber = number;
}

void CUserRecord::SetPostalCode(std::__cxx11::string postalCode)
{
    m_postalCode = postalCode;
}

void CUserRecord::SetPasswordHash(std::string passwordHash)
{
    m_passwordHash = passwordHash;
}

void CUserRecord::LogRecord()
{
    LOG_INFO("idUser: %d, username: %s, name: %s, surname: %s, email: %s, telephone: %d, city: %s, street: %s, homeNumber: %d, flatNumber: %d, postalCode: %s, passwordHash: %s",
                      m_userId, m_username.c_str(), m_name.c_str(), m_surname.c_str(), m_email.c_str(), m_telephone, m_city.c_str(), m_street.c_str(), m_homeNumber, m_flatNumber, m_postalCode.c_str(), m_passwordHash.c_str());
}

const char* CUserRecord::Serialize()
{
    std::stringstream ss;
    ss << "idUser: " << m_userId << ", " <<
          "username: " << m_username << ", " <<
          "name: " << m_name << ", " <<
          "surname: " << m_surname << ", " <<
          "email: " << m_email << ", " <<
          "telephone: " << m_telephone << ", " <<
          "city: " << m_city << ", " <<
          "street: " << m_street << ", " <<
          "homeNumber: " << m_homeNumber << ", " <<
          "flatNumber: " << m_flatNumber << ", " <<
          "postalCode: " << m_postalCode << ", " <<
          "passwordHash: " << m_passwordHash;

    return ss.str().c_str();
 }
