#include <iostream>
#include <sstream>
#include "Time.h"

using namespace std;

int main()
{
    cout << "--- Time Class Unit Tests ---" << endl;

    // 1. Default Constructor Test
    cout << "\n--- Default Constructor Test ---" << endl;
    Time defaultTime;
    cout << "Default Time: " << defaultTime << endl; // Should be 00:00:00
    if (defaultTime.GetHour() == 0 && defaultTime.GetMinute() == 0 && defaultTime.GetSecond() == 0)
    {
        cout << "Default Constructor Test: PASSED" << endl;
    }
    else
    {
        cout << "Default Constructor Test: FAILED" << endl;
    }

    // 2. Parameterized Constructor Test (Valid Values)
    cout << "\n--- Parameterized Constructor Test (Valid) ---" << endl;
    Time paramTimeValid(10, 30, 45);
    cout << "Parameterized Time (Valid): " << paramTimeValid << endl; // Should be 10:30:45
    if (paramTimeValid.GetHour() == 10 && paramTimeValid.GetMinute() == 30 && paramTimeValid.GetSecond() == 45)
    {
        cout << "Parameterized Constructor Test (Valid): PASSED" << endl;
    }
    else
    {
        cout << "Parameterized Constructor Test (Valid): FAILED" << endl;
    }

    // 3. SetHour Test (Valid)
    cout << "\n--- SetHour Test (Valid) ---" << endl;
    Time setHourTime;
    setHourTime.SetHour(15);
    cout << "Time after SetHour(15): " << setHourTime << endl; // Should be 15:00:00
    if (setHourTime.GetHour() == 15)
    {
        cout << "SetHour Test (Valid): PASSED" << endl;
    }
    else
    {
        cout << "SetHour Test (Valid): FAILED" << endl;
    }

    // 4. SetHour Test (Invalid)
    cout << "\n--- SetHour Test (Invalid) ---" << endl;
    Time setHourInvalidTime;
    setHourInvalidTime.SetHour(30); // Invalid hour
    cout << "Time after SetHour(30 - Should default to 00:MM:SS): " << setHourInvalidTime << endl; // Should be 00:00:00 (Hour defaults to 0)
    if (setHourInvalidTime.GetHour() == 0)
    {
        cout << "SetHour Test (Invalid): PASSED" << endl;
    }
    else
    {
        cout << "SetHour Test (Invalid): FAILED" << endl;
    }

    // 5. SetMinute Test (Valid)
    cout << "\n--- SetMinute Test (Valid) ---" << endl;
    Time setMinuteTime;
    setMinuteTime.SetMinute(59);
    cout << "Time after SetMinute(59): " << setMinuteTime << endl; // Should be 00:59:00
    if (setMinuteTime.GetMinute() == 59)
    {
        cout << "SetMinute Test (Valid): PASSED" << endl;
    }
    else
    {
        cout << "SetMinute Test (Valid): FAILED" << endl;
    }

    // 6. SetMinute Test (Invalid)
    cout << "\n--- SetMinute Test (Invalid) ---" << endl;
    Time setMinuteInvalidTime;
    setMinuteInvalidTime.SetMinute(60); // Invalid minute
    cout << "Time after SetMinute(60 - Should default to HH:00:SS): " << setMinuteInvalidTime << endl; // Should be 00:00:00 (Minute defaults to 0)
    if (setMinuteInvalidTime.GetMinute() == 0)
    {
        cout << "SetMinute Test (Invalid): PASSED" << endl;
    }
    else
    {
        cout << "SetMinute Test (Invalid): FAILED" << endl;
    }

    // 7. SetSecond Test (Valid)
    cout << "\n--- SetSecond Test (Valid) ---" << endl;
    Time setSecondTime;
    setSecondTime.SetSecond(58);
    cout << "Time after SetSecond(58): " << setSecondTime << endl; // Should be 00:00:58
    if (setSecondTime.GetSecond() == 58)
    {
        cout << "SetSecond Test (Valid): PASSED" << endl;
    }
    else
    {
        cout << "SetSecond Test (Valid): FAILED" << endl;
    }

    // 8. SetSecond Test (Invalid)
    cout << "\n--- SetSecond Test (Invalid) ---" << endl;
    Time setSecondInvalidTime;
    setSecondInvalidTime.SetSecond(61); // Invalid second
    cout << "Time after SetSecond(61 - Should default to HH:MM:00): " << setSecondInvalidTime << endl; // Should be 00:00:00 (Second defaults to 0)
    if (setSecondInvalidTime.GetSecond() == 0)
    {
        cout << "SetSecond Test (Invalid): PASSED" << endl;
    }
    else
    {
        cout << "SetSecond Test (Invalid): FAILED" << endl;
    }

    // 9. Output Stream Operator Test
    cout << "\n--- Output Stream Operator Test ---" << endl;
    Time outputTime(9, 5, 3);
    stringstream ssOutput;
    ssOutput << outputTime;
    cout << "Time using output stream operator: " << ssOutput.str() << endl; // Should be 09:05:03
    if (ssOutput.str() == "09:05:03")
    {
        cout << "Output Stream Operator Test: PASSED" << endl;
    }
    else
    {
        cout << "Output Stream Operator Test: FAILED" << endl;
    }

    cout << "\n--- End of Time Class Unit Tests ---" << endl;

    return 0;
}
