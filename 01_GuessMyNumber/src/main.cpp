#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::rand;
using std::srand;
using std::time;


void setup() {
    cout << "|)> Guess my Number <(|\n" << endl;
}

void shutDown() {

}

int main(int argc, char *argv[])
{
    bool isGameOver = false;
    int secretNumber = ;
    int tries;
    int guess;

    srand(static_cast<unsigned int>(time(0)));

    setup();
    while(!isGameOver) {
        
        
    }
    shutDown();
    
    return 0;
}
