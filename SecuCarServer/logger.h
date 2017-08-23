#ifndef LOGGER_H
#define LOGGER_H
#include <QDebug>
#include <errno.h>
#include <map>

/**
 * @macro __FILENAME__ - Macro which returns 'pretty' function - only the name, without the directory path
 */
#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)


/**
 * @brief The Logger class - Class providing logging functionality
 */
class Logger
{
public:

    /**
     * @brief The EMessageType enum - types of logs. Depending on those types, logs are coloured differently
     */
    enum class EMessageType: uint8_t
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    /**
     * @brief s_errnoMap - Map containing connection between errno value and human readable error type
     */
    static std::map<int, std::string> s_errnoMap;

    /**
     * @brief Logger - Constructor and main logging function
     * @param msgType - type of log
     * @param fileName - file name which is to be logged
     * @param functionName - function name which is to be logged
     * @param line - line in file which is to be logged
     * @param a... - vararg list containing additional user text and params which are to be displayed
     */
    Logger(EMessageType msgType, const char *fileName, const char* functionName, const int line, const char *a, ...);

private:
    /**
     * @brief M_LOG_BUFFER_SIZE - size of internal single line log buffer
     */
    const unsigned short M_LOG_BUFFER_SIZE = 512;

};

#define LOG_ERRNO() LOG_CRITICAL("ERRNO MESSAGE: %s", Logger::s_errnoMap[errno].c_str())

#define LOG_DBG(...)           LOG(Logger::EMessageType::DEBUG, __VA_ARGS__ )
#define LOG_INFO(...)          LOG(Logger::EMessageType::INFO, __VA_ARGS__)
#define LOG_WARNING(...)       LOG(Logger::EMessageType::WARNING, __VA_ARGS__ )
#define LOG_ERROR(...)         LOG(Logger::EMessageType::ERROR, __VA_ARGS__ )
#define LOG_FATAL(...)         LOG(Logger::EMessageType::FATAL, __VA_ARGS__ )

#define LOG(msgType, ...)  Logger(msgType, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__ )

#endif // LOGGER_H
