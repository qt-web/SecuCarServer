#include <QCoreApplication>
#include "myhttpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CHttpServer* httpServer = CHttpServer::GetInstance();
    httpServer->Initialize();
    httpServer->Start();


    return a.exec();
}
