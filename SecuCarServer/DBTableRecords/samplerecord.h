#ifndef SAMPLERECORD_H
#define SAMPLERECORD_H

#include <string>
#include "crecord.h"


/**
 * @brief The CSampleRecord class - This class represents the sample record
 */
class CSampleRecord : public Record
{
public:
    /**
     * @brief CSampleRecord
     * @param sampleId
     * @param trackId
     * @param timestamp
     * @param coordinates
     * @param speed
     * @param acceleration
     * @param azimuth
     */
    CSampleRecord(int sampleId, int trackId, int timestamp, std::string coordinates, int speed, int acceleration, int azimuth, int numOfSattellites, int hdop, int manouverAssessment);

    /**
     * @brief CSampleRecord
     * @param rec
     */
    CSampleRecord(const CSampleRecord& rec);

    /**
     * @brief GetSampleId
     * @return
     */
    int GetSampleId() const;

    /**
     * @brief GetTrackId
     * @return
     */
    int GetTrackId() const;

    /**
     * @brief GetTimestamp
     * @return
     */
    int GetTimestamp() const;

    /**
     * @brief GetCoordinates
     * @return
     */
    std::string GetCoordinates() const;

    /**
     * @brief GetSpeed
     * @return
     */
    int GetSpeed() const;

    /**
     * @brief GetAcceleration
     * @return
     */
    int GetAcceleration() const;

    /**
     * @brief GetAzimuth
     * @return
     */
    int GetAzimuth() const;

    int GetNumOfSattellites() const;

    int GetHdop() const;

    int GetManouverAssessment() const;

    /**
     * @brief SetSampleId
     * @param id
     */
    void SetSampleId(int id);

    /**
     * @brief SetTrackId
     * @param id
     */
    void SetTrackId(int id);

    /**
     * @brief SetTimestamp
     * @param timestamp
     */
    void SetTimestamp(int timestamp);

    /**
     * @brief SetCoordinates
     * @param coordinates
     */
    void SetCoordinates(std::string coordinates);

    /**
     * @brief SetSpeed
     * @param speed
     */
    void SetSpeed(int speed);

    /**
     * @brief SetAcceleration
     * @param acceleration
     */
    void SetAcceleration(int acceleration);

    /**
     * @brief SetAzimuth
     * @param azimuth
     */
    void SetAzimuth(int azimuth);

    //  @class Record functions

    void LogRecord();

    std::string Serialize();

private:
    /**
     * @brief CSampleRecord
     */
    CSampleRecord();

    /**
     * @brief m_sampleId - idSample database field.
     */
    int m_sampleId;

    /**
     * @brief m_trackId - idTrack database field. Describes the track to which sample will belong to
     */
    int m_trackId;

    /**
     * @brief m_timestamp - timestamp database field - timestamp from which the sample was gathered
     */
    int m_timestamp;

    /**
     * @brief m_coordinates - coordinates database field. Coordinates of the sample
     */
    std::string m_coordinates;

    /**
     * @brief m_speed - speed database field. Speed when the sample was gathered
     */
    int m_speed;

    /**
     * @brief m_acceleration - acceleration database field. Acceleration when the sample was gathered
     */
    int m_acceleration;

    /**
     * @brief m_azimuth - azimuth database field. Azimuth when the sample was gathered
     */
    int m_azimuth;

    int m_numOfSattelites;

    int m_hdop;

    int m_manouverAssessment;
};

#endif // SAMPLERECORD_H
