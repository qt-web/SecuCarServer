#ifndef TRACKRECORD_H
#define TRACKRECORD_H

#include <string>
#include "crecord.h"

/**
 * @brief The CTrackRecord class - This class represents the track table record
 */
class CTrackRecord : public Record
{
public:

    /**
     * @brief CTrackRecord
     * @param trackId
     * @param deviceId
     * @param startTimestmap
     * @param startLocation
     * @param endTimestamp
     * @param endLocation
     * @param distance
     * @param maneouverAssessment
     */
    CTrackRecord(int trackId, int deviceId, int startTimestmap, std::string startLocation, int endTimestamp, std::string endLocation, int distance, int maneouverAssessment);

    /**
     * @brief CTrackRecord - copy constructor
     * @param rec
     */
    CTrackRecord(const CTrackRecord& rec);

    /**
     * @brief GetTrackId
     * @return
     */
    int GetTrackId() const;

    /**
     * @brief GetDeviceId
     * @return
     */
    int GetDeviceId() const;

    /**
     * @brief GetStartTimestmap
     * @return
     */
    int GetStartTimestmap() const;

    /**
     * @brief GetStartLocation
     * @return
     */
    std::string GetStartLocation() const;

    /**
     * @brief GetEndTimestamp
     * @return
     */
    int GetEndTimestamp() const;

    /**
     * @brief GetEndLocation
     * @return
     */
    std::string GetEndLocation() const;

    /**
     * @brief GetDistance
     * @return
     */
    int GetDistance() const;

    /**
     * @brief GetManeouverAssessment
     * @return
     */
    int GetManeouverAssessment() const;

    /**
     * @brief SetTrackId
     * @param id
     */
    void SetTrackId(int id);

    /**
     * @brief SetDeviceId
     * @param id
     */
    void SetDeviceId(int id);

    /**
     * @brief SetStartTimestamp
     * @param timestamp
     */
    void SetStartTimestamp(int timestamp);

    /**
     * @brief SetStartLocation
     * @param location
     */
    void SetStartLocation(std::string location);

    /**
     * @brief SetEndTimestamp
     * @param timestamp
     */
    void SetEndTimestamp(int timestamp);

    /**
     * @brief SetEndLocation
     * @param endLocation
     */
    void SetEndLocation(std::string endLocation);

    /**
     * @brief SetDistance
     * @param distance
     */
    void SetDistance(int distance);

    /**
     * @brief SetManeouverAssessment
     * @param assessment
     */
    void SetManeouverAssessment(int assessment);

    /// @class Record functions
    void LogRecord();

    std::string Serialize();
private:

    /**
     * @brief CTrackRecord
     */
    CTrackRecord();

    /**
     * @brief m_trackId - idTrack database field.
     */
    int m_trackId;

    /**
     * @brief m_deviceId - idDevice database field. It holds the device which created the track.
     */
    int m_deviceId;

    /**
     * @brief m_startTimestamp - startTimestamp database field. Timestamp when the track was created.
     */
    int m_startTimestamp;

    /**
     * @brief m_startLocation - startLocation database field.
     */
    std::string m_startLocation;

    /**
     * @brief m_endTimestamp - endTimestamp database field.
     */
    int m_endTimestamp;

    /**
     * @brief m_endLocation - endLocation database field.
     */
    std::string m_endLocation;

    /**
     * @brief m_distance - distance database field.
     */
    int m_distance;

    /**
     * @brief m_maneouverAssessment - manouverAssessment database field.
     */
    int m_maneouverAssessment;
};

#endif // TRACKRECORD_H
