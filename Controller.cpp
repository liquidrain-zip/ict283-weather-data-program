#include "Controller.h"
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::ofstream;
using std::abs;
using std::stoi;
using std::stof;
using std::getline;

Vector<string> Controller::splitString(const string& s, char delimiter)
{
    Vector<string> tokens;
    string token;
    stringstream tokenStream(s);
    int inc = 0;
    while (getline(tokenStream, token, delimiter))
    {
        tokens.Insert(token, inc);
        inc++;
    }
    return tokens;
}

int Controller::LoadRecords(WeatherRecords & weatherRecords, const string & filename)
{
    int recordsLoaded = 0;
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return -1;
    }

    string headerLine;
    if (!getline(inFile, headerLine))
    {
        cerr << "Error: Could not read header line from file " << filename << endl;
        inFile.close();
        return -1;
    }

    Vector<string> headers = splitString(headerLine, CSV_DELIMITER);
    int dateTimeIndex = -1;
    int windSpeedIndex = -1;
    int tempIndex = -1;
    int solarRadIndex = -1;

    for (int i = 0; i < headers.getCount(); ++i)
    {
        string header = headers[i];

        if (header == DATE_TIME_COLUMN)
        {
            dateTimeIndex = i;
        }

        if (header == WIND_SPEED_COLUMN)
        {
            windSpeedIndex = i;
        }

        if (header == AIR_TEMP_COLUMN)
        {
            tempIndex = i;
        }

        if (header == SOLAR_RAD_COLUMN)
        {
            solarRadIndex = i;
        }
    }

    // --- 2. Validation ---
    if (dateTimeIndex == -1 || windSpeedIndex == -1 || tempIndex == -1 || solarRadIndex == -1)
    {
        cerr << "Error: One or more required columns ('WAST', 'S', 'T', 'SR') not found in the header." << endl;
        inFile.close();
        return -1;
    }

    // --- 3. Process Data Lines ---
    string line;
    while(getline(inFile, line))
    {
        Vector<string> tokens = splitString(line, CSV_DELIMITER);
        WeatherRecord record;

        // Skip lines that don't have enough data
        if (tokens.getCount() < headers.getCount())
        {
            continue;
        }

        // --- A. Parse Date/Time (D/M/Y H:M - 24hr format) ---
        string dateTimeStr = tokens[dateTimeIndex];

        // assuming date time separated by a space
        size_t spacePos = dateTimeStr.find_first_of(' ');
        if (spacePos == string::npos)
            continue; // Skip if no space found

        string datePart = dateTimeStr.substr(0, spacePos);
        string timePart = dateTimeStr.substr(spacePos + 1); // Skip the space

        // 1. Parse Date (D/M/Y)
        stringstream dateStream(datePart);
        string tempStr;
        int day, month, year;

        // Get Day, Month, Year
        getline(dateStream, tempStr, DATE_DELIMITER);
        day = stoi(tempStr);
        getline(dateStream, tempStr, DATE_DELIMITER);
        month = stoi(tempStr);
        getline(dateStream, tempStr);
        year = stoi(tempStr);
        Date recordDate(day, month, year);
        record.SetDate(recordDate);

        // 2. Parse Time (H:M)
        stringstream timeStream(timePart);
        int hour, minute, second;

        // Get Hour, Minute
        getline(timeStream, tempStr, TIME_DELIMITER);
        hour = stoi(tempStr);
        getline(timeStream, tempStr, TIME_DELIMITER);
        minute = stoi(tempStr);
        getline(timeStream, tempStr);
        second = stoi(tempStr);

        Time recordTime(hour, minute, second);
        record.SetTime(recordTime);

        // --- B. Parse Data Values ---
        try
        {
            // Wind Speed (S): Assumed in m/s, converted to km/h (multiplying by 3.6)
            record.SetWindSpeed(std::stof(tokens[windSpeedIndex]) * 3.6f);

            // Temperature (T)
            record.SetTemperature(std::stof(tokens[tempIndex]));

            // Solar Radiation (SR)
            // Record taken 10min apart
            double time_step = 10.0 / 60.0;
            // Convert power (W/m2) to energy (Wh/m2) by multiplying by the time step
            double srEnergy = std::stof(tokens[solarRadIndex]) * time_step;
            // Convert Wh/m2 to kWh/m2
            double srEnergyK = srEnergy / 1000.0;
            record.SetSolarRadiation(srEnergyK);
        }
        catch (const std::invalid_argument& e)
        {
            cerr << "Warning: Skipped record due to non-numeric data fields: " << line << endl;
            continue;
        }
        catch (const std::out_of_range& e)
        {
            cerr << "Warning: Skipped record due to numeric value out of range: " << line << endl;
            continue;
        }

        // --- C. Store Record ---
        weatherRecords.Insert(record, recordsLoaded);
        recordsLoaded++;
    }

    inFile.close();
    return recordsLoaded;
}

int Controller::LoadAllRecordsFromSourceFile(WeatherRecords& weatherRecords, const string& sourceFilename)
{
    ifstream sourceFile(sourceFilename);
    if (!sourceFile.is_open())
    {
        cerr << "Error: Could not open source file: " << sourceFilename << endl;
        return -1;
    }

    string filename;
    int totalRecordsLoaded = 0;
    int filesProcessed = 0;

    // read filenames line by line from the source file
    while (getline(sourceFile, filename))
    {
        cout << "Loading data from: " << filename << "... ";

        // call LoadRecords function for the current file
        int recordsFromFile = LoadRecords(weatherRecords, "data/" + filename);

        if (recordsFromFile >= 0)
        {
            totalRecordsLoaded += recordsFromFile;
            filesProcessed++;
            cout << recordsFromFile << " records loaded." << endl;
        }
        else
        {
            cerr << "ERROR: Failed to load data from " << filename << ". Skipping file." << endl;
        }
    }

    sourceFile.close();

    if (filesProcessed == 0 && totalRecordsLoaded == 0)
    {
        cout << "Finished loading. Found no valid data files or records to load." << endl;
    }
    else
    {
        cout << "\nFinished loading all files. Total records loaded: " << totalRecordsLoaded << endl;
    }

    return totalRecordsLoaded;
}
