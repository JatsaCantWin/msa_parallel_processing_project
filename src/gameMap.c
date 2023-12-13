#include "gameMap.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

gameMap* initializeGame(int rows, int columns) {
    gameMap* game = (gameMap*)malloc(sizeof(gameMap));
    game->rows = rows;
    game->columns = columns;

    game->grid = (bool**)malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; ++i) {
        game->grid[i] = (bool*)malloc(columns * sizeof(bool));
        memset(game->grid[i], false, columns * sizeof(bool));
    }

    return game;
}

void destroyGame(gameMap* game) {
    for (int i = 0; i < game->rows; ++i) {
        free(game->grid[i]);
    }
    free(game->grid);
    free(game);
}

bool isValidCell(gameMap* game, int row, int col) {
    return row >= 0 && row < game->rows && col >= 0 && col < game->columns;
}

void setCellState(gameMap* game, int row, int col, bool state) {
    if (isValidCell(game, row, col)) {
        game->grid[row][col] = state;
    } 
}

bool getCellState(gameMap* game, int row, int col) {
    if (isValidCell(game, row, col)) {
        return game->grid[row][col];
    } else {
	return NULL;
    }
}

void printGame(gameMap* game) {
    for (int i = 0; i < game->rows; ++i) {
        for (int j = 0; j < game->columns; ++j) {
            printf("%d ", game->grid[i][j] ? 1 : 0);
        }
        printf("\n");
    }
}

gameMap* readGameMap() {
    int rows, columns;
    scanf("%d,%d", &rows, &columns);
    getchar();

    gameMap* game = initializeGame(rows, columns);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int value;
            scanf("%d,", &value);
            game->grid[i][j] = (value == 1) ? true : false;
        }
    }

    return game;
}

void outputGameMap(gameMap* game) {
    printf("%d,%d,", game->rows, game->columns);
    for (int i = 0; i < game->rows; ++i) {
        for (int j = 0; j < game->columns; ++j) {
            printf("%d", game->grid[i][j] ? 1 : 0);
            if (j != game->columns - 1) {
                printf(",");
            }
        }
        if ((i + 1) < (game->rows))
            printf(",");
    }
}
