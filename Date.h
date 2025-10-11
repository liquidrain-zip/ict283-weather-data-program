#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * @class Date
 * @brief Declaration of the Date class.
 *
 * This file defines the Date class, which represents a calendar date
 * consisting of day, month, and year.
 */
class Date
{
public:
    /**
     * @brief Default constructor for the Date class.
     *
     * Initializes a `Date` object with default values, setting
     * the date to a default of 01/01/2000.
     */
    Date();

    /**
     * @brief Constructor for the Date class.
     *
     * Initializes a Date object with the provided day, month, and year.
     *
     * @param day - The day of the date.
     * @param month - The month of the date.
     * @param year - The year of the date.
     */
    Date(int day, int month, int year);

    /**
     * @brief Sets the day of the month range of 1-31.
     *
     * @param day - The day of the month to set.
     * @return void
     */
    void SetDay(int day);

    /**
     * @brief Gets the day of the month.
     *
     * @return int - The day of the month.
     */
    int GetDay() const;

    /**
     * @brief Sets the month of the year range of 1-12.
     *
     * @param month - The month of the year to set.
     * @return void
     */
    void SetMonth(int month);

    /**
     * @brief Gets the month of the year.
     *
     * @return int - The month of the year.
     */
    int GetMonth() const;

    /**
     * @brief Sets the year.
     *
     * @param year - The year to set.
     * @return void
     */
    void SetYear(int year);

    /**
     * @brief Gets the year.
     *
     * @return int - The year.
     */
    int GetYear() const;

private:
    int m_day;   ///< Day of the month (1-31).
    int m_month; ///< Month of the year (1-12).
    int m_year;  ///< Year (e.g., 2025).
};

/**
 * @brief Overloads the output stream operator to write a Date to a stream.
 *
 * @param os - The output stream to write to.
 * @param date - A constant reference to the Date to output.
 * @return std::ostream& - A reference to the output stream, for chaining operations.
 */
ostream & operator <<( ostream & os, const Date & date );

#endif // DATE_H_INCLUDED
