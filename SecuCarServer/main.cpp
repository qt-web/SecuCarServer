#include <QCoreApplication>
#include "myhttpserver.h"
#include "database.h"
#include <QSqlQuery>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    CHttpServer* httpServer = CHttpServer::GetInstance();
//    httpServer->Initialize();
//    httpServer->Start();
//    QPluginLoader loader;
//      loader.setFileName("/home/konrad/IDEs/Qt/5.8/gcc_64/plugins/sqldrivers/libqsqlmysql.so");
//      qDebug() << "PluginLoader worked =" << loader.load();
//      qDebug() << "Plugin Loader error=" << loader.errorString();

//      qDebug() << QCoreApplication::libraryPaths();
//      QCoreApplication::addLibraryPath("/home/konrad/IDEs/Qt/5.8/gcc_64/plugins/sqldrivers/libqsqlmysql.so");
//      qDebug() << QSqlDatabase::drivers();

    CDatabase* db = CDatabase::GetInstance();
    QSqlQuery ret = db->Select("users", "*");
    while (ret.next())
    {
        LOG_DBG("%s ", ret.value("name").toString().toStdString().c_str());
    }

    return a.exec();
}
