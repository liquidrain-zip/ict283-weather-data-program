#include "Controller.h"

int main()
{
    // 0. Data store
    Controller weatherController;
    WindLogType windRecords;
    const string filename = "data/MetData-31-3.csv";

    // 1. Input / Load
    if (weatherController.LoadRecords(windRecords, filename) == -1) {
        cerr << "Error loading records. Program terminating." << endl;
        return 1;
    }
    else
    {
        cout << "Successfully loaded " << windRecords.getCount() << " wind records." << endl;
    }


    // 2. Menu
    int choice;
    do {
        weatherController.DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number from the menu.\n";
            cin.clear();
            choice = 0; // returns to menu display
            continue;
        }

        weatherController.ProcessMenuChoice(choice, windRecords);

        cout << endl;

    } while (choice != 5);

    return 0;
}
