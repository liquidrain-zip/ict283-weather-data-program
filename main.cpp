#include "Controller.h"

int main()
{
    // 0. Data store
    Controller weatherController;
    Menu weatherMenu;
    WeatherRecords weatherRecords;
    const string filename = "data/data_source.txt";
    int recordsCount = weatherController.LoadAllRecordsFromSourceFile(weatherRecords, filename);

    // 1. Input / Load
    if (recordsCount > 0) {
        cout << "Successfully loaded " << weatherRecords.getCount() << " weather records." << endl;
    }
    else
    {
        cerr << "Error loading records. Program terminating." << endl;
        return 1;
    }


    // 2. Menu
    int choice;
    do {
        weatherMenu.DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number from the menu.\n";
            cin.clear();
            choice = 0; // returns to menu display
            continue;
        }

        weatherMenu.ProcessMenuChoice(choice, weatherRecords);

        cout << endl;

    } while (choice != 5);

    return 0;
}
