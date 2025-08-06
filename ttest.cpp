#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    cout << "Enter name: ";
    cin >> name;

    // Calculate the width of the box dynamically based on name length
    int name_length = name.length();
    int box_width = max(name_length + 4, 25); // Minimum box width of 25 to handle shorter names

    // Print top border
    cout << " ";
    for (int i = 0; i < box_width; i++) cout << "-";
    cout << "\n";

    // Print name line with centered name
    int padding = (box_width - name_length) / 2 - 1;
    cout << "|";
    for (int i = 0; i < padding; i++) cout << " ";
    cout << name;
    for (int i = 0; i < (box_width - name_length - padding - 2); i++) cout << " ";
    cout << "|\n";

    // Print empty lines in the box
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < box_width - 2; j++) cout << " ";
        cout << "|\n";
    }

    // Print bottom border
    cout << " ";
    for (int i = 0; i < box_width; i++) cout << "-";
    cout << "\n";

    return 0;
}
