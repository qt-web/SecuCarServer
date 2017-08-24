#ifndef USERRECORD_H
#define USERRECORD_H

#include <string>
#include "crecord.h"

class CUserRecord : public Record
{
public:
    CUserRecord(int id, std::string username, std::string name, std::string surname, std::string city, std::string street, int homeNumber, int flatNumber, std::string postalCode, std::string passwordHash);

    CUserRecord(const CUserRecord& rec);

    int GetUserId()  const;

    std::string GetUserName() const;

    std::string GetName() const;

    std::string GetSurname() const;

    std::string GetCity() const;

    std::string GetStreet() const;

    int GetHomeNumber() const;

    int GetFlatNumber() const;

    std::string GetPostalCode() const;

    std::string GetPasswordHash() const;

    void LogRecord();
private:
    CUserRecord();

    int m_userId;

    std::string m_username;

    std::string m_name;

    std::string m_surname;

    std::string m_city;

    std::string m_street;

    int m_homeNumber;

    int m_flatNumber;

    std::string m_postalCode;

    std::string m_passwordHash;
};

#endif // USERRECORD_H
