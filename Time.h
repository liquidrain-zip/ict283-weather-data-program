#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/**
 * @class Time
 * @brief Represents a time of day with hour, minute, and second.
 *
 * This class encapsulates the concept of time, storing hours, minutes, and seconds.
 * It provides methods to set and retrieve these time components.
 */
class Time
{
public:
    /**
     * @brief Default constructor for Time.
     *
     * Initializes the Time object to midnight (00:00:00).
     */
    Time();

    /**
     * @brief Constructor for Time with hour, minute, and second.
     *
     * @param hour   The hour (0-23).
     * @param minute The minute (0-59).
     * @param second The second (0-59).
     *
     * Initializes a Time object with the specified hour, minute, and second.
     * No validation is performed on the input values in this version.
     */
    Time(int hour, int minute, int second);

    /**
     * @brief Sets the hour of the Time object.
     *
     * @param hour The hour to set (0-23).
     *
     * Sets the hour value for the Time object.
     * No validation is performed on the input value in this version.
     */
    void SetHour(int hour);

    /**
     * @brief Gets the hour of the Time object.
     *
     * @return int The current hour (0-23).
     *
     * Returns the hour value stored in the Time object.
     */
    int GetHour() const;

    /**
     * @brief Sets the minute of the Time object.
     *
     * @param minute The minute to set (0-59).
     *
     * Sets the minute value for the Time object.
     * No validation is performed on the input value in this version.
     */
    void SetMinute(int minute);

    /**
     * @brief Gets the minute of the Time object.
     *
     * @return int The current minute (0-59).
     *
     * Returns the minute value stored in the Time object.
     */
    int GetMinute() const;

    /**
     * @brief Sets the second of the Time object.
     *
     * @param second The second to set (0-59).
     *
     * Sets the second value for the Time object.
     * No validation is performed on the input value in this version.
     */
    void SetSecond(int second);

    /**
     * @brief Gets the second of the Time object.
     *
     * @return int The current second (0-59).
     *
     * Returns the second value stored in the Time object.
     */
    int GetSecond() const;

private:
    int m_hour;
    int m_minute;
    int m_second;
};

/**
 * @brief Overloads the output stream operator to write a Time to a stream.
 *
 * @param os   The output stream to write to.
 * @param time A constant reference to the Time object to output.
 * @return std::ostream& A reference to the output stream, for chaining operations.
 *
 * Writes the Time object to the output stream in HH:MM:SS format.
 */
ostream & operator <<( ostream & os, const Time & time );

#endif // TIME_H_INCLUDED
