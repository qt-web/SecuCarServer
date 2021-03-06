#include <QCoreApplication>
#include "myhttpserver.h"
#include <QSqlQuery>
#include "logger.h"
#include "database.h"
#include "databasedriver.h"
#include "userarray.h"
#include "devicearray.h"
#include "trackarray.h"
#include "samplearray.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    CDatabaseDriver::s_applicationStartPath = argv[0];
    CDatabase::GetInstance();
    CUserArray::GetInstance();
    CDeviceArray::GetInstance();
    CTrackArray::GetInstance();
    CSampleArray::GetInstance();

    CHttpServer* httpServer = CHttpServer::GetInstance();
    httpServer->Initialize();
    httpServer->Start();

    return a.exec();
}
