#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "Types.h"
#include "Statistics.h"
#include "Menu.h"

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
     * @brief Loads weather records from a specified file into the WeatherDatabase container.
     * @param weatherRecords The container to store the loaded data.
     * @param filename The path to the data file.
     * @return The number of records loaded, or -1 on error.
    */
    int LoadRecords(WeatherDatabase& weatherRecords, const string & filename);
    /**
     * @brief Loads records from all filenames listed in the specified source file.
     * @param weatherRecords The container to store ALL loaded data.
     * @param sourceFilename The file containing the list of CSV filenames (e.g., "data_source.txt").
     * @return The total number of records loaded from all files, or -1 on critical error.
     */
    int LoadAllRecordsFromSourceFile(WeatherDatabase& weatherRecords, const string& sourceFilename);
    /**
     * @brief Splits a string by a delimiter and returns the tokens in a Vector.
     * @param s The string to split.
     * @param delimiter The character delimiter.
     * @return A Vector of strings (tokens).
     */
    Vector<string> splitString(const string& s, char delimiter);
};

#endif // CONTROLLER_H_INCLUDED
