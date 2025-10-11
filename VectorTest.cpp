#include <iostream>
#include <cassert> // For assertions (assert)
#include "Vector.h" // Include the Vector class definition

using namespace std;

int main() {
    cout << "--- Vector Class Unit Tests ---" << endl;

    // 1. Default Constructor Test
    cout << "\n--- Default Constructor Test ---" << endl;
    Vector<int> defaultVector;
    cout << "Default Vector Count: " << defaultVector.getCount() << endl;
    cout << "Default Vector Capacity: " << defaultVector.getCapacity() << endl;
    if (defaultVector.getCount() == 0 && defaultVector.getCapacity() >= 1) { // Capacity is at least 1 in your default constructor
        cout << "Default Constructor Test: PASSED" << endl;
    } else {
        cout << "Default Constructor Test: FAILED" << endl;
    }

    // 2. Insert Test - Initial Insert and Count
    cout << "\n--- Insert Test - Initial ---" << endl;
    Vector<int> insertVector;
    insertVector.insert(10);
    cout << "Vector Count after insert(10): " << insertVector.getCount() << endl;
    cout << "Vector Capacity after insert(10): " << insertVector.getCapacity() << endl;
    cout << "Element at index 0: " << insertVector[0] << endl;
    if (insertVector.getCount() == 1 && insertVector[0] == 10 && insertVector.getCapacity() >= 1) {
        cout << "Insert Test - Initial: PASSED" << endl;
    } else {
        cout << "Insert Test - Initial: FAILED" << endl;
    }

    // 3. Insert Test - Multiple Inserts and Resize
    cout << "\n--- Insert Test - Resize ---" << endl;
    Vector<int> resizeVector;
    int initialCapacity = resizeVector.getCapacity();
    for (int i = 1; i <= initialCapacity + 2; ++i) { // Insert more than initial capacity to force resize
        resizeVector.insert(i * 5);
    }
    cout << "Vector Count after multiple inserts: " << resizeVector.getCount() << endl;
    cout << "Vector Capacity after multiple inserts (resized): " << resizeVector.getCapacity() << endl;
    if (resizeVector.getCount() == initialCapacity + 2 && resizeVector.getCapacity() > initialCapacity) {
        cout << "Insert Test - Resize: PASSED" << endl;
    } else {
        cout << "Insert Test - Resize: FAILED" << endl;
    }
     cout << "Elements after resize: ";
    for (int i = 0; i < resizeVector.getCount(); ++i) {
        cout << resizeVector[i] << " ";
    }
    cout << endl;


    // 4. Copy Constructor Test
    cout << "\n--- Copy Constructor Test ---" << endl;
    Vector<int> originalVector;
    originalVector.insert(20);
    originalVector.insert(30);
    Vector<int> copyVector = originalVector; // Copy constructor called
    cout << "Copy Vector Count: " << copyVector.getCount() << endl;
    cout << "Copy Vector Capacity: " << copyVector.getCapacity() << endl;
    cout << "Element at index 0 in copy: " << copyVector[0] << endl;
    cout << "Element at index 1 in copy: " << copyVector[1] << endl;

    if (copyVector.getCount() == 2 && copyVector.getCapacity() == originalVector.getCapacity() &&
        copyVector[0] == 20 && copyVector[1] == 30) {
        cout << "Copy Constructor Test: PASSED" << endl;
    } else {
        cout << "Copy Constructor Test: FAILED" << endl;
    }

    // Modify original and check if copy is independent (deep copy)
    originalVector[0] = 25;
    cout << "Original Vector[0] modified to: " << originalVector[0] << endl;
    cout << "Copy Vector[0] (should be unchanged): " << copyVector[0] << endl;
    if (copyVector[0] == 20) { // Should still be the original value
        cout << "Copy Constructor - Deep Copy Verification: PASSED" << endl;
    } else {
        cout << "Copy Constructor - Deep Copy Verification: FAILED" << endl;
    }


    // 5. Assignment Operator Test
    cout << "\n--- Assignment Operator Test ---" << endl;
    Vector<int> assignVector1;
    assignVector1.insert(40);
    assignVector1.insert(50);
    Vector<int> assignVector2;
    assignVector2 = assignVector1; // Assignment operator called
    cout << "Assigned Vector Count: " << assignVector2.getCount() << endl;
    cout << "Assigned Vector Capacity: " << assignVector2.getCapacity() << endl;
    cout << "Element at index 0 in assigned: " << assignVector2[0] << endl;
    cout << "Element at index 1 in assigned: " << assignVector2[1] << endl;
    if (assignVector2.getCount() == 2 && assignVector2.getCapacity() == assignVector1.getCapacity() &&
        assignVector2[0] == 40 && assignVector2[1] == 50) {
        cout << "Assignment Operator Test: PASSED" << endl;
    } else {
        cout << "Assignment Operator Test: FAILED" << endl;
    }

    // Modify original and check if assigned is independent (deep copy)
    assignVector1[0] = 45;
    cout << "Original Vector[0] modified to: " << assignVector1[0] << endl;
    cout << "Assigned Vector[0] (should be unchanged): " << assignVector2[0] << endl;
    if (assignVector2[0] == 40) { // Should still be the original value
        cout << "Assignment Operator - Deep Copy Verification: PASSED" << endl;
    } else {
        cout << "Assignment Operator - Deep Copy Verification: FAILED" << endl;
    }

    // 6. Self-Assignment Test (should not crash or corrupt data)
    cout << "\n--- Self-Assignment Test ---" << endl;
    Vector<int> selfAssignVector;
    selfAssignVector.insert(60);
    selfAssignVector = selfAssignVector; // Self-assignment
    cout << "Vector after self-assignment Count: " << selfAssignVector.getCount() << endl;
    cout << "Vector after self-assignment Capacity: " << selfAssignVector.getCapacity() << endl;
    cout << "Element at index 0 after self-assignment: " << selfAssignVector[0] << endl;
    if (selfAssignVector.getCount() == 1 && selfAssignVector[0] == 60) {
        cout << "Self-Assignment Test: PASSED" << endl;
    } else {
        cout << "Self-Assignment Test: FAILED" << endl;
    }

    // 7. Const operator[] Test
    cout << "\n--- Const operator[] Test ---" << endl;
    const Vector<int> constVector = copyVector; // Use copyVector from previous test, it has elements
    cout << "Const Vector Element at index 0: " << constVector[0] << endl; // Calls const operator[]
    if (constVector[0] == 20) {
        cout << "Const operator[] Test: PASSED" << endl;
    } else {
        cout << "Const operator[] Test: FAILED" << endl;
    }

    // 8. getCount() Test - already tested implicitly above, but let's add a direct test
    cout << "\n--- getCount() Test - Direct ---" << endl;
    Vector<int> countTestVector;
    for (int i = 0; i < 5; ++i) {
        countTestVector.insert(i + 100);
    }
    cout << "getCount() should be 5, actual: " << countTestVector.getCount() << endl;
    if (countTestVector.getCount() == 5) {
        cout << "getCount() Test - Direct: PASSED" << endl;
    } else {
        cout << "getCount() Test - Direct: FAILED" << endl;
    }

    // 9. getCapacity() Test - Direct test
    cout << "\n--- getCapacity() Test - Direct ---" << endl;
    Vector<int> capacityTestVector;
    cout << "Initial getCapacity(): " << capacityTestVector.getCapacity() << endl;
    int capacityBeforeInsert = capacityTestVector.getCapacity();
    capacityTestVector.insert(1);
    cout << "getCapacity() after one insert (should be same or larger): " << capacityTestVector.getCapacity() << endl;
    if (capacityTestVector.getCapacity() >= capacityBeforeInsert) {
         cout << "getCapacity() Test - Direct: PASSED" << endl;
    } else {
        cout << "getCapacity() Test - Direct: FAILED" << endl;
    }


    cout << "\n--- End of Vector Class Unit Tests ---" << endl;

    return 0;
}
