#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <string>
#include <iostream>
#include "Types.h"


using std::string;
using std::cerr;

class Menu
{
public:
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

#endif // MENU_H_INCLUDED
