#pragma once
#include <iostream>

using namespace std;

//Block represents a cell
struct Block {
	//to indicate if there is a mine
	bool hasMine = false;

	//to indiciate whether a cell was dugged or not
	bool isDugged = false;

	//to indicate the number of nearby mines
	int nearbyMines = 0;
};