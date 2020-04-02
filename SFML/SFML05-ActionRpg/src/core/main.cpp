#include "game.h"
#include "state_manager.h"

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
