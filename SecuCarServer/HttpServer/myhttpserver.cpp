#include "myhttpserver.h"
#include <httpserver.h>
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
    m_addActionToLogin();
    m_addActionToRegisterUser();
    m_addActionToGetUserData();
    m_addActionToChangeUserData();
    m_addActionToChangePassword();

    // Device's actions
    m_addActionToAddDevice();
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

void CHttpServer::m_addActionToLogin()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Login", m_onLogin);
    action->registerRoute("GET", "Login", "/login");
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


void CHttpServer::m_onLogin(qttp::HttpData& request)
{
    const QJsonObject& requestJSON = request.getRequest().getJson();
    QJsonObject& response = request.getResponse().getJson();

    std::string username = requestJSON["username"].toString().toStdString();
    std::string passwordHash = requestJSON["password"].toString().toStdString();

    int ret = CDatabase::GetInstance()->Login(username, passwordHash);

    if (ret >= 0)
    {
        LOG_DBG("User successfully %s logged in", username.c_str());
        response["idUser"] = ret;
    }
    else
    {
        LOG_ERROR("User %s login failure", username.c_str());
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
    int idUser = requestJson["idUser"].toInt();

    CUserRecord rec = CDatabase::GetInstance()->GetUserData(idUser);

    if (rec.GetUserId() == -1)
    {
        LOG_ERROR("No user found with idUser: %d", idUser);

    }
    else
    {
        LOG_DBG("Request to read user data");
    }


    QJsonObject& response = request.getResponse().getJson();

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

    int idUser = requestJson["idUser"].toString().toInt();
    CUserRecord rec = CDatabase::GetInstance()->GetUserData(idUser);
    if (rec.GetUserId() == -1)
    {
        LOG_ERROR("User not found. idUser: %d", idUser);
        return;
    }

    std::string username = rec.GetUserName();
    std::string name = requestJson["name"].toString().toStdString();
    std::string surname = requestJson["surname"].toString().toStdString();
    std::string email = requestJson["email"].toString().toStdString();
    int telephone = requestJson["telephone"].toString().toInt();
    std::string city = requestJson["city"].toString().toStdString();
    std::string street = requestJson["street"].toString().toStdString();
    int homeNumber = requestJson["homeNumber"].toString().toInt();
    int flatNumber = requestJson["flatNumber"].toString().toInt();
    std::string postalCode = requestJson["postalCode"].toString().toStdString();
    std::string passwordHash = rec.GetPasswordHash();

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

    QJsonObject& response = request.getResponse().getJson();
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

}

void CHttpServer::m_onGetDeviceInfo(qttp::HttpData& request)
{

}

void CHttpServer::m_onGetDeviceCurLocation(qttp::HttpData& request)
{

}

void CHttpServer::m_onGetTrackInfo(qttp::HttpData& request)
{
    int userRequestingId = request.getRequest().getJson()["userId"].toString().toInt();
    int requestedTrackId = request.getRequest().getJson()["trackId"].toString().toInt();
    LOG_DBG("UserId: %d has requested track number: %d", userRequestingId, requestedTrackId);
    QList<Record> list = (QList<Record>)CTrackArray::GetInstance()->Select(requestedTrackId);

    if (list.empty())
    {
        LOG_ERROR("Track not found.");

    }
    else
    {
        CTrackRecord& record  = (CTrackRecord&)list[0];
        QJsonObject response = request.getResponse().getJson();
        QString responseData =  QString::number(record.GetTrackId()) + ";" +
                                QDateTime::fromSecsSinceEpoch(record.GetStartTimestmap()).toString("dd-MM-YYYY hh:mm:ss") + ";" +
                                QString::fromStdString(record.GetStartLocation()) + ";" +
                                QDateTime::fromSecsSinceEpoch(record.GetEndTimestamp()).toString("dd-MM-YYYY hh:mm:ss") + ";" +
                                QString::fromStdString(record.GetEndLocation()) + ";" +
                                QString::number(record.GetDistance()) + ";" +
                                QString::number(record.GetManeouverAssessment()) + ";";

        response["track"] = responseData;

    }
}

void CHttpServer::m_onGetTrackDetails(qttp::HttpData &request)
{

}

void CHttpServer::m_onAddNewTrack(qttp::HttpData& request)
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

