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
    m_addActionToRegisterUser();
    m_addActionToGetUserData();
    m_addActionToChangeUserData();
    m_addActionToChangePassword();

    // Device's actions
    m_addActionToAddDevice();
    m_addActionToGetDevicesList();
    m_addActionToGetDeviceInfo();
    m_addActionToGetDeviceCurLocation();
    m_addActionToGetTrackInfo();
    m_addActionToGetTrackDetails();

    m_addActionToAddNewTrack();
    m_addActionToAddNewTrackSample();
    m_addActionToGetLatestFirmwareVersion();
    m_addActionToUpdateFirmware();
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
}

void CHttpServer::m_addActionToLogin()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Login", m_onLogin);
    action->registerRoute("POST", "Login", "/login");
}

void CHttpServer::m_addActionToRegisterUser()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Register", m_onRegisterUser);
    action->registerRoute("GET", "Register", "/register");
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

void CHttpServer::m_addActionToGetTrackInfo()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetTrack", m_onGetTrackInfo);
    action->registerRoute("GET", "GetTrackInfo", "/get_track_info");
}

void CHttpServer::m_addActionToGetTrackDetails()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetTrack", m_onGetTrackDetails);
    action->registerRoute("GET", "GetTrackDetails", "/get_track_details");
}

void CHttpServer::m_addActionToAddNewTrack()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("AddNewTrack", m_onAddNewTrack);
    action->registerRoute("GET", "AddNewTrack", "/add_track");
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

void CHttpServer::m_onOptions(qttp::HttpData& request)
{
    LOG_DBG("Login OPTIONS request received :%s", QString(QJsonDocument(request.getRequest().getJson()).toJson(QJsonDocument::Compact)).toStdString().c_str());
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
    LOG_DBG("Login actual request received");
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
}

void CHttpServer::m_onRegisterUser(qttp::HttpData& request)
{
    const QJsonObject& requestJSON = request.getRequest().getJson();

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
    std::string passwordHash = requestJSON["passwordHash"].toString().toStdString();

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

    QJsonObject& response = request.getResponse().getJson();
    if (ret >= 0)
    {
        LOG_DBG("User successfully registered");
        response["result"] = 1;
    }
    else
    {
        LOG_ERROR("User registration failure");
        response["result"] = 0;
    }
}

void CHttpServer::m_onGetUserData(qttp::HttpData &request)
{
    const QJsonObject& requestJson = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idUser = requestJson["idUser"].toInt();
    CUserRecord rec = CDatabase::GetInstance()->GetUserData(idUser);

    if (rec.GetUserId() == -1)
    {
        LOG_ERROR("No user found with idUser: %d", idUser);
        response["result"] = 0;
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
        LOG_DBG("Adding device successful");
        response["result"] = 1;
    }
    else
    {
        LOG_ERROR("Device could not be added");
        response["result"] = 0;
    }
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
        return;
    }

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
}

void CHttpServer::m_onGetDeviceInfo(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int deviceId = req["idDevice"].toString().toInt();
    QList<Record> recordList = CDeviceArray::GetInstance()->Select(deviceId);

    if (recordList.empty())
    {
        LOG_ERROR("Could not find requested device");
        response["result"] = 0;
    }
    LOG_DBG("Received device info for idDevice: %d", deviceId);
    CDeviceRecord record = static_cast<CDeviceRecord&>(recordList[0]);

    response["result"] = 1;
    response["idDevice"] = record.GetDeviceId();
    response["idUser"] = record.GetUserId();
    response["serialNumber"] = record.GetSerialNumber();
    response["currentLocation"] = record.GetLastLocation().c_str();
    response["deviceName"] = record.GetDeviceName().c_str();
    response["firmwareVersion"] = record.GetFirmwareVersion();

}

void CHttpServer::m_onGetDeviceCurLocation(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idDevice = req["idDevice"].toString().toInt();

    QList<Record> recordlist = CDeviceArray::GetInstance()->Select(idDevice);

    if (recordlist.empty())
    {
        LOG_ERROR("Could not find the requested device.");
        response["result"] = 0;
        return;
    }

    CDeviceRecord devRecord = static_cast<CDeviceRecord&>(recordlist[0]);
    LOG_DBG("Requested device location is: %d", devRecord.GetLastLocation().c_str());


    response["result"] = 1;
    response["currentLocation"] = devRecord.GetLastLocation().c_str();
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

    int result = CDatabase::AddTrack(idDevice, startDate, startLocation, endDate, endLocation, distance, manouverAssessment);

    if (result > 0)
    {
        LOG_DBG("Track added to database. TrackId: %d, deviceId: %d, startDate, %d", result, idDevice, startDate);
        response["result"] = 1;
    }
    else
    {
        LOG_ERROR("Track could not be added to the database");
        response["result"] = 0;
    }
}

void CHttpServer::m_onListTracks(qttp::HttpData &request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int idDevice = req["idDevice"].toString().toInt();

    QList<CTrackRecord> trackList = CDatabase::GetTracksList(idDevice);
    if (trackList.empty())
    {
        LOG_ERROR("Could not find the requested device.");
        response["result"] = 0;
        return;
    }

    QJsonArray trackArray;
    for (auto iter = trackList.begin(); iter != trackList.end(); ++iter)
    {
        QString trackSerialized = QString::fromStdString((*iter).Serialize());
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
    response["devices"] = trackArray;
}


void CHttpServer::m_onGetTrackInfo(qttp::HttpData& request)
{
    const QJsonObject& req = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    int userRequestingId = req["userId"].toString().toInt();
    int requestedTrackId = req["trackId"].toString().toInt();

    LOG_DBG("UserId: %d has requested track number: %d", userRequestingId, requestedTrackId);
    QList<Record> list = (QList<Record>)CTrackArray::GetInstance()->Select(requestedTrackId);
    if (list.empty())
    {
        LOG_ERROR("Track not found.");
        response["result"] = 0;
    }
    else
    {
        CTrackRecord& record  = (CTrackRecord&)list[0];
        response["result"] = 1;
        response["trackId"] = QString::number(record.GetTrackId());
        response["startDate"] =    QDateTime::fromSecsSinceEpoch(record.GetStartTimestmap()).toString("dd-MM-YYYY hh:mm:ss");
        response["startLocation"] = QString::fromStdString(record.GetStartLocation());
        response["endDate"] = QDateTime::fromSecsSinceEpoch(record.GetEndTimestamp()).toString("dd-MM-YYYY hh:mm:ss");
        response["endLocation"] = QString::fromStdString(record.GetEndLocation());
        response["distance"] = QString::number(record.GetDistance());
        response["manouverAssessment"] = QString::number(record.GetManeouverAssessment());
    }
}

void CHttpServer::m_onGetTrackDetails(qttp::HttpData &request)
{

}

void CHttpServer::m_onEndTrack(qttp::HttpData &request)
{

}

void CHttpServer::m_onAddNewTrackSample(qttp::HttpData& request)
{

}

void CHttpServer::m_onGetLatestFirmareVersion(qttp::HttpData& request)
{

}

void CHttpServer::m_onUpdateFirmware(qttp::HttpData& request)
{

}
