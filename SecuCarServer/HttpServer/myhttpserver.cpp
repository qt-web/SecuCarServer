#include "myhttpserver.h"
#include <httpserver.h>
#include <httpresponse.h>
#include <QJsonObject>
#include <QList>
#include "userarray.h"
#include "devicearray.h"
#include "trackarray.h"
#include "samplearray.h"
#include "userrecord.h"
#include "devicerecord.h"
#include "trackrecord.h"
#include "samplerecord.h"
#include "logger.h"
#include "database.h"
#include <QDateTime>
#include <QJsonDocument>

CHttpServer::CHttpServer(QObject *parent) : QObject(parent)
{

}

CHttpServer* CHttpServer::GetInstance()
{
    static CHttpServer s_instance;
    return &s_instance;
}

void CHttpServer::Initialize()
{
    m_qttpServerGetInstance()->initialize();

    // User's actions
    m_addActionToOptionsRequest();
    m_addActionToLogin();
    m_addActionToLogout();
    m_addActionToRegisterUser();
    m_addActionToGetUserData();
    m_addActionToChangeUserData();
    m_addActionToChangePassword();
    m_addActionToDeleteUser();

    // Device's actions
    m_addActionToAddDevice();
    m_addActionToGetDevicesList();
    m_addActionToGetDeviceInfo();
    m_addActionToGetDeviceCurLocation();
    m_addActionToChangeDeviceName();
    m_addActionToGetLatestFirmwareVersion();
    m_addActionToUpdateFirmware();
    m_addActionToDeleteDevice();

    m_addActionToAddNewTrack();
    m_addActionToListTracks();
    m_addActionToGetTrackInfo();
    m_addActionToGetTrackDetails();
    m_addActionToAddNewTrackSample();
    m_addActionToEndTrack();
    m_addActionToDeleteTrack();
}

void CHttpServer::Start()
{
    m_qttpServerGetInstance()->startServer();
}

qttp::HttpServer* CHttpServer::m_qttpServerGetInstance()
{
    return qttp::HttpServer::getInstance();
}

void CHttpServer::m_addActionToOptionsRequest()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Options", m_onOptions);
    action->registerRoute("OPTIONS", "Options", "/login");

    action->createAction("Options1", m_onOptions);
    action->registerRoute("OPTIONS", "Options1", "/logout");

    action->createAction("Options2", m_onOptions);
    action->registerRoute("OPTIONS", "Options2", "/register");

    action->createAction("Options3", m_onOptions);
    action->registerRoute("OPTIONS", "Options3", "/get_user_data");

    action->createAction("Options4", m_onOptions);
    action->registerRoute("OPTIONS", "Options4", "/change_user_data");

    action->createAction("Options5", m_onOptions);
    action->registerRoute("OPTIONS", "Options5", "/change_password");

    action->createAction("Options6", m_onOptions);
    action->registerRoute("OPTIONS", "Options6", "/delete_user");

    action->createAction("Options7", m_onOptions);
    action->registerRoute("OPTIONS", "Options7", "/add_device");

    action->createAction("Options8", m_onOptions);
    action->registerRoute("OPTIONS", "Options8", "/get_devices_list");

    action->createAction("Options9", m_onOptions);
    action->registerRoute("OPTIONS", "Options9", "/get_device_info");

    action->createAction("Options10", m_onOptions);
    action->registerRoute("OPTIONS", "Options10", "/get_latest_firmware_version");

    action->createAction("Options11", m_onOptions);
    action->registerRoute("OPTIONS", "Options11", "/update_firmware");

    action->createAction("Options12", m_onOptions);
    action->registerRoute("OPTIONS", "Options12", "/delete_device");

    action->createAction("Options13", m_onOptions);
    action->registerRoute("OPTIONS", "Options13", "/get_track_info");

    action->createAction("Options14", m_onOptions);
    action->registerRoute("OPTIONS", "Options14", "/get_track_details");

    action->createAction("Options15", m_onOptions);
    action->registerRoute("OPTIONS", "Options15", "/add_track");

    action->createAction("Options16", m_onOptions);
    action->registerRoute("OPTIONS", "Options16", "/list_tracks");

    action->createAction("Options17", m_onOptions);
    action->registerRoute("OPTIONS", "Options17", "/end_track");

    action->createAction("Options18", m_onOptions);
    action->registerRoute("OPTIONS", "Options18", "/add_track_sample");

    action->createAction("Options19", m_onOptions);
    action->registerRoute("OPTIONS", "Options19", "/delete_track");

    action->createAction("Options20", m_onOptions);
    action->registerRoute("OPTIONS", "Options20", "/change_device_name");
}

