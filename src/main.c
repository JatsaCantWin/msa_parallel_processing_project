#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool** initGeneration(int size_x, int size_y)
{
	bool** newGeneration;

	newGeneration = malloc(sizeof(bool*)*size_x);
	for (int i = 0; i < size_x; i++)
	{
		newGeneration[i] = malloc(sizeof(bool)*size_y);
	}

	return newGeneration;
}

bool isAlive(bool** generation, int x, int y, int size_x, int size_y)
{
	if (x < 0)
		return false;
	if (y < 0)
		return false;
	if (x >= size_x)
		return false;
	if (x >= size_y)
		return false;

	return generation[x][y];
}

void destroyGeneration(bool** generation, int size_x)
{
	for (int i = 0; i < size_x; i++)
	{
		free(generation[i]);
	}

	free(generation);
}

int countAliveNeighbors(bool** generation, int x, int y, int size_x, int size_y)
{
	int aliveNeighbors = 0;

	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if ((x == i) && (j == y))
				continue;
			
			if (isAlive(generation, i, j, size_x, size_y))
				aliveNeighbors++;
		}
	}

	return aliveNeighbors;
}

bool canSurvive(bool** generation, int x, int y, int size_x, int size_y)
{
	int aliveNeighbors = countAliveNeighbors(generation, x, y, size_x, size_y);

	return !((aliveNeighbors == 4) || (aliveNeighbors == 1));
}

bool canBeBorn(bool** generation, int x, int y, int size_x, int size_y)
{
	int aliveNeighbors = countAliveNeighbors(generation, x, y, size_x, size_y);

	return (aliveNeighbors == 3);
}

void simulate_generation(bool*** generation, int size_x, int size_y)
{
	bool** newGeneration;

	newGeneration = initGeneration(size_x, size_y);

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if (isAlive(*generation, i, j, size_x, size_y))
			{
				if (!canSurvive(*generation, i, j, size_x, size_y))
				{
					newGeneration[i][j] = false;	
				}
				else
				{
					newGeneration[i][j] = true;
				}
			}
			else 
			{
				if (canBeBorn(*generation, i, j, size_x, size_y))
				{
					newGeneration[i][j] = true;
				}
				else
				{
					newGeneration[i][j] = false;
				}
			}
		}
	}
	
	destroyGeneration(*generation, size_x);
	*generation = newGeneration;
}

void printGeneration(bool** generation, int size_x, int size_y)
{
	for (int j = 0; j < size_y; j++)
	{
		for (int i = 0; i < size_x; i++)
		{
			if (isAlive(generation, i, j, size_x, size_y))
				printf("x");
			else
				printf("o");
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	int generationNum = 10;
	
	int size_x = 10;
	int size_y = 10;

	bool** generation = initGeneration(size_x, size_y);
	
	for (int i = 0; i < generationNum; i++)
	{
		simulate_generation(&generation, size_x, size_y);

	 	printGeneration(generation, size_x, size_y);
	}
	
	destroyGeneration(generation, size_x);

	return 0;
}
