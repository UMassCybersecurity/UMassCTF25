#include <iostream>

using namespace std;

int main() {
    int input = 0;

    cout << "Enter a number (1 to get flag): " << flush;

    while (cin >> input) { // Keep reading input
        if (input == 1) {
            cout << "UMASS{example-pwn-or-crypto!92}" << endl;
            break; // Exit after correct input
        } else {
            cout << "Wrong number :( Try again: " << flush;
        }
    }

    return 0;
}