void CHttpServer::m_addActionToLogin()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Login", m_onLogin);
    action->registerRoute("POST", "Login", "/login");
}

void CHttpServer::m_addActionToLogout()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Logout", m_onLogout);
    action->registerRoute("GET", "Logout", "/logout");
}

void CHttpServer::m_addActionToRegisterUser()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Register", m_onRegisterUser);
    action->registerRoute("POST", "Register", "/register");
}

void CHttpServer::m_addActionToGetUserData()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetUserData", m_onGetUserData);
    action->registerRoute("GET", "GetUserData", "/get_user_data");
}

void CHttpServer::m_addActionToChangeUserData()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("ChangeUserData", m_onUserDataChange);
    action->registerRoute("POST", "ChangeUserData", "/change_user_data");
}

void CHttpServer::m_addActionToChangePassword()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("ChangePassword", m_onChangeUserPassword);
    action->registerRoute("POST", "ChangePassword", "/change_password");
}

void CHttpServer::m_addActionToDeleteUser()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("DeleteUser", m_onUserDelete);
    action->registerRoute("GET", "DeleteUser", "/delete_user");
}

void CHttpServer::m_addActionToAddDevice()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("AddDevice", m_onAddDevice);
    action->registerRoute("GET", "AddDevice", "/add_device");
}

void CHttpServer::m_addActionToGetDevicesList()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetDevicesList", m_onListDevices);
    action->registerRoute("GET", "GetDevicesList", "/get_devices_list");
}

void CHttpServer::m_addActionToGetDeviceInfo()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetDeviceInfo", m_onGetDeviceInfo);
    action->registerRoute("GET", "GetDeviceInfo", "/get_device_info");
}

void CHttpServer::m_addActionToGetDeviceCurLocation()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetCurrentDevLocation", m_onGetDeviceCurLocation);
    action->registerRoute("GET", "GetCurrentDevLocation", "/get_dev_location");
}

void CHttpServer::m_addActionToChangeDeviceName()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("ChangeDeviceName", m_onChangeDeviceName);
    action->registerRoute("GET", "ChangeDeviceName", "/change_device_name");
}

void CHttpServer::m_addActionToGetLatestFirmwareVersion()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetLatestFirmwareVersion", m_onGetLatestFirmareVersion);
    action->registerRoute("GET", "GetLatestFirmwareVersion", "/get_latest_firmware_version");
}

void CHttpServer::m_addActionToUpdateFirmware()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("UpdateFirmware", m_onUpdateFirmware);
    action->registerRoute("GET", "UpdateFirmware", "/update_firmware");
}

void CHttpServer::m_addActionToDeleteDevice()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("DeleteDevice", m_onDeviceDelete);
    action->registerRoute("GET", "DeleteDevice", "/delete_device");
}

void CHttpServer::m_addActionToGetTrackInfo()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetTrackInfo", m_onGetTrackInfo);
    action->registerRoute("GET", "GetTrackInfo", "/get_track_info");
}

void CHttpServer::m_addActionToGetTrackDetails()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetTrackDetails", m_onGetTrackDetails);
    action->registerRoute("GET", "GetTrackDetails", "/get_track_details");
}

void CHttpServer::m_addActionToAddNewTrack()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("AddNewTrack", m_onAddNewTrack);
    action->registerRoute("GET", "AddNewTrack", "/add_track");
}

void CHttpServer::m_addActionToListTracks()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("ListTracks", m_onListTracks);
    action->registerRoute("GET", "ListTracks", "/list_tracks");
}

void CHttpServer::m_addActionToEndTrack()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("EndTrack", m_onEndTrack);
    action->registerRoute("GET", "EndTrack", "/end_track");
}

void CHttpServer::m_addActionToAddNewTrackSample()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("AddNewTrackSample", m_onAddNewTrackSample);
    action->registerRoute("GET", "AddNewTrackSample", "/add_track_sample");
}

void CHttpServer::m_addActionToDeleteTrack()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("DeleteTrack", m_onTrackDelete);
    action->registerRoute("GET", "DeleteTrack", "/delete_track");
}

