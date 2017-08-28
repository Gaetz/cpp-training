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
    
}

bool update() {

    return false;
}

void draw() {

}

void shutDown() {

}

int main(int argc, char *argv[])
{
    bool isGameOver = false;


    setup();
    while(!isGameOver) {
        isGameOver = update();
        draw();
    }
    shutDown();
    
    return 0;
}
