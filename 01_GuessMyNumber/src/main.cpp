#include <iostream>

using std::cout;
using std::endl;
using std::cin;

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

void setup() {

}

bool update() {

    return false;
}

void draw() {

}

void shutDown() {
    
}