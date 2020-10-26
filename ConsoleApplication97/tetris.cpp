#ifndef TETRIS_CPP
#define TETRIS_CPP

#include "tetris.h"

void tetris::inicijalizacija()
{
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

}

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

void tetris::odredjivanje_oblika()
{
	srand(time(NULL));

	int pice = rand() % 7;

	for (int i = 0; i < n * n; i++)
	{
		tetronim[i / n][i % n] = pices[pice][i / n][i % n];
	}

	srand(time(NULL));
	int ponavljanje = rand() % 4;
	for (int i = 0; i < ponavljanje; i++)
		rotacija();
}

bool tetris::provera(int x, int y)
{
	bool test = true;
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			if (tabla[i + y][j + x] != 0 && tetronim[i][j] != 0)
			{
				test = false;
				goto izlaz;
			}
		}
izlaz:
	return test;
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
			else std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void tetris::proba_ispisa()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tetronim[i][j] == 1)
				std::cout << 'X';
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}
}

#endif;