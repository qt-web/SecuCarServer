#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <vector>
#include <qttpserver>
#include <samplerecord.h>
/**
 * @brief The CHttpServer class - This class is responsible for receiving requests from users and devices,
 *               taking actions and sending response to the requester
 */
class CHttpServer : public QObject
{
    Q_OBJECT
public:

    static CHttpServer* GetInstance();

    /**
     * @brief Initialize the server - define actions to HTTP requests and add callbacks to service them
     */
    void Initialize();

    /**
     * @brief Start - Start the http server - It works in it's own thread
     */
    void Start();
signals:

public slots:

private:
    explicit CHttpServer(QObject *parent = 0);

    /**
     * @brief m_getInstance - Get instance of qttp lib http server
     * @return
     */
    qttp::HttpServer* m_qttpServerGetInstance();

    /**  <<< ADDING ACTIONS >>> **/

    void m_addActionToOptionsRequest();

    /**
     * @brief CHttpServer::m_addActionToLogin - Add action to login http request
     */
    void m_addActionToLogin();

    /**
     * @brief m_addActionToLogout - Adds action to logout request
     */
    void m_addActionToLogout();

    /**
     * @brief CHttpServer::m_addActionToRegisterUser - Add action to Register user http request
     */
    void m_addActionToRegisterUser();

    /**
     * @brief m_addActionToGetUserData - Adds action to request for user account data
     */
    void m_addActionToGetUserData();

    /**
     * @brief m_addActionToChangeUserData - Adds action to request for changing user account data
     */
    void m_addActionToChangeUserData();

    /**
     * @brief m_addActionToChangePassword - Adds action to request for changing user password
     */
    void m_addActionToChangePassword();

    /**
     * @brief m_addActionToDeleteUser - Adds action to request for delete user account
     */
    void m_addActionToDeleteUser();

    /**
     * @brief CHttpServer::m_addActionToAddDevice - Adds action to Add Device http request
     */
    void m_addActionToAddDevice();

    /**
     * @brief m_addActionToGetDevicesList - Adds action to List User Devices request
     */
    void m_addActionToGetDevicesList();

    /**
     * @brief CHttpServer::m_addActionToGetDeviceInfo - Adds action to Get Device Info http request
     */
    void m_addActionToGetDeviceInfo();

    /**
     * @brief CHttpServer::m_addActionToGetDeviceCurLocation - Adds action to Get Current Device Location http request
     */
    void m_addActionToGetDeviceCurLocation();

    /**
     * @brief m_addActionToGetLatestFirmwareVersion - Add action to Get Latest Firmware Version http request - request sent by the device
     */
    void m_addActionToGetLatestFirmwareVersion();

    /**
     * @brief m_addActionToUpdateFirmware - Add action to Update Firmware http request - request sent by the device
     */
    void m_addActionToUpdateFirmware();

    /**
     * @brief m_addActionToChangeDeviceName - Adda ction to change device name
     */
    void m_addActionToChangeDeviceName();

    /**
     * @brief m_addActionToDeleteDevice - Adds action to request for device deletion
     */
    void m_addActionToDeleteDevice();

    /**
     * @brief m_addActionToAddNewTrack - Add action to Add new track http request - request sent by device
     */
    void m_addActionToAddNewTrack();

    /**
     * @brief m_addActionToListTracks - Adds action to List Tracks request
     */
    void m_addActionToListTracks();

    /**
     * @brief CHttpServer::m_addActionToGetTrackInfo - Add action to Get Track http request - returns the basinc info about the track
     */
    void m_addActionToGetTrackInfo();

    /**
     * @brief m_addActionToGetTrackDetails - Add action to Get track samples
     */
    void m_addActionToGetTrackDetails();

    /**
     * @brief m_addActionToEndTrack - Add action to end of the track
     */
    void m_addActionToEndTrack();

    /**
     * @brief m_addActionToDeleteTrack - Adds action to deleting the track request
     */
    void m_addActionToDeleteTrack();

    /**
     * @brief m_addActionToAddNewTrackSample - Add action to Add New Track Sample http request - request sent by the device
     */
    void m_addActionToAddNewTrackSample();


    /**  <<< REQUEST CALLBACKS >>> **/
    /**    #### USER  REQUESTS ####    **/
    static void m_onOptions(qttp::HttpData& request);

