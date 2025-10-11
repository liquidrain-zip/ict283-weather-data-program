#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <string>

#include "Date.h"
#include "Time.h"
#include "Vector.h"

const char CSV_DELIMITER = ',';
const char DATE_DELIMITER = '/';
const char TIME_DELIMITER = ':';

typedef struct
{
    Date m_date = Date();
    Time m_time = Time();
    float m_speed = 0.0;
} WindRecType;

typedef Vector<WindRecType> WindLogType;

using std::string;

/**
 * @class Controller
 * @brief Declaration of the Controller class.
 *
 * This file defines the Controller class, which displays a menu,
 * data processing and printing out
 */

class Controller
{
public:
    int LoadRecords(WindLogType & windRecords, const string & filename);
    double CalculateAverageWindSpeed(const WindLogType& windData);
    double CalculateWindSpeedStandardDeviation(const WindLogType& windData, double averageSpeed);
    void PrintRecordsNearAverageSpeed(const WindLogType& windData, double averageSpeed, double tolerance);
    void DisplayMenu();
    void ProcessMenuChoice(int choice, const WindLogType& windRecords);
    Vector<string> splitString(const string& s, char delimiter);

private:

};

#endif // CONTROLLER_H_INCLUDED
