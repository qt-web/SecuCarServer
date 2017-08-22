#include "myhttpserver.h"
#include <httpserver.h>

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

    m_addActionToLogin();
    m_addActionToRegisterUser();
    m_addActionToAddDevice();
    m_addActionToGetDeviceInfo();
    m_addActionToGetDeviceCurLocation();
    m_addActionToGetTrack();

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
    action->registerRoute("POST", "Login", "/login");
}

void CHttpServer::m_addActionToRegisterUser()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("Register", m_onLogin);
    action->registerRoute("POST", "Register", "/register");
}

void CHttpServer::m_addActionToAddDevice()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("AddDevice", m_onLogin);
    action->registerRoute("GET", "AddDevice", "/add_device");
}

void CHttpServer::m_addActionToGetDeviceInfo()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetDeviceInfo", m_onLogin);
    action->registerRoute("GET", "GetDeviceInfo", "/get_device_info");
}

void CHttpServer::m_addActionToGetDeviceCurLocation()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetCurrentDevLocation", m_onLogin);
    action->registerRoute("GET", "GetCurrentDevLocation", "/get_dev_location");
}

void CHttpServer::m_addActionToGetTrack()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetTrack", m_onLogin);
    action->registerRoute("GET", "GetTrack", "/get_track");
}

void CHttpServer::m_addActionToAddNewTrack()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("AddNewTrack", m_onLogin);
    action->registerRoute("GET", "AddNewTrack", "/add_track");
}

void CHttpServer::m_addActionToAddNewTrackSample()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("AddNewTrackSample", m_onLogin);
    action->registerRoute("GET", "AddNewTrackSample", "/add_track_sample");
}

void CHttpServer::m_addActionToGetLatestFirmwareVersion()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("GetLatestFirmwareVersion", m_onLogin);
    action->registerRoute("GET", "GetLatestFirmwareVersion", "/get_latest_firmware_version");
}

void CHttpServer::m_addActionToUpdateFirmware()
{
    auto action = m_qttpServerGetInstance();
    action->createAction("UpdateFirmware", m_onLogin);
    action->registerRoute("GET", "UpdateFirmware", "/update_firmware");
}


void CHttpServer::m_onLogin(qttp::HttpData& request)
{

}

void CHttpServer::m_onRegisterUser(qttp::HttpData& request)
{

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

void CHttpServer::m_onGetTrack(qttp::HttpData& request)
{

}

void CHttpServer::m_onAddNewTrack(qttp::HttpData& request)
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

