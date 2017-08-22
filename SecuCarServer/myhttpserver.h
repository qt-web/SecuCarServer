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

    /**
     * @brief CHttpServer::m_addActionToLogin - Add action to login http request
     */
    void m_addActionToLogin();

    /**
     * @brief CHttpServer::m_addActionToRegisterUser - Add action to Register user http request
     */
    void m_addActionToRegisterUser();

    /**
     * @brief CHttpServer::m_addActionToAddDevice - Add action to Add Device http request
     */
    void m_addActionToAddDevice();

    /**
     * @brief CHttpServer::m_addActionToGetDeviceInfo - Add action to Get Device Info http request
     */
    void m_addActionToGetDeviceInfo();

    /**
     * @brief CHttpServer::m_addActionToGetDeviceCurLocation - Add action to Get Current Device Location http request
     */
    void m_addActionToGetDeviceCurLocation();

    /**
     * @brief CHttpServer::m_addActionToGetTrack - Add action to Get Track http request - returns all the location samples about the requested track
     */
    void m_addActionToGetTrack();

    /**
     * @brief m_addActionToAddNewTrack - Add action to Add new track http request - request sent by device
     */
    void m_addActionToAddNewTrack();

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
    /**         #### USER SIDE REQUESTS ####    **/
    static void m_onLogin(qttp::HttpData& request);

    static void m_onRegisterUser(qttp::HttpData& request);

    static void m_onAddDevice(qttp::HttpData& request);

    static void m_onGetDeviceInfo(qttp::HttpData& request);

    static void m_onGetDeviceCurLocation(qttp::HttpData& request);

    static void m_onGetTrack(qttp::HttpData& request);

    /**         #### DEVICE SIDE REQUESTS ####    **/
    static void m_onAddNewTrack(qttp::HttpData& request);

    static void m_onAddNewTrackSample(qttp::HttpData& request);

    static void m_onGetLatestFirmareVersion(qttp::HttpData& request);

    static void m_onUpdateFirmware(qttp::HttpData& request);
};

#endif // HTTPSERVER_H