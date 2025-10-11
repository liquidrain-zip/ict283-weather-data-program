#include <iostream>
#include <sstream> // For stringstream
#include "Date.h" // Include the Date class definition

using namespace std;

int main() {
    cout << "--- Date Class Unit Tests ---" << endl;

    // 1. Default Constructor Test
    cout << "\n--- Default Constructor Test ---" << endl;
    Date defaultDate;
    cout << "Default Date: " << defaultDate << endl; // Should be 1/1/2000
    if (defaultDate.GetDay() == 1 && defaultDate.GetMonth() == 1 && defaultDate.GetYear() == 2000) {
        cout << "Default Constructor Test: PASSED" << endl;
    } else {
        cout << "Default Constructor Test: FAILED" << endl;
    }

    // 2. Parameterized Constructor Test (Valid Values)
    cout << "\n--- Parameterized Constructor Test (Valid) ---" << endl;
    Date paramDateValid(15, 8, 2023);
    cout << "Parameterized Date (Valid): " << paramDateValid << endl; // Should be 15/8/2023
    if (paramDateValid.GetDay() == 15 && paramDateValid.GetMonth() == 8 && paramDateValid.GetYear() == 2023) {
        cout << "Parameterized Constructor Test (Valid): PASSED" << endl;
    } else {
        cout << "Parameterized Constructor Test (Valid): FAILED" << endl;
    }

    // 3. SetDay Test (Valid)
    cout << "\n--- SetDay Test (Valid) ---" << endl;
    Date setDayDate;
    setDayDate.SetDay(25);
    cout << "Date after SetDay(25): " << setDayDate << endl; // Should be 25/1/2000 (Month and Year default)
    if (setDayDate.GetDay() == 25) {
        cout << "SetDay Test (Valid): PASSED" << endl;
    } else {
        cout << "SetDay Test (Valid): FAILED" << endl;
    }

    // 4. SetDay Test (Invalid)
    cout << "\n--- SetDay Test (Invalid) ---" << endl;
    Date setDayInvalidDate;
    setDayInvalidDate.SetDay(0); // Invalid day
    cout << "Date after SetDay(0 - Should default to 1/MM/YYYY): " << setDayInvalidDate << endl; // Should be 1/1/2000 (Day defaults to 1)
    if (setDayInvalidDate.GetDay() == 1) {
        cout << "SetDay Test (Invalid): PASSED" << endl;
    } else {
        cout << "SetDay Test (Invalid): FAILED" << endl;
    }

    // 5. SetMonth Test (Valid)
    cout << "\n--- SetMonth Test (Valid) ---" << endl;
    Date setMonthDate;
    setMonthDate.SetMonth(12);
    cout << "Date after SetMonth(12): " << setMonthDate << endl; // Should be 1/12/2000
    if (setMonthDate.GetMonth() == 12) {
        cout << "SetMonth Test (Valid): PASSED" << endl;
    } else {
        cout << "SetMonth Test (Valid): FAILED" << endl;
    }

    // 6. SetMonth Test (Invalid)
    cout << "\n--- SetMonth Test (Invalid) ---" << endl;
    Date setMonthInvalidDate;
    setMonthInvalidDate.SetMonth(13); // Invalid month
    cout << "Date after SetMonth(13 - Should default to DD/1/YYYY): " << setMonthInvalidDate << endl; // Should be 1/1/2000 (Month defaults to 1)
    if (setMonthInvalidDate.GetMonth() == 1) {
        cout << "SetMonth Test (Invalid): PASSED" << endl;
    } else {
        cout << "SetMonth Test (Invalid): FAILED" << endl;
    }

    // 7. SetYear Test (Valid - although year validation is basic)
    cout << "\n--- SetYear Test (Valid) ---" << endl;
    Date setYearDate;
    setYearDate.SetYear(2025);
    cout << "Date after SetYear(2025): " << setYearDate << endl; // Should be 1/1/2025
    if (setYearDate.GetYear() == 2025) {
        cout << "SetYear Test (Valid): PASSED" << endl;
    } else {
        cout << "SetYear Test (Valid): FAILED" << endl;
    }

    // 8. Output Stream Operator Test
    cout << "\n--- Output Stream Operator Test ---" << endl;
    Date outputDate(7, 3, 2024);
    stringstream ssOutput;
    ssOutput << outputDate;
    cout << "Date using output stream operator: " << ssOutput.str() << endl; // Should be 7/3/2024
    if (ssOutput.str() == "7/3/2024") {
        cout << "Output Stream Operator Test: PASSED" << endl;
    } else {
        cout << "Output Stream Operator Test: FAILED" << endl;
    }

    cout << "\n--- End of Date Class Unit Tests ---" << endl;

    return 0;
}
