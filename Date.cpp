#include "Date.h"

Date::Date(): m_day(1), m_month(1), m_year(2000)
{
}

Date::Date(int day, int month, int year): m_day(day), m_month(month), m_year(year)
{
}

void Date::SetDay(int day)
{
    if (day > 0 && day <= 31)
    {
        m_day = day;
    }
    else
    {
        m_day = 1;
    }
}

int Date::GetDay() const
{
    return m_day;
}

void Date::SetMonth(int month)
{
    if (month > 0 && month <= 12)
    {
        m_month = month;
    }
    else
    {
        m_month = 1;
    }
}

int Date::GetMonth() const
{
    return m_month;
}

void Date::SetYear(int year)
{
    m_year = year;
}

int Date::GetYear() const
{
    return m_year;
}

ostream & operator << (ostream& os, const Date& date)
{
    os << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear();
    return os;
}
