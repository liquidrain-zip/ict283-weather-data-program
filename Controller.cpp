#include "Controller.h"

#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>

using std::ifstream;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

void Controller::DisplayMenu()
{
    cout << "\nWind Data Analysis Menu\n";
    cout << "-------------------------\n";
    cout << "1. Display number of wind records\n";
    cout << "2. Display average wind speed\n";
    cout << "3. Display standard deviation of wind speed\n";
    cout << "4. Find records near average speed\n";
    cout << "5. Exit\n";
    cout << "-------------------------\n";
}

void Controller::ProcessMenuChoice(int choice, const WindLogType& windRecords)
{
    double averageSpeed, stdDev;
    const double speedToleranceKmH = 2.0;
    averageSpeed = CalculateAverageWindSpeed(windRecords); // Need average to find SD and near records

    switch (choice) {
        case 1:
            cout << "Number of wind speed values (N): " << windRecords.getCount() << endl;
            break;
        case 2:
            cout << "The mean of the wind speed values: " << fixed << setprecision(2) << averageSpeed << " km/h" << endl;
            break;
        case 3:
            stdDev = CalculateWindSpeedStandardDeviation(windRecords, averageSpeed);
            cout << "The sample standard deviation: " << fixed << setprecision(2) << stdDev << " km/h" << endl;
            break;
        case 4:
            PrintRecordsNearAverageSpeed(windRecords, averageSpeed, speedToleranceKmH);
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
    }
}

Vector<string> Controller::splitString(const string& s, char delimiter)
{
    Vector<string> tokens;
    string token;
    stringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.insert(token);
    }
    return tokens;
}

int Controller::LoadRecords(WindLogType & windRecords, const string & filename)
{
    int count = 0;
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return -1;
    }

    string headerLine;
    if (!getline(inFile, headerLine)) {
        cerr << "Error: Could not read header line from file " << filename << endl;
        inFile.close();
        return -1;
    }

    // to get index of Columns 'S'
    Vector<string> headers = splitString(headerLine, CSV_DELIMITER);

    int windSpeedColumnIndex = -1;
    for (int i = 0; i < headers.getCount(); ++i) {
        if (headers[i] == "S") {
            windSpeedColumnIndex = i;
            break;
        }
    }

    if (windSpeedColumnIndex == -1) {
        cerr << "Error: Could not find 'S' column header in file " << filename << endl;
        inFile.close();
        return -1;
    }

    string line;
    string tempStr;
    while(getline(inFile, line))
    {
        stringstream ss(line);
        WindRecType windRecord;
        int day, month, year;
        int hour, minute, second;
        float windSpeed;

        // Column 0: Date and Time
        getline(ss, tempStr, CSV_DELIMITER);
        stringstream dateTimeStream(tempStr);

        // Parse Date and Time... (Date and Time parsing code remains the same)
        getline(dateTimeStream, tempStr, DATE_DELIMITER);
        day = stoi(tempStr);
        getline(dateTimeStream, tempStr, DATE_DELIMITER);
        month = stoi(tempStr);
        getline(dateTimeStream, tempStr, ' ');
        year = stoi(tempStr);
        windRecord.m_date.SetDay(day);
        windRecord.m_date.SetMonth(month);
        windRecord.m_date.SetYear(year);

        getline(dateTimeStream, tempStr, TIME_DELIMITER);
        hour = stoi(tempStr);
        getline(dateTimeStream, tempStr, TIME_DELIMITER);
        minute = stoi(tempStr);
        getline(dateTimeStream, tempStr);
        second = stoi(tempStr);
        windRecord.m_time.SetHour(hour);
        windRecord.m_time.SetMinute(minute);
        windRecord.m_time.SetSecond(second);

        for(int i = 0; i < windSpeedColumnIndex; i++) {
            getline(ss, tempStr, CSV_DELIMITER);
        }
        windSpeed = stof(tempStr);
        windRecord.m_speed = windSpeed * 3.6;

        // set record to vector
        windRecords.insert(windRecord);
        count ++;
    }

    inFile.close();
    return count;
}

double Controller::CalculateAverageWindSpeed(const WindLogType& windData)
{
    if (windData.getCount() == 0) {
        return 0.0;
    }

    double sumSpeeds = 0.0;
    for (int i = 0; i < windData.getCount(); i++) {
        sumSpeeds += windData[i].m_speed;
    }
    return sumSpeeds / windData.getCount();
}

double Controller::CalculateWindSpeedStandardDeviation(const WindLogType& windData, double averageSpeed)
{
    if (windData.getCount() < 2) {
        return 0.0;
    }

    double sumSquaredDifferences = 0.0;
    for (int i = 0; i < windData.getCount(); ++i) {
        sumSquaredDifferences += pow(windData[i].m_speed - averageSpeed, 2);
    }

    return sqrt(sumSquaredDifferences / (windData.getCount() - 1));
}

void Controller::PrintRecordsNearAverageSpeed(const WindLogType& windData, double averageSpeed, double tolerance)
{
    cout << "\nRecords with wind speed near average (" << fixed << setprecision(2)
    << averageSpeed << " km/h +/- " << tolerance << " km/h):\n";

    bool foundRecord = false;
    for (int i = 0; i < windData.getCount(); i++) {
        if (abs(windData[i].m_speed - averageSpeed) <= tolerance) {
            cout << "  Date: " << windData[i].m_date << ", Time: "
            << windData[i].m_time << ", Speed: " << fixed
            << setprecision(2) << windData[i].m_speed << " km/h\n";
            foundRecord = true;
        }
    }
    if (!foundRecord) {
        cout << "  No records found with wind speed near the average.\n";
    }
}
