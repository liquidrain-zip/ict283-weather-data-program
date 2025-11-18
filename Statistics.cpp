#include "Statistics.h"
#include "WeatherRecord.h"
#include "Types.h"
#include <stdexcept>

float Statistics::GetValue(const WeatherRecord& record, string dataType)
{
    if (dataType == WIND_SPEED_COLUMN) {
        return record.GetWindSpeed();
    } else if (dataType == AIR_TEMP_COLUMN) {
        return record.GetTemperature();
    } else if (dataType == SOLAR_RAD_COLUMN) {
        return record.GetSolarRadiation();
    }
    return 0.0f;
}

double Statistics::CalculateTotal(const Vector<WeatherRecord>& weatherRecords, string dataType)
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

double Statistics::CalculateAverage(const Vector<WeatherRecord>& weatherRecords, string dataType)
{
    int count = weatherRecords.getCount();
    if (count == 0) {
        return 0.0;
    }

    double total = CalculateTotal(weatherRecords, dataType);
    return total / count;
}

double Statistics::CalculateStandardDeviation(
    const Vector<WeatherRecord>& weatherRecords,
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

double Statistics::CalculateSPCC(const Vector<float>& dataX, const Vector<float>& dataY)
{
    int n = dataX.getCount();
    if (n == 0 || n != dataY.getCount()) {
        return 0.0; // No data or mismatched data
    }

    // 1. Calculate means
    double sumX = 0.0, sumY = 0.0;
    for (int i = 0; i < n; ++i) {
        sumX += dataX[i];
        sumY += dataY[i];
    }
    double meanX = sumX / n;
    double meanY = sumY / n;

    // 2. Calculate numerator and denominator parts
    double numerator = 0.0;
    double denomX = 0.0;
    double denomY = 0.0;

    for (int i = 0; i < n; ++i) {
        double diffX = dataX[i] - meanX;
        double diffY = dataY[i] - meanY;

        numerator += diffX * diffY;
        denomX += diffX * diffX;
        denomY += diffY * diffY;
    }

    // 3. Calculate sPCC
    double denominator = sqrt(denomX * denomY);

    if (denominator == 0) {
        return 0.0;
    }

    return numerator / denominator;
}
