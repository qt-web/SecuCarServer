#include <QCoreApplication>
#include "myhttpserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    CHttpServer* httpServer = CHttpServer::GetInstance();
//    httpServer->Initialize();
//    httpServer->Start();
    CDatabase* db = CDatabase::GetInstance();
    db->Select("USERS", "*");

    return a.exec();
}
