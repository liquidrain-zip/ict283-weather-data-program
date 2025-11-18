#include <limits>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

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

static Vector<WeatherRecord> AggregateMonthRecords(const DayMap* dayMap)
{
    Vector<WeatherRecord> aggregatedRecords;
    if (dayMap == nullptr)
    {
        return aggregatedRecords;
    }

    for (DayMap::const_iterator it = dayMap->begin(); it != dayMap->end(); ++it)
    {
        const Vector<WeatherRecord>& dayVector = it->second;

        for (int i = 0; i < dayVector.getCount(); ++i)
        {
            aggregatedRecords.Insert(dayVector[i], aggregatedRecords.getCount());
        }
    }
    return aggregatedRecords;
}

/**
 * @brief Context struct to hold data for the sPCC collector.
 */
struct SPCC_Collector
{
    SPCC_Collector() : targetMonth(0), all_S(), all_T(), all_R() {}

    int targetMonth;
    Vector<float> all_S; // All Wind Speed data
    Vector<float> all_T; // All Temperature data
    Vector<float> all_R; // All Solar Radiation data
};

/**
 * @brief The "visit" function (static) to be passed to the BST traversal.
 *
 * This function is called for EVERY YearData node in the main BST.
 * It checks if that year has data for the 'targetMonth' and, if so,
 * collects all S, T, and R values into the collector struct.
 */
