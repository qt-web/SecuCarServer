#include <QCoreApplication>
#include "myhttpserver.h"
#include "database.h"
#include "userarray.h"
#include "userrecord.h"
#include <QSqlQuery>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CDatabase* db = CDatabase::GetInstance();
    CUserArray* ua = CUserArray::GetInstance();

    CUserRecord record(0, "scyphio122", "Konrad", "Traczyk", "Warszawa", "Egejska", 10, 13, "02-764", "0");
    ua->Insert(record);
    ua->Select(0);
    ua->Select("scyphio122");

    return a.exec();
}
