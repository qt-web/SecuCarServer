#include <QCoreApplication>
#include "myhttpserver.h"
#include "databasedriver.h"
#include "userarray.h"
#include "userrecord.h"
#include <QSqlQuery>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CDatabaseDriver* db = CDatabaseDriver::GetInstance();
    CUserArray* ua = CUserArray::GetInstance();

    CUserRecord record(0, "scyphio122", "Konrad", "Traczyk", "Warszawa", "Egejska", 10, 13, "02-764", "0");
    ua->Insert(record);
    ua->Select(0);
    record.SetCity("Parzyce");
    ua->Update(record);
    ua->Select("scyphio122");
    ua->Delete(0);
    ua->Select(0);

    return a.exec();
}
