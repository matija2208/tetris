#ifndef TETRIS_CPP
#define TETRIS_CPP

#include "tetris.h"

void tetris::rotacija()
{
	int Tetris[4][4];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int poz = i - (n - 1);
			if (poz < 0)
				poz *= -1;
			Tetris[j][poz] = tetronim[i][j];
		}
	}
	for (int i = 0; i < n * n; i++)
	{
		tetronim[i / n][i % n] = Tetris[i / n][i % n];
	}
}

void tetris::pos_rotacija()
{
	int Tetris[4][4];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int poz = i - (n - 1);
			if (poz < 0)
				poz *= -1;
			Tetris[j][poz] = next[i][j];
		}
	}
	for (int i = 0; i < n * n; i++)
	{
		next[i / n][i % n] = Tetris[i / n][i % n];
	}
}

void tetris::odredjivanje_oblika()
{
	srand(time(NULL));

	int pice = rand() % 7;

	for (int i = 0; i < n * n; i++)
	{
		next[i / n][i % n] = pices[pice][i / n][i % n];
	}

	srand(time(NULL));
	int ponavljanje = rand() % 4;
	for (int i = 0; i < ponavljanje; i++)
		pos_rotacija();
}

void tetris::zamena()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tetronim[i][j] = next[i][j];
		}
	}
}

bool tetris::provera(int x, int y)
{
	int i = 0;
	int j = 0;

	if (y < 0)
	{
		i = -y;
	}
	if (x < 0)
	{
		j = -x;
	}

	for (i = i; i < n; i++)
	{
		for (j = j; j < n; j++)
		{
			if (tabla[i + y][j + x] != 0 && tetronim[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}

int tetris::max_x()
{
	int Max_x = 9;
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (tetronim[i][j] == 1 && 9-i<Max_x)
			{
				Max_x = 9 - i;
			}
		}
	}
	return Max_x;
}

int tetris::min_x()
{
	int Min_x = 0;
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (tetronim[i][j] == 1 && 0 - i > Min_x)
			{
				Min_x = - i;
			}
		}
	}
	return Min_x;
}

void tetris::stampaj(int x, int y)
{
	system("cls");
	std::cout << std::endl;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if ((i == 0 && j < 5) || (j == 0 && i < 5) || (i == 5 && j < 5) || j == 5 || j == 16 || (i == 20 && j > 5 && j < 16))
				std::cout << "#";
			else if ((i > 0 && i < 5) && (j > 0 && j < 5))
			{
				if (next[i - 1][j - 1] == 1)
					std::cout << 'X';
				else
					std::cout << ' ';
			}
			else if ((i > y - 1 && i < y + 4) && (j - 6 > x - 1 && j - 6 < x + 4))
			{
				if (tetronim[i - y][j - x - 6] == 1)
					std::cout << 'X';
				else
					std::cout << ' ';
			}
			else std::cout <<" ";
		}
		std::cout << std::endl;
	}
}

void tetris::inicijalizacija()
{
	odredjivanje_oblika();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

#endif;