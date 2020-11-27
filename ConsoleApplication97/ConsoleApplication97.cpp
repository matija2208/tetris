#include "tetris.h"
#include <fstream>
#include <string>

bool game = true;
bool keys[4];
bool falling = false;
bool flevel = true;
bool stampanje = true;
bool rotate = true;
int mrotate;

int pice = 0;
int next_pice;

short x, y, max_x, min_x, max_y, tlines, soft_drop_points = 0;

//int speed[20] = {360000,320000,290000,250000,220000,180000,150000,110000,70000,50000,40000,40000,40000,30000,30000,30000,20000,20000,20000,10000};
int speed[30] = { 48,43,38,33,28,23,18,13,8,6,5,5,5,4,4,4,3,3,3,2,2,2,2,2,2,2,2,2,2,1 };
int level = 0;
int frame = 0;

int points[5] = { 0,40,100,300,1200 };
int score = 0;

int lines = 0;
int mlines;

int main()
{
	tetris igra;

	std::cin >> level;

	next_pice = igra.inicijalizacija();

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 48;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	//wcscpy_s(cfi.FaceName, L"Arial"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	while (game)
	{
		//timing
		std::this_thread::sleep_for(std::chrono::milliseconds(17));
		//input--------------
		for (int i = 0; i < 4; i++)
		{
			keys[i] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x11\x27\x28"[i])));
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
			stampanje = true;
		}

		//levo
		if (keys[0] && x - 1 >= igra.min_x() && igra.provera(x - 1, y))
		{
			x -= 1;
			stampanje = true;
		}
		//desno
		else if (keys[2] && x + 1 <= igra.max_x() && igra.provera(x + 1, y))
		{
			x += 1;
			stampanje = true;
		}

		//dole
		if (keys[3] && y + 1 <= igra.max_y() && igra.provera(x, y + 1))
		{
			y += 1;
			soft_drop_points++;
			stampanje = true;
		}

		//rotacija
		if (keys[1] && rotate)
		{
			rotate = false;
			mrotate = frame;
			igra.rotacija(pice);
			if (!igra.provera(x, y) || x > igra.max_x() || x<igra.min_x() || y>igra.max_y())
			{
				igra.rotacija(pice);
				igra.rotacija(pice);
				igra.rotacija(pice);
			}
			else
			{
				stampanje = true;
			}
		}
		else
		{
			mrotate = frame;
			rotate = true;
		}

		//ako je level veci od 19/29
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
				score += (points[tlines] * (level + 1));
				score += soft_drop_points;
				soft_drop_points = 0;
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
			stampanje = true;
		}

		//output-------------
		if (stampanje)
		{
			stampanje = false;
			igra.stampaj(x, y, score, level);
		}

		frame++;
	}
	system("cls");
	std::fstream file;
	file.open("score.txt", std::ios::out | std::ios::in);
	std::string data;
	std::string d[100];

	int counter = 0, sc = 0, mult = 100000, poz = 0;
	bool t = true;
	std::string name = { "PET" };

	while (file >> data)
	{
		d[counter].append(data);


		if (t)
		{
			sc = 0;
			mult = 100000;
			for (int i = 0; i < 6; i++)
			{
				sc += ((int(data[i]) - 48) * mult);
				mult /= 10;
			}

			if (score > sc)
			{
				poz = counter;
				t = false;
			}
		}
		counter++;
	}
	d[counter].append(d[counter - 1]);
	for (int i = poz; i < counter; i++)
	{
		d[i + 1] = d[i];
	}
	std::string ubacivanje = { "      " };
	for (int i = 5; i >= 0; i--)
	{
		ubacivanje[i] = (score % 10 + 48);
		score /= 10;
	}
	for (int i = 0; i < 9; i++)
	{
		if (i < 6)
		{
			d[poz][i] = ubacivanje[i];
		}
		else
		{
			d[poz][i] = name[i - 6];
		}
	}

	for (int i = 0; i < counter + 1; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << d[i][j];
		}
		std::cout << std::endl;
	}
	file.close();
	//system("cls");
	return 0;
}