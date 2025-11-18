#ifndef WEATHERDATABASE_H_INCLUDED
#define WEATHERDATABASE_H_INCLUDED

#include "Bst.h"
#include "WeatherRecord.h"
#include "Vector.h"
#include <map>

using DayMap = std::map<int, Vector<WeatherRecord>>;

/**
 * @struct MonthData
 * @brief Stores all data for a single month, held within a YearData's BST.
 */
struct MonthData
{
    int month = 0;
    DayMap dayData; // Map of <Day_Number, Vector_Of_Records_For_That_Day>

    // Required operators for Bst<MonthData>
    bool operator<(const MonthData& other) const { return month < other.month; }
    bool operator>(const MonthData& other) const { return month > other.month; }
    bool operator==(const MonthData& other) const { return month == other.month; }
};

/**
 * @struct YearData
 * @brief Stores all data for a single year, held within the main BST.
 */
struct YearData
{
    int year = 0;
    Bst<MonthData> monthTree; // A BST of all months for this year

    // Required operators for Bst<YearData>
    bool operator<(const YearData& other) const { return year < other.year; }
    bool operator>(const YearData& other) const { return year > other.year; }
    bool operator==(const YearData& other) const { return year == other.year; }
};


/**
 * @class WeatherDatabase
 * @brief Encapsulates the Year->Month->Day nested data structure.
 *
 * This class provides efficient insertion and query methods for the menu options.
 */
class WeatherDatabase
{
public:
    WeatherDatabase() = default;
    ~WeatherDatabase() = default;

    /**
     * @brief Inserts a single weather record into the nested data structure.
     * @param record The WeatherRecord to add.
     */
    void Insert(const WeatherRecord& record);

    /**
     * @brief Retrieves the map of day-data for a specific month and year.
     * @param y The year to search for.
     * @param m The month to search for.
     * @return A const pointer to the DayMap, or nullptr if no data exists.
     */
    const DayMap* GetMonthData(int y, int m) const;

    /**
     * @brief Traverses the Year BST, calling the visit function on each YearData.
     * This is used for Menu Option 3 (sPCC) to collect data across all years.
     * @param visit_func The function pointer to call.
     * @param userData A void pointer to a 'collector' struct.
     */
    void TraverseYears(visit_t<YearData> visit_func, void* userData);

private:
    Bst<YearData> m_yearTree; // The root of our data structure
};

#endif // WEATHERDATABASE_H_INCLUDED
