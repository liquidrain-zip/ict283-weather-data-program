#include <limits>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

#include "Menu.h"
#include "Statistics.h"

using std::ifstream;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::ofstream;
using std::abs;
using std::stoi;
using std::stof;
using std::getline;

void Menu::DisplayMenu()
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

void Menu::ProcessMenuChoice(int choice, const WeatherRecords& weatherRecords)
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

WeatherRecords Menu::getRecordsForMonthAndYear(int month, int year, const WeatherRecords& weatherRecords) const
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
void Menu::displayAverageWindSpeedAndStdev(int month, int year, const WeatherRecords& weatherRecords) const
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
void Menu::displayMonthlyTemperatureAveragesAndStdev(int year, const WeatherRecords& weatherRecords) const
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
void Menu::displayMonthlyTotalSolarRadiation(int year, const WeatherRecords& weatherRecords) const
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
        double totalSolarRad = Statistics::CalculateTotal(filtered, "SR");

        cout << fixed << setprecision(1) << totalSolarRad << " kWh/m2" << endl;
    }
}

// Menu Option 4 (Output to File)
void Menu::outputMonthlyWindTempSolarSummary(int year, const WeatherRecords& weatherRecords) const
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
        double totalSolarRad = Statistics::CalculateTotal(filtered, "SR");

        // Start line: Month name
        outputFile << monthNames[month] << ",";

        // 1. Average Wind Speed (S)
        outputFile << fixed << setprecision(2) << avgSpeed << "(" << fixed << setprecision(1) << stDevSpeed << "),";

        // 2. Average Ambient Temperature (T)
        outputFile << fixed << setprecision(2) << avgTemp << "(" << fixed << setprecision(1) << stDevTemp << "),";

        // 3. Total Solar Radiation (SR)
        outputFile << fixed << setprecision(2) << totalSolarRad << endl;
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

