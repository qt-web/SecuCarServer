#include <QCoreApplication>
#include "myhttpserver.h"
#include "databasedriver.h"
#include "userarray.h"
#include "userrecord.h"
#include <QSqlQuery>
#include "logger.h"
#include "devicearray.h"
#include "devicerecord.h"
#include "trackarray.h"
#include "trackrecord.h"
#include "samplearray.h"
#include "samplerecord.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CDatabaseDriver* databaseDriver = CDatabaseDriver::GetInstance();
    CUserArray* userArray = CUserArray::GetInstance();
    CDeviceArray* deviceArray = CDeviceArray::GetInstance();
    CTrackArray* trackArray = CTrackArray::GetInstance();
    CSampleArray* sampleArray = CSampleArray::GetInstance();

    CHttpServer* httpServer = CHttpServer::GetInstance();
    httpServer->Initialize();
    httpServer->Start();

    return a.exec();
}
