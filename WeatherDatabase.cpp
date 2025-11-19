#include "WeatherDatabase.h"

void WeatherDatabase::Insert(const WeatherRecord& record)
{
    const Date& date = record.GetDate();
    int year = date.GetYear();
    int month = date.GetMonth();
    int day = date.GetDay();

    // 1. Find or Create Year
    YearData searchYear;
    searchYear.year = year;
    YearData* yearNode = m_yearTree.Search(searchYear);

    if (yearNode == nullptr)
    {
        // Year doesn't exist, create it and insert it
        m_yearTree.Insert(searchYear);
        // find the node that was just inserted
        yearNode = m_yearTree.Search(searchYear);
    }

    // 2. Find or Create Month
    MonthData searchMonth;
    searchMonth.month = month;
    MonthData* monthNode = yearNode->monthTree.Search(searchMonth);

    if (monthNode == nullptr)
    {
        // Month doesn't exist for this year, create and insert it
        yearNode->monthTree.Insert(searchMonth);
        // find the node that was just inserted
        monthNode = yearNode->monthTree.Search(searchMonth);
    }

    // 3. Insert Record into Day Map
    // std::map operator[] auto-creates the Vector<WeatherRecord> if the day doesn't exist.
    // We then Insert the record at the end of that day's vector.
    Vector<WeatherRecord>& dayVector = monthNode->dayData[day];
    dayVector.Insert(record, dayVector.getCount());
}

const DayMap* WeatherDatabase::GetMonthData(int y, int m) const
{
    // 1. Find Year
    YearData searchYear;
    searchYear.year = y;
    const YearData* yearNode = m_yearTree.Search(searchYear);

    if (yearNode == nullptr)
    {
        return nullptr; // Year not found
    }

    // 2. Find Month
    MonthData searchMonth;
    searchMonth.month = m;
    const MonthData* monthNode = yearNode->monthTree.Search(searchMonth);

    if (monthNode == nullptr)
    {
        return nullptr; // Month not found
    }

    // 3. Return pointer to the DayMap
    return &(monthNode->dayData);
}

void WeatherDatabase::TraverseYears(visit_t<YearData> visit_func, void* userData)
{
    // Delegate to the BST's InOrder traversal
    m_yearTree.InOrder(visit_func, userData);
}
