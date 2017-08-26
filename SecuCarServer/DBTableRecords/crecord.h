#ifndef CRECORD_H
#define CRECORD_H

class Record
{
public:
    virtual void LogRecord()
    {

    }

    virtual std::string Serialize()
    {

    }

protected:
    bool m_isValid = false;
};

#endif // CRECORD_H
