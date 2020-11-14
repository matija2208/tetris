#ifndef TETRIS_CPP
#define TETRIS_CPP

#include "tetris.h"

//nalazenje sledeceg oblika (next)
int tetris::odredjivanje_oblika()
{
	srand(time(NULL));

	int pice = rand() % 7;

	for (int i = 0; i < 4 * 4; i++)
	{
		next[i / 4][i % 4] = pices[pice][i / 4][i % 4];
	}

	srand(time(NULL));
	int ponavljanje = rand() % 4;
	for (int i = 0; i < ponavljanje; i++)
		pos_rotacija(pice);
	return pice;
}

//tetronim = next
void tetris::zamena()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tetronim[i][j] = next[i][j];
		}
	}
}

//rotacija trenutnog oblika (tetronim)
void tetris::rotacija(int pice)
{
	int Tetris[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	int k = 3;
	int p = pice;
	if (p == 0 || p == 2)
	{
		k = 4;
	}

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			int poz = i - (k - 1);
			if (poz < 0)
				poz *= -1;
			Tetris[j][poz] = tetronim[i][j];
		}
	}
	for (int i = 0; i < 4 * 4; i++)
	{
		tetronim[i / 4][i % 4] = Tetris[i / 4][i % 4];
	}
}

//rotacija sledeceg oblika (next)
void tetris::pos_rotacija(int pice)
{
	int Tetris[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	int k = 3;
	int p = pice;
	if (p == 0 || p == 2)
	{
		k = 4;
	}

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			int poz = i - (k - 1);
			if (poz < 0)
				poz *= -1;
			Tetris[j][poz] = next[i][j];
		}
	}
	for (int i = 0; i < 4 * 4; i++)
	{
		next[i / 4][i % 4] = Tetris[i / 4][i % 4];
	}
}

//da li se oblik uklapa na zadate kordinate
bool tetris::provera(int x, int y)
{
	int k = 0;
	int l = 0;

	if (y < 0)
	{
		k = -y;
	}
	if (x < 0)
	{
		l = -x;
	}

	for (int i = k; i < 4; i++)
	{
		for (int j = l; j < 4; j++)
		{
			if (tabla[i + y][j + x] != 0 && tetronim[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}

//maximalno x za dati oblik
int tetris::max_x()
{
	int Max_x = 9;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (tetronim[i][j] == 1 && 9 - j < Max_x)
			{
				Max_x = 9 - j;
			}
		}
	}
	return Max_x;
}

//minimalno x za dati oblik
int tetris::min_x()
{
	int Min_x = -3;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (tetronim[i][j] == 1 && 0 - j > Min_x)
			{
				Min_x = -j;
			}
		}
	}
	return Min_x;
}

//maximalno x za dati oblik
int tetris::max_y()
{
	int Max_y = 19;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetronim[i][j] == 1 && 19 - i < Max_y)
			{
				Max_y = 19 - i;
			}
		}
	}
	return Max_y;
}

//pretvaranje trenutnog oblika u pozadinu
void tetris::stapanje(int x, int y)
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (tetronim[i][j] == 1)
			{
				tabla[y + i][x + j] = 1;
			}
		}
	}
}

//dobijanje broja unistenih linija
int tetris::nDlines()
{
	bool test;
	int num_lines = 0;
	for (int i = 0;i < 20;i++)
	{
		test = true;
		for (int j = 0;j < 10;j++)
		{
			if (tabla[i][j] == 0)
			{
				test = false;
				break;
			}
		}
		if (test)
		{
			num_lines += 1;
			for (int k = i;k > 0;k--)
			{
				for (int l = 0;l < 10;l++)
				{
					tabla[k][l] = tabla[k - 1][l];
				}
			}
			for (int l = 0;l < 10;l++)
			{
				tabla[0][l] = 0;
			}
		}
	}
	return num_lines;
}

//ispis
void tetris::stampaj(int x, int y, int score, int level)
{
	system("cls");
	std::cout << "\033[0;32m" << std::endl;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if ((i == 0 && j < 5) || (j == 0 && i < 5) || (i == 5 && j < 5) || j == 5 || j == 16 || (i == 20 && j > 5 && j < 16))
			{
				std::cout << char(178) << char(178);
				if (j == 16)
				{
					if (i == 0)
					{
						std::cout << "   SCORE:";
					}
					else if (i == 1)
					{
						std::cout << "   " << score;
					}
					else if (i == 3)
					{
						std::cout << "   LEVEL:";
					}
					else if (i == 4)
					{
						std::cout << "   " << level;
					}
				}
			}
			else if ((i > 0 && i < 5) && (j > 0 && j < 5))
			{
				if (next[i - 1][j - 1] == 1)
					std::cout << char(219) << char(219);
				else
					std::cout << "  ";
			}
			else if ((i > y - 1 && i < y + 4) && (j - 6 > x - 1 && j - 6 < x + 4) && tetronim[i - y][j - x - 6] == 1)
			{
				std::cout << char(219) << char(219);
			}
			else if (i >= 0 && i < 20 && j>5 && j < 16)
			{
				if (tabla[i][j - 6] == 1)
					std::cout << char(219) << char(219);
				else
					std::cout << " .";
			}

			else std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

//set funkcija koje se moraju pozvati pre pocetka igre
int tetris::inicijalizacija()
{
	int pice = odredjivanje_oblika();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return pice;
}

#endif;
