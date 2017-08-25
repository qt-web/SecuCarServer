#include "database.h"
#include "databasedriver.h"
#include "userarray.h"
#include "devicearray.h"
#include "trackarray.h"
#include "samplearray.h"
#include "userrecord.h"
#include "devicerecord.h"
#include "trackrecord.h"
#include "samplerecord.h"

CDatabase::CDatabase()
{
    CDatabaseDriver* databaseDriver = CDatabaseDriver::GetInstance();
    CUserArray* userArray = CUserArray::GetInstance();
    CDeviceArray* deviceArray = CDeviceArray::GetInstance();
    CTrackArray* trackArray = CTrackArray::GetInstance();
    CSampleArray* sampleArray = CSampleArray::GetInstance();
}
