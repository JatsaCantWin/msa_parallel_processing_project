#include "gameMap.h"

int main() {
    gameMap* gameMap = readGameMap();
    outputGameMap(gameMap);
    destroyGame(gameMap);

    return 0;
}