void CHttpServer::m_onOptions(qttp::HttpData& request)
{
    LOG_DBG("OPTIONS request received :%s", QString(QJsonDocument(request.getRequest().getJson()).toJson(QJsonDocument::Compact)).toStdString().c_str());
    QList< std::pair<QString, QString>> headersList;
    headersList.append(std::pair<QString, QString>("Access-Control-Allow-Origin", "*"));
    headersList.append(std::pair<QString, QString>("Access-Control-Allow-Methods", "POST, GET, OPTIONS"));
    headersList.append(std::pair<QString, QString>("Access-Control-Allow-Headers", "Content-Type"));
    headersList.append(std::pair<QString, QString>("Content-Type", ""));
    //request.getResponse().getJson()["result"] = 1;
    request.getResponse().setHeader(headersList);
    request.getResponse().removeHeader("Content-Type");
    request.getResponse().finish();
}

void CHttpServer::m_onLogin(qttp::HttpData& request)
{
    LOG_DBG("Login request received");
    const QJsonObject& requestJSON = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    LOG_DBG("Login request: %s", QString(QJsonDocument(requestJSON).toJson(QJsonDocument::Compact)).toStdString().c_str());

    std::string username = requestJSON["username"].toString().toStdString();
    std::string passwordHash = requestJSON["password"].toString().toStdString();

    int ret = CDatabase::GetInstance()->Login(username, passwordHash);

    if (ret >= 0)
    {
        LOG_DBG("User successfully %s logged in", username.c_str());
        response["result"] = 1;
        response["idUser"] = ret;
    }
    else
    {
        LOG_ERROR("User %s login failure", username.c_str());
        response["result"] = 0;
        response["idUser"] = -1;
    }

    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onLogout(qttp::HttpData &request)
{
    LOG_DBG("Logout request received");
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    response["result"] = 1;
    response["idUser"] = -1;

    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onRegisterUser(qttp::HttpData& request)
{
    const QJsonObject& requestJSON = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    std::string username = requestJSON["username"].toString().toStdString();
    std::string name = requestJSON["name"].toString().toStdString();
    std::string surname = requestJSON["surname"].toString().toStdString();
    std::string email = requestJSON["email"].toString().toStdString();
    int telephone = requestJSON["telephone"].toString().toInt();
    std::string city = requestJSON["city"].toString().toStdString();
    std::string street = requestJSON["street"].toString().toStdString();
    int homeNumber = requestJSON["homeNumber"].toString().toInt();
    int flatNumber = requestJSON["flatNumber"].toString().toInt();
    std::string postalCode = requestJSON["postalCode"].toString().toStdString();
    std::string passwordHash = requestJSON["password"].toString().toStdString();

    int ret = CDatabase::GetInstance()->RegisterUser(username,
                                                     name,
                                                     surname,
                                                     email,
                                                     telephone,
                                                     city,
                                                     street,
                                                     homeNumber,
                                                     flatNumber,
                                                     postalCode,
                                                     passwordHash);


    if (ret >= 0)
    {
        LOG_DBG("User successfully registered. idUser: %d", ret);
        response["result"] = 1;
    }
    else
    {
        LOG_ERROR("User registration failure");
        response["result"] = 0;
    }

    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onGetUserData(qttp::HttpData &request)
{
    const QJsonObject& requestJson = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");

    int idUser = requestJson["idUser"].toString().toInt();
    CUserRecord rec = CDatabase::GetInstance()->GetUserData(idUser);

    if (rec.GetUserId() == -1)
    {
        LOG_ERROR("No user found with idUser: %d", idUser);
        response["result"] = 0;
        return;
    }

    LOG_DBG("Request to read user data");

    response["result"] = 1;
    response["username"]    = rec.GetUserName().c_str();
    response["name"]        = rec.GetName().c_str();
    response["surname"]     = rec.GetSurname().c_str();
    response["email"]       = rec.GetEmail().c_str();
    response["telephone"]   = rec.GetTelephone();
    response["city"]        = rec.GetCity().c_str();
    response["street"]      = rec.GetStreet().c_str();
    response["homeNumber"]  = rec.GetHomeNumber();
    response["flatNumber"]  = rec.GetFlatNumber();
    response["postalCode"]  = rec.GetPostalCode().c_str();
}

void CHttpServer::m_onUserDataChange(qttp::HttpData &request)
{
    const QJsonObject& requestJson = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idUser = requestJson["idUser"].toString().toInt();
    CUserRecord record = CDatabase::GetInstance()->GetUserData(idUser);
    if (record.GetUserId() == -1)
    {
        LOG_ERROR("User not found. idUser: %d", idUser);
        response["result"] = 0;
        request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
        return;
    }

    std::string username = record.GetUserName();
    std::string name = requestJson["name"].toString().toStdString();
    std::string surname = requestJson["surname"].toString().toStdString();
    std::string email = requestJson["email"].toString().toStdString();
    int telephone = requestJson["telephone"].toString().toInt();
    std::string city = requestJson["city"].toString().toStdString();
    std::string street = requestJson["street"].toString().toStdString();
    int homeNumber = requestJson["homeNumber"].toString().toInt();
    int flatNumber = requestJson["flatNumber"].toString().toInt();
    std::string postalCode = requestJson["postalCode"].toString().toStdString();
    std::string passwordHash = record.GetPasswordHash();

    int ret = CDatabase::GetInstance()->ChangeUserData(  idUser,
                                                         username,
                                                         name,
                                                         surname,
                                                         email,
                                                         telephone,
                                                         city,
                                                         street,
                                                         homeNumber,
                                                         flatNumber,
                                                         postalCode,
                                                         passwordHash);


    if (ret > 0)
    {
        LOG_DBG("Changing the user data succeeded");
        response["result"] = 1;
    }
    else
    {
        LOG_ERROR("Changing the user data failed");
        response["result"] = 0;
    }

    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onChangeUserPassword(qttp::HttpData &request)
{
    const QJsonObject& requestJson = request.getRequest().getJson();
    QJsonObject& resultJson = request.getResponse().getJson();

    int idUser                  = requestJson["idUser"].toString().toInt();
    std::string oldPasswordHash = requestJson["oldPassword"].toString().toStdString();
    std::string newPasswordHash = requestJson["newPassword"].toString().toStdString();

    if (oldPasswordHash == newPasswordHash)
    {
        LOG_ERROR("New password is the same as the current one.");
        resultJson["result"] = -1;
        request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
        return;
    }

    int ret = CDatabase::GetInstance()->ChangePassword(idUser, oldPasswordHash, newPasswordHash);

    if (ret > 0)
    {
        LOG_DBG("Password changed successfully");
        resultJson["result"] = 1;
    }
    else
    {
        LOG_ERROR("Changing the password failed");
        resultJson["result"] = 0;
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onUserDelete(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idUser = req["idUser"].toString().toInt();
    LOG_DBG("Deleting user: %d", idUser);

    int ret = CDatabase::GetInstance()->DeleteUser(idUser);
    if (ret < 0)
    {
        LOG_ERROR("Could not delete user: %d", idUser);
        response["result"] = 0;
    }
    else
    {
        response["result"] = 1;
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onAddDevice(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idUser = req["idUser"].toString().toInt();
    int serialNumber = req["serialNumber"].toString().toInt();
    std::string currentLocation = req["currentLocation"].toString().toStdString();
    std::string deviceName = req["deviceName"].toString().toStdString();
    int firmwareVersion = req["firmwareVersion"].toString().toInt();

    int ret = CDatabase::GetInstance()->AddDevice(idUser, serialNumber, currentLocation, deviceName, firmwareVersion);
    if (ret > 0)
    {
        LOG_DBG("Adding device successful. idDev: %d", ret);
        response["result"] = 1;
        response["idDevice"] = ret;
    }
    else
    {
        LOG_ERROR("Device could not be added");
        response["result"] = 0;
        response["idDevice"] = -1;
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onListDevices(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();
    QJsonArray deviceArray;

    int idUser = req["idUser"].toString().toInt();

    QList<CDeviceRecord> list = CDatabase::GetInstance()->GetRegisteredDevicesList(idUser);

    if (list.empty())
    {
        LOG_ERROR("Could not find the requested user: %d", idUser);
        response["result"] = 0;
        request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
        return;
    }

    LOG_DBG("Requested device list for idUser: %d. Found %d devices", idUser, list.size());
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        QString deviceSerialized = QString::fromStdString((*iter).Serialize());
        QList<QString> deviceFields = deviceSerialized.split(',');
        QJsonObject singleDevice;
        for(int i=0; i<deviceFields.size(); ++i)
        {
            QList<QString> parts = deviceFields[i].split(':');
            singleDevice[parts[0]] = parts[1];
        }
        deviceArray.append(singleDevice);
    }
    response["result"] = 1;
    response["devices"] = deviceArray;
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onGetDeviceInfo(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int deviceId = req["idDevice"].toString().toInt();

    CDeviceRecord record = CDatabase::GetInstance()->GetDeviceInfo(deviceId);


    if (record.GetDeviceId() == -1)
    {
        LOG_ERROR("Devicd: %d not found", deviceId);
        response["result"] = 0;
        request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
        return;
    }

    LOG_DBG("Requested device info acquired");

    response["result"] = 1;
    response["idDevice"] = record.GetDeviceId();
    response["idUser"] = record.GetUserId();
    response["serialNumber"] = record.GetSerialNumber();
    response["currentLocation"] = record.GetLastLocation().c_str();
    response["deviceName"] = record.GetDeviceName().c_str();
    response["firmwareVersion"] = record.GetFirmwareVersion();
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onGetDeviceCurLocation(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idDevice = req["idDevice"].toString().toInt();

    CDeviceRecord devRecord = CDatabase::GetInstance()->GetDeviceInfo(idDevice);
    if (devRecord.GetDeviceId() == -1)
    {
        LOG_ERROR("idDevice: %d not found", idDevice);
        response["result"] = 0;
        request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
        return;
    }

    LOG_DBG("Requested device location is (LAT, LNG): %s", devRecord.GetLastLocation().c_str());
    response["result"] = 1;
    response["currentLocation"] = devRecord.GetLastLocation().c_str();
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onChangeDeviceName(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");

    int idDevice = req["idDevice"].toString().toInt();
    std::string devName = req["deviceName"].toString().toStdString();

   int result =  CDatabase::GetInstance()->ChangeDeviceName(idDevice, devName);

   if (!result)
   {
       response["result"] = 0;
       return;
   }

   response["result"] = 1;

}

void CHttpServer::m_onGetLatestFirmareVersion(qttp::HttpData& request)
{
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onUpdateFirmware(qttp::HttpData& request)
{
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onDeviceDelete(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idDevice = req["idDevice"].toString().toInt();
    LOG_DBG("Deleting device: %d", idDevice);

    int ret = CDatabase::GetInstance()->DeleteDevice(idDevice);
    if (ret < 0)
    {
        LOG_ERROR("Could not delete device: %d", idDevice);
        response["result"] = 0;
    }
    else
    {
        response["result"] = 1;
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onAddNewTrack(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idDevice = req["idDevice"].toString().toInt();
    int startDate = req["startDate"].toString().toInt();
    std::string startLocation = req["startLocation"].toString().toStdString();
    int endDate = req["endDate"].toString().toInt();
    std::string endLocation = req["endLocation"].toString().toStdString();
    int distance = req["distance"].toString().toInt();
    int manouverAssessment = req["manouverAssessment"].toString().toInt();

    int result = CDatabase::GetInstance()->AddTrack(idDevice, startDate, startLocation, endDate, endLocation, distance, manouverAssessment);

    if (result > 0)
    {
        LOG_DBG("Track added to database. TrackId: %d, deviceId: %d, startDate, %d", result, idDevice, startDate);
        response["result"] = 1;
        response["idTrack"] = result;
    }
    else
    {
        LOG_ERROR("Track could not be added to the database");
        response["result"] = 0;
        response["idTrack"] = -1;
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onListTracks(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idDevice = req["idDevice"].toString().toInt();

    QList<CTrackRecord> trackList = CDatabase::GetInstance()->GetTracksList(idDevice);
    LOG_DBG("Requested track list for idDevice: %d. Found %d tracks", idDevice, trackList.size());

    if (trackList.empty())
    {
        LOG_ERROR("Could not find the requested device.");
        response["result"] = 0;
        request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
        return;
    }

    QJsonArray trackArray;
    for (int iter = 0; iter < trackList.size(); ++iter)
    {
        CTrackRecord& record = static_cast<CTrackRecord&>(trackList[0]);
        QString trackSerialized = QString::fromStdString(record.Serialize());
        QList<QString> trackFields = trackSerialized.split(',');
        QJsonObject singleTrack;
        for(int i=0; i<trackFields.size(); ++i)
        {
            QList<QString> parts = trackFields[i].split(':');
            singleTrack[parts[0]] = parts[1];
        }
        trackArray.append(singleTrack);
    }

    response["result"] = 1;
    response["tracks"] = trackArray;
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onGetTrackInfo(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int userRequestingId = req["idUser"].toString().toInt();
    int requestedTrackId = req["idTrack"].toString().toInt();

    LOG_DBG("UserId: %d has requested track number: %d", userRequestingId, requestedTrackId);
    CTrackRecord record = CDatabase::GetInstance()->GetTrackInfo(requestedTrackId);
    if (record.GetTrackId() == -1)
    {
        LOG_ERROR("Track not found");
        response["result"] = 0;
    }
    else
    {
        response["result"] = 1;
        response["trackId"] = QString::number(record.GetTrackId());
        response["startDate"] =    QDateTime::fromSecsSinceEpoch(record.GetStartTimestmap()).toString("dd-MM-YYYY hh:mm:ss");
        response["startLocation"] = QString::fromStdString(record.GetStartLocation());
        response["endDate"] = QDateTime::fromSecsSinceEpoch(record.GetEndTimestamp()).toString("dd-MM-YYYY hh:mm:ss");
        response["endLocation"] = QString::fromStdString(record.GetEndLocation());
        response["distance"] = QString::number(record.GetDistance());
        response["manouverAssessment"] = QString::number(record.GetManeouverAssessment());
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onGetTrackDetails(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int requestedTrackId = req["idTrack"].toString().toInt();

    QList<CSampleRecord> sampleList = CDatabase::GetInstance()->GetTrackDetails(requestedTrackId);

    if (sampleList.empty())
    {
        response["result"] = 0;
        request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
        return;
    }

    QJsonArray sampleArray;
    for (auto iter = sampleList.begin(); iter != sampleList.end(); ++iter)
    {
        CSampleRecord& record = *iter;
        QString sampleSerialized = QString::fromStdString(record.Serialize());
        QList<QString> sampleFields = sampleSerialized.split(',');
        QJsonObject singleSample;
        for(int i=0; i<sampleFields.size(); ++i)
        {
            QList<QString> parts = sampleFields[i].split(':');
            singleSample[parts[0]] = parts[1];
        }
        sampleArray.append(singleSample);
    }

    response["result"] = 1;
    response["samples"] = sampleArray;
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onEndTrack(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idTrack = req["idTrack"].toString().toInt();
    int endDate = req["endDate"].toString().toInt();
    std::string endLocation = req["endLocation"].toString().toStdString();
    int distance = req["distance"].toString().toInt();
    int manouverAssessment = req["manouverAssessment"].toString().toInt();

    int ret = CDatabase::GetInstance()->EndTrack(idTrack, endDate, endLocation, distance, manouverAssessment);

    if (ret)
    {
        response["result"] = 1;
    }
    else
    {
        response["result"] = 0;
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

void CHttpServer::m_onAddNewTrackSample(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idTrack = req["idTrack"].toString().toInt();
    int timestamp = req["timestamp"].toString().toInt();
    std::string coordinates = req["coordinates"].toString().toStdString();
    int speed = req["speed"].toString().toInt();
    int acceleration = req["acceleration"].toString().toInt();
    int azimuth = req["azimuth"].toString().toInt();

    int ret = CDatabase::GetInstance()->AddTrackSample(idTrack, timestamp, coordinates, speed, acceleration, azimuth);

    response["result"] = 1;
    // If sample added correctly then update the last known location of the device
//    if (ret > 0)
//    {
//        CTrackRecord track = CDatabase::GetInstance()->GetTrackInfo(idTrack);
//        CDatabase::GetInstance()->UpdateDeviceLocation(track.GetDeviceId(), coordinates);
//    }
}

void CHttpServer::m_onTrackDelete(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idTrack = req["idTrack"].toString().toInt();
    LOG_DBG("Deleting track: %d", idTrack);

    int ret = CDatabase::GetInstance()->DeleteTrack(idTrack);
    if (ret > 0)
    {
        response["result"] = 1;
    }
    else
    {
        LOG_ERROR("Could not delete track: %d", idTrack);
        response["result"] = 0;
    }
    request.getResponse().setHeader("Access-Control-Allow-Origin", "*");
}

