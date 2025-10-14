#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "Types.h"
#include <cmath>

/**
 * @class Statistics
 * @brief Handles all statistical calculations for weather data.
 * * Provides static methods to calculate total, average, and sample standard
 * deviation for Wind Speed ('S'), Temperature ('T'), and Solar Radiation ('R').
 */
class Statistics
{
public:
    /**
     * @brief Calculates the sum (total) of a specified data type.
     * * @param weatherData The Vector containing the weather records.
     * @param dataType A string code specifying the data type.
     * @return The total sum of the values.
     */
    static double CalculateTotal(const WeatherRecords& weatherData, string dataType);

    /**
     * @brief Calculates the arithmetic mean (average) of a specified data type.
     * * @param weatherData The Vector containing the weather records.
     * @param dataType A string code specifying the data type.
     * @return The average value.
     */
    static double CalculateAverage(const WeatherRecords& weatherData, string dataType);

    /**
     * @brief Calculates the sample standard deviation of a specified data type.
     * * @param weatherData The Vector containing the weather records.
     * @param averageValue The pre-calculated average value of the data type.
     * @param dataType A string code specifying the data type.
     * @return The sample standard deviation.
     */
    static double CalculateStandardDeviation(
        const WeatherRecords& weatherData,
        double averageValue,
        string dataType
    );

private:
    /**
     * @brief Helper function to get the value of the specified data type from a single record.
     * * @param record The single WeatherRecord object.
     * @param dataType A string code specifying the data type.
     * @return The float value of the requested data member.
     */
    static float GetValue(const WeatherRecord& record, string dataType);
};

#endif // STATISTICS_H_INCLUDED
