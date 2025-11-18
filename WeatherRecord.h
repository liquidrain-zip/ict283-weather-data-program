#ifndef WEATHERRECORD_H_INCLUDED
#define WEATHERRECORD_H_INCLUDED

#include "Date.h"
#include "Time.h"

/**
 * @brief Class to hold a single weather record entry.
 * Manages data members privately with public getters and setters.
 */
class WeatherRecord
{
public:
    /**
     * @brief Gets the date of the record.
     * @return const Date& A constant reference to the date object.
     */
    const Date& GetDate() const
    {
        return m_date;
    }

    /**
     * @brief Gets the time of the record.
     * @return const Time& A constant reference to the time object.
     */
    const Time& GetTime() const
    {
        return m_time;
    }

    /**
     * @brief Gets the wind speed.
     * @return float The wind speed value.
     */
    float GetWindSpeed() const
    {
        return m_windSpeed;
    }

    /**
     * @brief Gets the ambient temperature.
     * @return float The temperature value.
     */
    float GetTemperature() const
    {
        return m_temperature;
    }

    /**
     * @brief Gets the solar radiation.
     * @return float The solar radiation value.
     */
    float GetSolarRadiation() const
    {
        return m_solarRadiation;
    }

    /**
     * @brief Sets the date of the record.
     * @param newDate The new Date object.
     */
    void SetDate(const Date& newDate)
    {
        m_date = newDate;
    }

    /**
     * @brief Sets the time of the record.
     * @param newTime The new Time object.
     */
    void SetTime(const Time& newTime)
    {
        m_time = newTime;
    }

    /**
     * @brief Sets the wind speed.
     * @param newSpeed The new wind speed value.
     */
    void SetWindSpeed(float newSpeed)
    {
        m_windSpeed = newSpeed;
    }

    /**
     * @brief Sets the ambient temperature.
     * @param newTemp The new temperature value.
     */
    void SetTemperature(float newTemp)
    {
        m_temperature = newTemp;
    }

    /**
     * @brief Sets the solar radiation.
     * @param newRadiation The new solar radiation value.
     */
    void SetSolarRadiation(float newRadiation)
    {
        m_solarRadiation = newRadiation;
    }


private:
    Date m_date = Date();
    Time m_time = Time();
    float m_windSpeed = 0.00;
    float m_temperature = 0.00;
    float m_solarRadiation = 0.00;
};

#endif // WEATHERRECORD_H_INCLUDED
