#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "Vector.h"
#include "WeatherRecord.h"
#include <string>
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
     * Parameter is const Vector<WeatherRecord>&
     */
    static double CalculateTotal(const Vector<WeatherRecord>& weatherData, string dataType);

    /**
     * @brief Calculates the arithmetic mean (average) of a specified data type.
     * Parameter is const Vector<WeatherRecord>&
     */
    static double CalculateAverage(const Vector<WeatherRecord>& weatherData, string dataType);

    /**
     * @brief Calculates the sample standard deviation of a specified data type.
     * Parameter is const Vector<WeatherRecord>&
     */
    static double CalculateStandardDeviation(
        const Vector<WeatherRecord>& weatherData,
        double averageValue,
        string dataType
    );
    /**
     * @brief Calculates the sample Pearson Correlation Coefficient.
     */
    static double CalculateSPCC(const Vector<float>& dataX, const Vector<float>& dataY);

    /**
     * @brief Calculates the Mean Absolute Deviation (MAD) of a specified data type.
     *
     * @param weatherData The Vector containing the weather records.
     * @param averageValue The pre-calculated average value of the data type.
     * @param dataType A string code specifying the data type.
     * @return The Mean Absolute Deviation.
     */
    static double CalculateMAD(
        const Vector<WeatherRecord>& weatherData,
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
