#include "Game.h"
#include "StateManager.h"

int main(int argc, char* argv[]) {
    Game game;
    // Game loop
    while(!game.getWindow().isDone()) {
        game.handleInput();
        game.update();
        game.render();
        game.lateUpdate();
    }

    return 0;
}
