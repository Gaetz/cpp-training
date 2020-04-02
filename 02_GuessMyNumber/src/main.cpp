#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::rand;
using std::srand;
using std::time;

void setup()
{
    cout << "|)> Guess my Number <(|\n"
         << endl;
}

void shutDown()
{
    cout << "\n\nHave a nice day o/"
         << endl;
}

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(0)));

    bool isGameOver = false;
    int secretNumber = rand() % 100 + 1;
    int tries = 0;
    int guess;

    setup();
    while (!isGameOver)
    {
        cout << "\nEnter a guess between 1 and 100: ";
        cin >> guess;

        if (guess > secretNumber)
        {
            ++tries;
            cout << "Too High!";
        }
        else if (guess < secretNumber)
        {
            ++tries;
            cout << "Too Low!";
        }
        else
        {
            cout << "That's it! You got it in " << tries << " tries." << endl;
            cout << "Play again ? (y/n) ";
            char choice;
            cin >> choice;
            isGameOver = !(choice == 'y');

            if (!isGameOver)
            {
                tries = 0;
                secretNumber = rand() % 100 + 1;
                cout << "\n";
            }
        }
    }
    shutDown();

    return 0;
}
