#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "Date.h"
#include "Time.h"
#include "Vector.h"
#include "WeatherRecord.h"
#include "WeatherDatabase.h"
#include <string>

using std::string;

const char CSV_DELIMITER = ',';
const char DATE_DELIMITER = '/';
const char TIME_DELIMITER = ':';
const string DATE_TIME_COLUMN = "WAST";
const string WIND_SPEED_COLUMN = "S";
const string AIR_TEMP_COLUMN = "T";
const string SOLAR_RAD_COLUMN = "SR";

const string monthNames[] =
{
    "Invalid Month",
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

typedef WeatherDatabase WeatherRecords;


#endif // TYPES_H_INCLUDED
