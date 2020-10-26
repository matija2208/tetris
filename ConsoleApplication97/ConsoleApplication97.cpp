#include "tetris.h"

#include <iostream>
#include <thread>
#include <chrono>

bool game = true;
bool keys[4];
bool falling = false;

short x, y;

int main()
{
	tetris igra;
	igra.inicijalizacija();

	while (game)
	{
		//timing-------------
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		//input--------------
		for (int i = 0; i < 4; i++)
		{
			keys[i] = (0x8000 & GetAsyncKeyState((unsigned char)("\x37\x38\x39\x20"[i])));
		}

		//testing------------
		/*if (!falling)
		{
			falling = true;
			igra.odredjivanje_oblika();
			x = 3;
			y = -1;
		}
		if (keys[0])
			x -= 1;
		else if (keys[1])
			x += 1;
		if (keys[2])
		{
			igra.rotacija();
			bool test = igra.provera(x, y);
			if (!test)
			{
				igra.rotacija();
				igra.rotacija();
				igra.rotacija();
			}
		}*/
			
		//output-------------
		igra.stampaj(x, y);
	}
	return 0;
}