    /**
     * @brief m_onLogin - Callback for login request. Sends back the idUser if logged in successfully, otherwise idUser is set to -1
     * @param request - contains JSON with "username" and "password fields
     */
    static void m_onLogin(qttp::HttpData& request);

    /**
     * @brief m_onLogout - Callback for logging out. Sends back the idUser as -1.
     * @param request
     */
    static void m_onLogout(qttp::HttpData& request);

    /**
     * @brief m_onRegisterUser - Callback for register user request. Adds user to the database. Sends back "result" as 1 if succeeded, 0 otherwise
     * @param request
     */
    static void m_onRegisterUser(qttp::HttpData& request);

    /**
     * @brief m_onGetUserData - Callback for getting user acount information.
     * @param request
     */
    static void m_onGetUserData(qttp::HttpData& request);

    /**
     * @brief m_onUserDataChange - Callback for changing user account information.
     * @param request
     */
    static void m_onUserDataChange(qttp::HttpData& request);

    /**
     * @brief m_onChangeUserPassword - Callback for changing user password
     * @param request
     */
    static void m_onChangeUserPassword(qttp::HttpData& request);

    /**
     * @brief m_onUserDelete - Callback for user deleting
     * @param request
     */
    static void m_onUserDelete(qttp::HttpData& request);


    /**    #### DEVICES REQUESTS ####    **/

    /**
     * @brief m_onAddDevice _ callback for adding device
     * @param request
     */
    static void m_onAddDevice(qttp::HttpData& request);

    /**
     * @brief m_onListDevices - Callback for devices list request
     * @param request
     */
    static void m_onListDevices(qttp::HttpData& request);

    /**
     * @brief m_onGetDeviceInfo - Callback for request for device details
     * @param request
     */
    static void m_onGetDeviceInfo(qttp::HttpData& request);

    /**
     * @brief m_onGetDeviceCurLocation - Callback for request for current location of the requested device ("idDevice")
     * @param request
     */
    static void m_onGetDeviceCurLocation(qttp::HttpData& request);

    /**
     * @brief m_onChangeDeviceName - Callback for request to change device name
     * @param request
     */
    static void m_onChangeDeviceName(qttp::HttpData& request);

    /**
     * @brief m_onGetLatestFirmareVersion - Callback for request for latest available firmware software
     * @param request
     */
    static void m_onGetLatestFirmareVersion(qttp::HttpData& request);

    /**
     * @brief m_onUpdateFirmware - Callback for updating firmware request (sent by device)
     * @param request
     */
    static void m_onUpdateFirmware(qttp::HttpData& request);

    /**
     * @brief m_onDeviceDelete - Callback for device delete request
     * @param request
     */
    static void m_onDeviceDelete(qttp::HttpData& request);


    /**    #### TRACKS REQUESTS ####    **/

    /**
     * @brief m_onAddNewTrack - Callback for adding new track
     * @param request
     */
    static void m_onAddNewTrack(qttp::HttpData& request);

    /**
     * @brief m_onListTracks - Callback for listing tracks for the specified device request
     * @param request
     */
    static void m_onListTracks(qttp::HttpData& request);

    /**
     * @brief m_onGetTrackInfo - Callback for request for getting track info
     * @param request
     */
    static void m_onGetTrackInfo(qttp::HttpData& request);

    /**
     * @brief m_onGetTrackDetails - Callback for request for samples for a specified track
     * @param request
     */
    static void m_onGetTrackDetails(qttp::HttpData& request);

    static void m_splitCoordsToLatAndLong(std::string inCoords, std::string& outLatitude, std::string& outLongtitude);

    static double m_splitCoordToDegrees(std::string coord);

    static double m_calculateTotalDistance(QList<CSampleRecord>& samples);

    static int m_calculateMeanAssessment(QList<CSampleRecord>& samples);

    /**
     * @brief m_onEndTrack - Callback for request to end the specified track
     * @param request
     */
    static void m_onEndTrack(qttp::HttpData& request);

    /**
     * @brief m_onTrackDelete - Callback for request to delete the specified track
     * @param request
     */
    static void m_onTrackDelete(qttp::HttpData& request);

    /**
     * @brief m_onAddNewTrackSample - Callback for request to
     * @param request
     */
    static void m_onAddNewTrackSample(qttp::HttpData& request);
};

#endif // HTTPSERVER_H
