#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "Date.h"
#include "Time.h"
#include "Vector.h"
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

/**
 * @brief Structure to hold a single weather record entry.
 */
typedef struct
{
    Date m_date = Date();
    Time m_time = Time();
    float m_windSpeed = 0.0;
    float m_temperature  = 0.0;
    float m_solarRadiation  = 0.0;
} WeatherRecord;

/**
 * @brief The primary data structure for storing all weather records.
 * Implemented as a Vector of WeatherRecord.
 */
typedef Vector<WeatherRecord> WeatherRecords;

#endif // TYPES_H_INCLUDED
