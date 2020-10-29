#include "tetris.h"

#include <iostream>
#include <thread>
#include <chrono>

bool game = true;
bool keys[4];
bool falling = false;

short x, y, max_x, min_x, max_y;

int main()
{
	tetris igra;
	
	igra.inicijalizacija();

	ShowCursor(false);

	while (game)
	{
		//timing-------------
		std::this_thread::sleep_for(std::chrono::microseconds(16700));

		//input--------------
		for (int i = 0; i < 4; i++)
		{
			keys[i] = (0x8000 & GetAsyncKeyState((unsigned char)("\x37\x38\x39\x20"[i])));
		}

		//testing------------
		if (!falling)
		{
			falling = true;
			igra.zamena();
			igra.odredjivanje_oblika();
			x = 3;
			y = -1;
			
			if (!igra.provera(x, y))
				game = false;
		}

		if (keys[0])
		{
			if(x-1 >= igra.min_x())
				x -= 1;
		}
		else if (keys[2])
		{
			if(x+1 <= igra.max_x())
				x += 1;
		}
		
		if (keys[3] && ((y + 1) < 20))
			y += 1;

		/*if (keys[1])
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
