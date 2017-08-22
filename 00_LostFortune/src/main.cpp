#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main(int argc, char *argv[])
{
    int score;
    double distance;
    char playAgain;
    bool areShieldsUp;
    short lives, killedAliens;

    score = 0;
    distance = 1200.76;
    playAgain = 'y';
    areShieldsUp = true;
    lives = 3;
    killedAliens = 10;
    double engineTemp = 5438.216;

    cout << "\nscore: " << score << endl;
    cout << "distance: " << distance << endl;
    cout << "playAgain: " << playAgain << endl;
    cout << "lives: " << lives << endl;
    cout << "killedAliens: " << killedAliens << endl;
    cout << "engineTemp: " << engineTemp << endl;

    int fuel;
    cout << "How much fuel? >> ";
    cin >> fuel;
    cout << "fuel: " << fuel << endl;

    typedef unsigned short int ushort;
    ushort bonus = 10;
    cout << "bonus: " << bonus << endl;    
    
    // Altering score
    score = score + 100;
    cout << "\nscore: " << score << endl;
    score += 100;    
    cout << "score: " << score << endl;
    
    // Increment operators
    ++lives;
    cout << "\nlives: " << lives << endl;
    
    lives = 3;
    lives++;
    cout << "lives: " << lives << endl;
    
    lives = 3;
    bonus = ++lives * 10;
    cout << "lives, bonus: " << lives << ", " << bonus << endl;
    
    lives = 3;
    bonus = lives++ * 10;
    cout << "lives, bonus: " << lives << ", " << bonus << endl;
    
    // Integer wrap around
    score = 4294967295;
    cout << "\nscore: " << score << endl;
    ++score;    
    cout << "score: " << score << endl;

    // End of program
    char end;
    cout << "Enter a char to end >> ";
    cin >> end;

    return 0;
}
