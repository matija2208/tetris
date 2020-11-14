#include "tetris.h"

bool game = true;
bool keys[4];
bool falling = false;
bool flevel = true;

int pice = 0;
int next_pice;

short x, y, max_x, min_x, max_y, tlines;

int speed[30] = { 18,16,14,12,10,8,6,6,5,5,5,4,4,4,4,3,3,3,3,2,2,2,2,2,2,2,2,2,2,1 };
int level = 0;
int frame = 0;

int points[5] = { 0,40,100,300,1200 };
int score = 0;

int lines = 0;
int mlines;

int main()
{
	tetris igra;

	next_pice = igra.inicijalizacija();

	while (game)
	{
		//input--------------
		for (int i = 0; i < 4; i++)
		{
			keys[i] = (0x8000 & GetAsyncKeyState((unsigned char)("\x37\x38\x39\x20"[i])));
		}

		//testing------------
			//stvara novi oblik
		if (!falling)
		{
			falling = true;
			igra.zamena();
			pice = next_pice;
			next_pice = igra.odredjivanje_oblika();
			x = 3;
			y = -1;

			if (!igra.provera(x, y))
				game = false;
		}

		//levo
		if (keys[0] && x - 1 >= igra.min_x() && igra.provera(x - 1, y))
		{
			x -= 1;
		}
		//desno
		else if (keys[2] && x + 1 <= igra.max_x() && igra.provera(x + 1, y))
		{
			x += 1;
		}

		//dole
		if (keys[3] && y + 1 <= igra.max_y() && igra.provera(x, y + 1))
		{
			y += 1;
		}

		//rotacija
		if (keys[1])
		{
			igra.rotacija(pice);
			if (!igra.provera(x, y) || x > igra.max_x() || x<igra.min_x() || y>igra.max_y())
			{
				igra.rotacija(pice);
				igra.rotacija(pice);
				igra.rotacija(pice);
			}
		}

		//ako je level veci od 29
		int t = level;
		if (t > 29)
			t = 29;

		//tajming
		if (frame == speed[t])
		{
			//provera mogucnosti spustanja oblika
			frame = -1;
			if (igra.provera(x, y + 1) && y + 1 <= igra.max_y())
			{
				y += 1;
			}
			else
			{
				//dobijanje novog oblika
				falling = false;
				//brisanje starog oblika
				igra.stapanje(x, y);
				//dobijanje sastavljenih linija ako ih ima i njihovo brisanje sa table
				tlines = igra.nDlines();

				//uvecavanje poena
				score += points[tlines] * (level + 1);
				//uvecavanje broja unistenih linija
				lines += tlines;

				//da li je trenutni level pocetni level
				if (flevel)
				{
					//uslov za uvecavanje pocetnog levela levela
					if (lines >= level * 10 + 10 || lines >= max(100, (level * 10 - 50)))
					{
						flevel = false;
						level++;
						mlines = lines;
					}
				}
				//uslov za uvecavanje ostalih levela
				else if (lines - mlines >= 10)
				{
					mlines = lines;
					level++;
				}
			}
		}

		//output-------------
		igra.stampaj(x, y, score, level);

		frame++;
	}
	return 0;
}