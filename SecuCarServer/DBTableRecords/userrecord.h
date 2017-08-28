#ifndef USERRECORD_H
#define USERRECORD_H

#include <string>
#include "crecord.h"

/**
 * @brief The CUserRecord class - The class represents the user table record
 */
class CUserRecord : public Record
{
public:
    /**
     * @brief CUserRecord
     * @param id
     * @param username
     * @param name
     * @param surname
     * @param email
     * @param telephoneNumber
     * @param city
     * @param street
     * @param homeNumber
     * @param flatNumber
     * @param postalCode
     * @param passwordHash
     */
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

    /**
     * @brief CUserRecord - copy constructor
     * @param rec
     */
    CUserRecord(const CUserRecord& rec);

    /**
     * @brief CUserRecord - copy constructor 2
     * @param rec
     */
    CUserRecord(CUserRecord &rec);

    /**
     * @brief CUserRecord
     */
    CUserRecord();

    /**
     * @brief GetUserId
     * @return
     */
    int GetUserId()  const;

    /**
     * @brief GetUserName
     * @return
     */
    std::string GetUserName() const;

    /**
     * @brief GetName
     * @return
     */
    std::string GetName() const;

    /**
     * @brief GetSurname
     * @return
     */
    std::string GetSurname() const;

    /**
     * @brief GetEmail
     * @return
     */
    std::string GetEmail() const;

    /**
     * @brief GetTelephone
     * @return
     */
    int GetTelephone() const;

    /**
     * @brief GetCity
     * @return
     */
    std::string GetCity() const;

    /**
     * @brief GetStreet
     * @return
     */
    std::string GetStreet() const;

    /**
     * @brief GetHomeNumber
     * @return
     */
    int GetHomeNumber() const;

    /**
     * @brief GetFlatNumber
     * @return
     */
    int GetFlatNumber() const;

    /**
     * @brief GetPostalCode
     * @return
     */
    std::string GetPostalCode() const;

    /**
     * @brief GetPasswordHash
     * @return
     */
    std::string GetPasswordHash() const;

    /**
     * @brief SetUserId
     * @param id
     */
    void SetUserId(int id);

    /**
     * @brief SetUserName
     * @param username
     */
    void SetUserName(std::string username);

    /**
     * @brief SetName
     * @param name
     */
    void SetName(std::string name);

    /**
     * @brief SetSurname
     * @param surname
     */
    void SetSurname(std::string surname);

    /**
     * @brief SetEmail
     * @param email
     */
    void SetEmail(std::string email);

    /**
     * @brief SetTelephone
     * @param phoneNumber
     */
    void SetTelephone(int phoneNumber);

    /**
     * @brief SetCity
     * @param city
     */
    void SetCity(std::__cxx11::string city);

    /**
     * @brief SetStreet
     * @param street
     */
    void SetStreet(std::string street);

    /**
     * @brief SetHomeNumber
     * @param number
     */
    void SetHomeNumber(int number);

    /**
     * @brief SetFlatNumber
     * @param number
     */
    void SetFlatNumber(int number);

    /**
     * @brief SetPostalCode
     * @param postalCode
     */
    void SetPostalCode(std::string postalCode);

    /**
     * @brief SetPasswordHash
     * @param passwordHash
     */
    void SetPasswordHash(std::string passwordHash);

    /// @class Record functions
    void LogRecord();

    std::string Serialize();
private:

    /**
     * @brief m_userId - idUser database field
     */
    int m_userId;

    /**
     * @brief m_username - username database field
     */
    std::string m_username;

    /**
     * @brief m_name - name database field
     */
    std::string m_name;

    /**
     * @brief m_surname - surname database field
     */
    std::string m_surname;

    /**
     * @brief m_email - email database field
     */
    std::string m_email;

    /**
     * @brief m_telephone - telephone database field
     */
    int m_telephone;

    /**
     * @brief m_city - city database field
     */
    std::string m_city;

    /**
     * @brief m_street - street database field
     */
    std::string m_street;

    /**
     * @brief m_homeNumber - homeNumber database field
     */
    int m_homeNumber;

    /**
     * @brief m_flatNumber - flatNumber database field
     */
    int m_flatNumber;

    /**
     * @brief m_postalCode - postalCode database field
     */
    std::string m_postalCode;

    /**
     * @brief m_passwordHash - passwordHash database field
     */
    std::string m_passwordHash;
};

#endif // USERRECORD_H
