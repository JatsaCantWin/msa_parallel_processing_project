#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdbool.h>

typedef struct {
    int rows;
    int columns;
    bool** grid;
} gameMap;

gameMap* initializeGame(int rows, int columns);
void destroyGame(gameMap* game);
bool isValidCell(gameMap* game, int row, int col);
void setCellState(gameMap* game, int row, int col, bool state);
bool getCellState(gameMap* game, int row, int col);
void printGame(gameMap* game);
gameMap* readGameMap();
void outputGameMap(gameMap* game);

#endif // GAMEMAP_H

