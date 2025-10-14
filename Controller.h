#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "Types.h"
#include "Statistics.h"

#include <string>
#include <iostream>


using std::string;
using std::cerr;

/**
 * @class Controller
 * @brief Defines the Controller class, handling I/O, menu, user input validation,
 * data filtering, and delegating calculations to the Statistics class.
 */
class Controller
{
public:
    /**
     * @brief Loads weather records from a specified file into the WeatherRecords container.
     * @param weatherRecords The container to store the loaded data.
     * @param filename The path to the data file.
     * @return The number of records loaded, or -1 on error.
    */
    int LoadRecords(WeatherRecords& weatherRecords, const string & filename);
    /**
     * @brief Loads records from all filenames listed in the specified source file.
     * @param weatherRecords The container to store ALL loaded data.
     * @param sourceFilename The file containing the list of CSV filenames (e.g., "data_source.txt").
     * @return The total number of records loaded from all files, or -1 on critical error.
     */
    int LoadAllRecordsFromSourceFile(WeatherRecords& weatherRecords, const string& sourceFilename);
    /**
     * @brief Displays the main menu options to the user.
     */
    void DisplayMenu();
    /**
     * @brief Processes the user's menu choice, prompts for necessary input, and runs the requested report.
     * @param choice The integer choice from the menu.
     * @param weatherRecords The complete set of all loaded weather records.
     */
    void ProcessMenuChoice(int choice, const WeatherRecords& weatherRecords);
    /**
     * @brief Splits a string by a delimiter and returns the tokens in a Vector.
     * @param s The string to split.
     * @param delimiter The character delimiter.
     * @return A Vector of strings (tokens).
     */
    Vector<string> splitString(const string& s, char delimiter);
private:
    /**
     * @brief Retrieves all WeatherRecords for a specific month and year.
     * @param month The month number (1-12) to filter by.
     * @param year The year number to filter by.
     * @param weatherRecords The full set of all loaded weather records.
     * @return WeatherRecords A new Vector containing only the matching records.
     */
    WeatherRecords getRecordsForMonthAndYear(int month, int year, const WeatherRecords& weatherRecords) const;
     // Menu 1: Average wind speed and sample standard deviation (specific month and year)
    void displayAverageWindSpeedAndStdev(int month, int year, const WeatherRecords& weatherRecords) const;

    // Menu 2: Average ambient air temperature and sample standard deviation (each month of a year)
    void displayMonthlyTemperatureAveragesAndStdev(int year, const WeatherRecords& weatherRecords) const;

    // Menu 3: Total solar radiation (each month of a specified year)
    void displayMonthlyTotalSolarRadiation(int year, const WeatherRecords& weatherRecords) const;

    // Menu 4: Output monthly summary to file (WindTempSolar.csv)
    void outputMonthlyWindTempSolarSummary(int year, const WeatherRecords& weatherRecords) const;
};

#endif // CONTROLLER_H_INCLUDED
