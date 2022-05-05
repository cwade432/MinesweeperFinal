#pragma once
#include "Block.h"
#include <cstdlib>
#include <queue>
#include <ctime>
#include <array>

using namespace std;

const int gridYMax = 10;
const int gridXMax = 10;

/*
* Name: Trever Cluney
* Date: 06/23/21
* Email: tlcluney@dmacc.edu
* Overview: This is the map class that will be creating and managing the display of the minefield for the minesweeper game.
* Code here is coming from https://www.programmersought.com/article/73244580123/ on how to build a minesweeper game in c++.
*/

class Map {
private:
	Block grid[gridXMax][gridYMax];
public:
	Map(int mines);
	bool dig(int coordX, int coordY);
	void flagArea(int coordX, int coordY);
	void printMineLoc();


	// Added by Daniel De Lima, the function declarations below and implementations were not taken from any other external sources

	//displays row marks from 0 - 9 for each row
	void displayRowMarks(int row, int col);

	//displays the column marks from 0 - 9 for each column
	void printColumnMarks();

	//prints the whole game layout
	void printLayout();
};