static void sPCC_Visit_Func(YearData& yearData, void* userData)
{
    SPCC_Collector* collector = static_cast<SPCC_Collector*>(userData);

    // 1. Search this Year's monthTree for the target month
    MonthData searchMonth;
    searchMonth.month = collector->targetMonth;
    MonthData* monthNode = yearData.monthTree.Search(searchMonth);

    if (monthNode != nullptr)
    {
        // 2. Found the month. Iterate through its DayMap.
        for (DayMap::const_iterator it = monthNode->dayData.begin(); it != monthNode->dayData.end(); ++it)
        {
            const Vector<WeatherRecord>& dayVector = it->second;

            // 3. Add every record's data to the collector's vectors
            for (int i = 0; i < dayVector.getCount(); ++i)
            {
                const WeatherRecord& rec = dayVector[i];
                collector->all_S.Insert(rec.GetWindSpeed(), collector->all_S.getCount());
                collector->all_T.Insert(rec.GetTemperature(), collector->all_T.getCount());
                collector->all_R.Insert(rec.GetSolarRadiation(), collector->all_R.getCount());
            }
        }
    }
}

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
        cout << "Enter the month (1-12): ";
        if (!(cin >> month) || month < 1 || month > 12)
        {
            cout << "Invalid month. Returning to menu.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        displaySPCC(month, weatherRecords);
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

// Menu Option 1
void Menu::displayAverageWindSpeedAndStdev(int month, int year, const WeatherRecords& weatherRecords) const
{
    // Query the database
    const DayMap* monthData = weatherRecords.GetMonthData(year, month);

    // Aggregate all records for that month
    Vector<WeatherRecord> filtered = AggregateMonthRecords(monthData);

    cout << monthNames[month] << " " << year << ": ";

    if (filtered.getCount() == 0)
    {
        cout << "No Data" << endl;
        return;
    }

    // Calculate stats
    double avgSpeed = Statistics::CalculateAverage(filtered, "S");
    double stDevSpeed = Statistics::CalculateStandardDeviation(filtered, avgSpeed, "S");

    cout << "Average speed: " << fixed << setprecision(2) << avgSpeed << " km/h ";
    cout << "Sample stdev: " << fixed << setprecision(2) << stDevSpeed << endl;
}

// Menu Option 2
void Menu::displayMonthlyTemperatureAveragesAndStdev(int year, const WeatherRecords& weatherRecords) const
{
    cout << year << endl;

    for (int month = 1; month <= 12; ++month)
    {
        // Query DB for this month (FAST)
        const DayMap* monthData = weatherRecords.GetMonthData(year, month);

        // Aggregate
        Vector<WeatherRecord> filtered = AggregateMonthRecords(monthData);

        cout << monthNames[month] << ": ";

        if (filtered.getCount() == 0)
        {
            cout << "No Data" << endl;
            continue;
        }

        // Calculate stats
        double avgTemp = Statistics::CalculateAverage(filtered, "T");
        double stDevTemp = Statistics::CalculateStandardDeviation(filtered, avgTemp, "T");

        cout << "average: "
             << fixed << setprecision(2) << avgTemp << " degrees C, "
             << "stdev: " << fixed << setprecision(2) << stDevTemp << endl;
    }
}

// ---
// Menu Option 3
// ---
void Menu::displaySPCC(int month, const WeatherRecords& weatherRecords) const
{
    // Create the collector
    SPCC_Collector collector;
    collector.targetMonth = month;

    // Run the traversal
    // I cast away 'const' here to call TraverseYears, which calls a
    // non-const BST InOrder. This is a design trade-off.
    // A better way would be to have const- and non-const traversals.
    // For this assignment, this cast is the simplest solution.
    WeatherDatabase& nonConstDB = const_cast<WeatherDatabase&>(weatherRecords);
    nonConstDB.TraverseYears(sPCC_Visit_Func, &collector);

    cout << "\nSample Pearson Correlation Coefficient for " << monthNames[month] << endl;

    if (collector.all_S.getCount() < 2)
    {
        cout << "Not enough data to calculate sPCC for " << monthNames[month] << "." << endl;
        return;
    }

    // Calculate and display results
    double s_t = Statistics::CalculateSPCC(collector.all_S, collector.all_T);
    double s_r = Statistics::CalculateSPCC(collector.all_S, collector.all_R);
    double t_r = Statistics::CalculateSPCC(collector.all_T, collector.all_R);

    cout << "S_T: " << fixed << setprecision(2) << s_t << endl;
    cout << "S_R: " << fixed << setprecision(2) << s_r << endl;
    cout << "T_R: " << fixed << setprecision(2) << t_r << endl;
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
        const DayMap* monthData = weatherRecords.GetMonthData(year, month);
        Vector<WeatherRecord> filtered = AggregateMonthRecords(monthData);
        int count = filtered.getCount();

        if (count == 0)
        {
            continue; // Skip outputting month if no data
        }

        hasAnyMonthlyData = true;

        // 1. Wind Speed (S)
        double avgSpeed = Statistics::CalculateAverage(filtered, WIND_SPEED_COLUMN);
        double stDevSpeed = Statistics::CalculateStandardDeviation(filtered, avgSpeed, WIND_SPEED_COLUMN);
        double madSpeed = Statistics::CalculateMAD(filtered, avgSpeed, WIND_SPEED_COLUMN);

        // 2. Ambient Temperature (T)
        double avgTemp = Statistics::CalculateAverage(filtered, AIR_TEMP_COLUMN);
        double stDevTemp = Statistics::CalculateStandardDeviation(filtered, avgTemp, AIR_TEMP_COLUMN);
        double madTemp = Statistics::CalculateMAD(filtered, avgTemp, AIR_TEMP_COLUMN);

        // 3. Total Solar Radiation (SR)
        double totalSolarRad = Statistics::CalculateTotal(filtered, SOLAR_RAD_COLUMN);

        outputFile << monthNames[month] << ",";

        // 1. Average Wind Speed (S)
        outputFile << fixed << setprecision(1) << avgSpeed
                   << "(" << fixed << setprecision(1) << stDevSpeed
                   << ", " << fixed << setprecision(1) << madSpeed << "),";

        // 2. Average Ambient Temperature (T)
        outputFile << fixed << setprecision(1) << avgTemp
                   << "(" << fixed << setprecision(1) << stDevTemp
                   << ", " << fixed << setprecision(1) << madTemp << "),";

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

