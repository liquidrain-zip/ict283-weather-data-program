#include "Time.h"

Time::Time(): m_hour(0), m_minute(0), m_second(0)
{
}

Time::Time(int hour, int minute, int second) {
    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

void Time::SetHour(int hour) {
    if (hour >= 0 && hour <= 23) {
        m_hour = hour;
    } else {
        m_hour = 0;
    }
}

int Time::GetHour() const {
    return m_hour;
}

void Time::SetMinute(int minute) {
    if (minute >= 0 && minute <= 59) {
        m_minute = minute;
    } else {
        m_minute = 0;
    }
}

int Time::GetMinute() const {
    return m_minute;
}

void Time::SetSecond(int second) {
    if (second >= 0 && second <= 59) {
        m_second = second;
    } else {
        m_second = 0;
    }
}

int Time::GetSecond() const {
    return m_second;
}

ostream& operator << (ostream& os, const Time& time) {
    os << std::setfill('0') << std::setw(2) << time.GetHour() << ":"
       << std::setw(2) << time.GetMinute() << ":"
       << std::setw(2) << time.GetSecond();
    return os;
}
