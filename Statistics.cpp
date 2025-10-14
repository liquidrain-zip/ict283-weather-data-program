#include "Statistics.h"
#include <stdexcept>

float Statistics::GetValue(const WeatherRecord& record, string dataType)
{
    if (dataType == WIND_SPEED_COLUMN) {
        return record.m_windSpeed;
    } else if (dataType == AIR_TEMP_COLUMN) {
        return record.m_temperature;
    } else if (dataType == SOLAR_RAD_COLUMN) {
        return record.m_solarRadiation;
    }
    return 0.0f;
}

double Statistics::CalculateTotal(const WeatherRecords& weatherRecords, string dataType)
{
    if (weatherRecords.getCount() == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < weatherRecords.getCount(); ++i) {
        sum += GetValue(weatherRecords[i], dataType);
    }
    return sum;
}

double Statistics::CalculateAverage(const WeatherRecords& weatherRecords, string dataType)
{
    int count = weatherRecords.getCount();
    if (count == 0) {
        return 0.0;
    }

    double total = CalculateTotal(weatherRecords, dataType);
    return total / count;
}

double Statistics::CalculateStandardDeviation(
    const WeatherRecords& weatherRecords,
    double averageValue,
    string dataType)
{
    int count = weatherRecords.getCount();
    if (count < 2) {
        return 0.0; // Cannot calculate sample SD with less than 2 points
    }

    double sumSquaredDifferences = 0.0;
    for (int i = 0; i < count; ++i) {
        double value = GetValue(weatherRecords[i], dataType);
        sumSquaredDifferences += pow(value - averageValue, 2);
    }

    return sqrt(sumSquaredDifferences / (count - 1));
}
