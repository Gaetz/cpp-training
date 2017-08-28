#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::rand;
using std::srand;
using std::time;

int main() {
    // Random seed
    srand(static_cast<unsigned int>(time(0)));
    // Game loop
    char throwAgain = 'y';
    while(throwAgain == 'y') {
        // Throw dice
        int randomNumber = rand();
        int dice = (randomNumber % 6) + 1; // Between 1 and 6
        cout << "\nYou got a " << dice << "." << endl;
        // Again ?
        cout << "Throw again ? ";
        cin >> throwAgain;
    }

    return 0;
}