#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void testFile(const string& fileName) {
    ifstream testFile(fileName);
    if (!testFile.is_open()) {
        cout << "File " << fileName << " cannot be opened or does not exist – program terminated" << endl;
        return;
    }

    // Check if the file is empty by moving the cursor to the end and checking the position
    testFile.seekg(0, ios::end);
    if (testFile.tellg() == 0) {
        cout << "File " << fileName << " contains no data – program terminated" << endl;
        return;
    }

    cout << "File " << fileName << " is ready for further testing" << endl;
}

int main() {
    // Example test cases
    testFile("nonexistentfile.dat"); // Test 1: Non-existent file
    testFile("emptyfile.dat");       // Test 2: Empty file
    return 0;
}
