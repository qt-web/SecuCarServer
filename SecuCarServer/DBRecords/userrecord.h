#ifndef USERRECORD_H
#define USERRECORD_H

#include <string>
#include "crecord.h"

class CUserRecord : public Record
{
public:
    CUserRecord(int id,
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
                std::__cxx11::string passwordHash);

    CUserRecord(const CUserRecord& rec);

    int GetUserId()  const;

    std::string GetUserName() const;

    std::string GetName() const;

    std::string GetSurname() const;

    std::string GetEmail() const;

    int GetTelephone() const;

    std::string GetCity() const;

    std::string GetStreet() const;

    int GetHomeNumber() const;

    int GetFlatNumber() const;

    std::string GetPostalCode() const;

    std::string GetPasswordHash() const;

    void SetUserId(int id);

    void SetUserName(std::string username);

    void SetName(std::string name);

    void SetSurname(std::string surname);

    void SetEmail(std::string email);

    void SetTelephone(int phoneNumber);

    void SetCity(std::__cxx11::string city);

    void SetStreet(std::string street);

    void SetHomeNumber(int number);

    void SetFlatNumber(int number);

    void SetPostalCode(std::string postalCode);

    void SetPasswordHash(std::string passwordHash);

    void LogRecord();
private:
    CUserRecord();

    int m_userId;

    std::string m_username;

    std::string m_name;

    std::string m_surname;

    std::string m_email;

    int m_telephone;

    std::string m_city;

    std::string m_street;

    int m_homeNumber;

    int m_flatNumber;

    std::string m_postalCode;

    std::string m_passwordHash;
};

#endif // USERRECORD_H
