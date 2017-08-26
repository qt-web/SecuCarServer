#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <vector>
#include <qttpserver>

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
     * @brief CHttpServer::m_addActionToRegisterUser - Add action to Register user http request
     */
    void m_addActionToRegisterUser();

    void m_addActionToGetUserData();

    void m_addActionToChangeUserData();

    void m_addActionToChangePassword();

    /**
     * @brief CHttpServer::m_addActionToAddDevice - Add action to Add Device http request
     */
    void m_addActionToAddDevice();

    void m_addActionToGetDevicesList();
    /**
     * @brief CHttpServer::m_addActionToGetDeviceInfo - Add action to Get Device Info http request
     */
    void m_addActionToGetDeviceInfo();

    /**
     * @brief CHttpServer::m_addActionToGetDeviceCurLocation - Add action to Get Current Device Location http request
     */
    void m_addActionToGetDeviceCurLocation();

    /**
     * @brief CHttpServer::m_addActionToGetTrackInfo - Add action to Get Track http request - returns the basinc info about the track
     */
    void m_addActionToGetTrackInfo();

    /**
     * @brief m_addActionToGetTrackDetails - Add action to Get track samples
     */
    void m_addActionToGetTrackDetails();

    /**
     * @brief m_addActionToAddNewTrack - Add action to Add new track http request - request sent by device
     */
    void m_addActionToAddNewTrack();

    /**
     * @brief m_addActionToEndTrack - Add action to end of the track
     */
    void m_addActionToEndTrack();

    /**
     * @brief m_addActionToAddNewTrackSample - Add action to Add New Track Sample http request - request sent by the device
     */
    void m_addActionToAddNewTrackSample();

    /**
     * @brief m_addActionToGetLatestFirmwareVersion - Add action to Get Latest Firmware Version http request - request sent by the device
     */
    void m_addActionToGetLatestFirmwareVersion();

    /**
     * @brief m_addActionToUpdateFirmware - Add action to Update Firmware http request - request sent by the device
     */
    void m_addActionToUpdateFirmware();

    /**  <<< REQUEST CALLBACKS >>> **/
    /**    #### USER  REQUESTS ####    **/
    static void m_onOptions(qttp::HttpData& request);

    static void m_onLogin(qttp::HttpData& request);

    static void m_onRegisterUser(qttp::HttpData& request);

    static void m_onGetUserData(qttp::HttpData& request);

    static void m_onUserDataChange(qttp::HttpData& request);

    static void m_onChangeUserPassword(qttp::HttpData& request);


    /**    #### DEVICES REQUESTS ####    **/
    static void m_onAddDevice(qttp::HttpData& request);

    static void m_onListDevices(qttp::HttpData& request);

    static void m_onGetDeviceInfo(qttp::HttpData& request);

    static void m_onGetDeviceCurLocation(qttp::HttpData& request);

    static void m_onGetLatestFirmareVersion(qttp::HttpData& request);

    static void m_onUpdateFirmware(qttp::HttpData& request);


    /**    #### TRACKS REQUESTS ####    **/
    static void m_onAddNewTrack(qttp::HttpData& request);

    static void m_onListTracks(qttp::HttpData& request);

    static void m_onGetTrackInfo(qttp::HttpData& request);

    static void m_onGetTrackDetails(qttp::HttpData& request);

    static void m_onEndTrack(qttp::HttpData& request);

    static void m_onAddNewTrackSample(qttp::HttpData& request);

};

#endif // HTTPSERVER_H
