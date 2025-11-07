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

void Controller::DisplayMenu()
{
    cout << "\nWeather Data Analysis Menu\n";
    cout << "-------------------------\n";
    cout << "1. Average wind speed and sample standard deviation (specific month and year)\n";
    cout << "2. Average ambient air temperature and sample standard deviation (each month of a year)\n";
    cout << "3. Calculate sPCC result for S_T, S_R & T_R (specific month for all years)\n";
    cout << "4. Output monthly summary to file (WindTempSolar.csv)\n";
    cout << "5. Exit\n";
    cout << "-------------------------\n";
}

void Controller::ProcessMenuChoice(int choice, const WeatherRecords& weatherRecords)
{
    int month = -1, year = -1;

    switch (choice)
    {
    case 1:
        cout << "Enter the month (1-12): ";
        if (!(cin >> month) || month < 1 || month > 12)
        {
            cout << "Invalid month. Returning to menu.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        displayAverageWindSpeedAndStdev(month, year, weatherRecords);
        break;
    case 2:
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        displayMonthlyTemperatureAveragesAndStdev(year, weatherRecords);
        break;
    case 3:
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        displayMonthlyTotalSolarRadiation(year, weatherRecords);
        break;
    case 4:
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        outputMonthlyWindTempSolarSummary(year, weatherRecords);
        break;
    case 5:
        cout << "Exiting program.\n";
        break;
    default:
        cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

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
            record.SetSolarRadiation(std::stof(tokens[solarRadIndex]));
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

WeatherRecords Controller::getRecordsForMonthAndYear(int month, int year, const WeatherRecords& weatherRecords) const
{
    WeatherRecords filteredRecords;
    int insertIndex = 0;

    if (month < 1 || month > 12)
    {
        return filteredRecords;
    }

    for (int i = 0; i < weatherRecords.getCount(); ++i)
    {
        const WeatherRecord& record = weatherRecords[i];
        const Date& recordDate = record.GetDate();
        if (recordDate.GetMonth() == month && recordDate.GetYear() == year)
        {
            filteredRecords.Insert(record, insertIndex);
            insertIndex++;
        }
    }

    return filteredRecords;
}

// Menu Option 1
void Controller::displayAverageWindSpeedAndStdev(int month, int year, const WeatherRecords& weatherRecords) const
{
    WeatherRecords filtered = getRecordsForMonthAndYear(month, year, weatherRecords);

    cout << monthNames[month] << " " << year << ": ";

    if (filtered.getCount() == 0)
    {
        cout << "No Data" << endl;
        return;
    }

    double avgSpeed = Statistics::CalculateAverage(filtered, "S");
    double stDevSpeed = Statistics::CalculateStandardDeviation(filtered, avgSpeed, "S");

    cout << "Average speed: " << fixed << setprecision(1) << avgSpeed << " km/h ";
    cout << "Sample stdev: " << fixed << setprecision(1) << stDevSpeed << endl;
}

// Menu Option 2
void Controller::displayMonthlyTemperatureAveragesAndStdev(int year, const WeatherRecords& weatherRecords) const
{
    cout << year << endl;

    for (int month = 1; month <= 12; ++month)
    {
        WeatherRecords filtered = getRecordsForMonthAndYear(month, year, weatherRecords);

        cout << monthNames[month] << ": ";

        if (filtered.getCount() == 0)
        {
            cout << "No Data" << endl;
            continue;
        }

        double avgTemp = Statistics::CalculateAverage(filtered, "T");
        double stDevTemp = Statistics::CalculateStandardDeviation(filtered, avgTemp, "T");

        cout << "average: "
             << fixed << setprecision(1) << avgTemp << " degrees C, "
             << "stdev: " << fixed << setprecision(1) << stDevTemp << endl;
    }
}

// Menu Option 3
void Controller::displayMonthlyTotalSolarRadiation(int year, const WeatherRecords& weatherRecords) const
{
    cout << year << endl;

    for (int month = 1; month <= 12; ++month)
    {
        WeatherRecords filtered = getRecordsForMonthAndYear(month, year, weatherRecords);

        cout << monthNames[month] << ": ";

        if (filtered.getCount() == 0)
        {
            cout << "No Data" << endl;
            continue;
        }

        // Record taken 10min apart
        double time_step = 10.0 / 60.0;
        // Calculate total in W/m2
        double total_W_m2 = Statistics::CalculateTotal(filtered, "SR");
        // Convert power (W/m2) to energy (Wh/m2) by multiplying by the time step
        double total_Wh_m2 = total_W_m2 * time_step;
        // Convert Wh/m2 to kWh/m2
        double totalSolarRad = total_Wh_m2 / 1000.0;

        cout << fixed << setprecision(1) << totalSolarRad << " kWh/m2" << endl;
    }
}

// Menu Option 4 (Output to File)
void Controller::outputMonthlyWindTempSolarSummary(int year, const WeatherRecords& weatherRecords) const
{
    ofstream outputFile("WindTempSolar.csv");
    if (!outputFile.is_open())
    {
        cout << "Error opening WindTempSolar.csv for writing." << endl;
        return;
    }

    outputFile << year << endl;
    bool hasAnyMonthlyData = false;

    for (int month = 1; month <= 12; ++month)
    {
        WeatherRecords filtered = getRecordsForMonthAndYear(month, year, weatherRecords);
        int count = filtered.getCount();

        if (count == 0)
        {
            continue; // Skip outputting month if no data
        }

        hasAnyMonthlyData = true;

        // Calculate all values
        double avgSpeed = Statistics::CalculateAverage(filtered, "S");
        double stDevSpeed = Statistics::CalculateStandardDeviation(filtered, avgSpeed, "S");
        double avgTemp = Statistics::CalculateAverage(filtered, "T");
        double stDevTemp = Statistics::CalculateStandardDeviation(filtered, avgTemp, "T");
        double totalSolarRad = Statistics::CalculateTotal(filtered, "SR") / 1000.0; // kWh/m2

        // Start line: Month name
        outputFile << monthNames[month] << ",";

        // 1. Average Wind Speed (S)
        outputFile << fixed << setprecision(1) << avgSpeed << "(" << fixed << setprecision(1) << stDevSpeed << "),";

        // 2. Average Ambient Temperature (T)
        outputFile << fixed << setprecision(1) << avgTemp << "(" << fixed << setprecision(1) << stDevTemp << "),";

        // 3. Total Solar Radiation (SR)
        outputFile << fixed << setprecision(1) << totalSolarRad << endl;
    }

    if (!hasAnyMonthlyData)
    {
        // Case: If the entire year’s data is not available
        outputFile << "No Data" << endl;
        cout << "No data found for year " << year << ". Output written to WindTempSolar.csv" << endl;
    }
    else
    {
        cout << "Data for year " << year << " written to WindTempSolar.csv" << endl;
    }

    outputFile.close();
}
