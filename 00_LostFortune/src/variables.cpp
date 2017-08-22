#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int oldMain(int argc, char *argv[])
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

    // Consts
    const int ALIEN_POINTS = 150;
    killedAliens = 10;
    score = killedAliens * ALIEN_POINTS;
    cout << "\nscore: " << score << endl;
    
    enum Difficulty {EASY, NORMAL, HARD, GODLIKE};
    Difficulty myDifficulty = EASY;

    enum ShipCost {FIGHTER_COST = 25, BOMBER_COST, CRUISER_COST = 100}; // BOMBER_COST is equal to 26 by default
    ShipCost myShipCost = BOMBER_COST;
    cout << "Upgrade ship to Cruiser will cost " << (CRUISER_COST - myShipCost) << " ressource points." << endl;



    // End of program
    char end;
    cout << "Enter a char to end >> ";
    cin >> end;

    return 0;
}
