#ifndef CRECORD_H
#define CRECORD_H

#include <string>

/**
 * @brief The Record class - The base class of all the records
 */
class Record
{
public:
    virtual void LogRecord()
    {

    }

    virtual std::string Serialize()
    {
        return "";
    }

protected:
    bool m_isValid = false;
};

#endif // CRECORD_H
