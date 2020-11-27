#ifndef TETRIS_H
#define TETRIS_H

#include <windows.h>
#include <time.h>
#include <iostream>
#include <thread>
#include <chrono>

class tetris
{
	//tabla za redjanje oblika
	int tabla[20][10] =
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};

	//svi moguci oblici u tetrisu
	int pices[7][4][4] =
	{
		{
			{0,0,0,0},
			{0,0,0,0} ,
			{1,1,1,1} ,
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{1,1,1,0} ,
			{0,1,0,0} ,
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,1,0} ,
			{0,1,1,0} ,
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0} ,
			{0,1,1,0} ,
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0} ,
			{1,1,0,0} ,
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0} ,
			{0,0,1,0} ,
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0} ,
			{1,0,0,0} ,
			{0,0,0,0}
		}
	};

	//trenutni oblik
	int tetronim[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//sledeci oblik
	int next[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

#define SCREEN_WIDTH 43
#define SCREEN_HEIGHT 25

public:

	int odredjivanje_oblika();
	void zamena();
	void rotacija(int pice);
	void pos_rotacija(int pice);
	bool provera(int x, int y);
	int max_x();
	int min_x();
	int max_y();
	void stapanje(int x, int y);
	int nDlines();
	void stampaj(int x, int y, int score, int level);
	int inicijalizacija();
};

#endif;