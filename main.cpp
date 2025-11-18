#include "Controller.h"
#include "Types.h"
#include "Menu.h"
#include <limits>

int main()
{
    // 0. Data store
    Controller weatherController;
    Menu weatherMenu;
    WeatherDatabase weatherDatabase;
    const string filename = "data/data_source.txt";

    // 1. Input / Load
    int recordsCount = weatherController.LoadAllRecordsFromSourceFile(weatherDatabase, filename);

    if (recordsCount > 0) {
        cout << "Successfully loaded " << recordsCount << " weather records." << endl;
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
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0; // returns to menu display
            continue;
        }

        weatherMenu.ProcessMenuChoice(choice, weatherDatabase);

        cout << endl;

    } while (choice != 5);

    return 0;
}
