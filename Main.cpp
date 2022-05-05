/*===============================================================================
*
* Authors: Caleb Wade, Daniel DeLima, Trever Cluney
* Class: CIS 165
* Date: 07/11/2021
*
* Email Caleb: cawasle@dmacc.edu
* Email Daniel: dcdelima@dmacc.edu
* Email Trever : tlcluney@dmacc.edu
*
* Overview: This program implements a text basded version of the minesweeper game
*
*			The objective of the game is to find all cells where there are no mines
*
*			A user is prompted to enter a row(X) and a column (Y), if the cell corresponding
*			to that coordinate has a mine, the game will end, if not the player will be
*			prompted to keep playing and as the game runs, the nearby mines will be indicated
*			by numbers inside each cell dugged.
*
*
=================================================================================*/


//Driver made by Caleb Wade and Daniel DeLima
#include "Map.h"
#include "Block.h"
#include <algorithm>

//function to handle bad player input
void handleBadInput(int input);

int main() {

	int mines = 1;																		// Amount of mines on field
	int spaces = 100;																		// total of grid layout gridYMax * gridXMax
	string playerDigFlag;																// Player input

	int digX;																			// Input for row
	int digY;																			// Input for column

	int flagX;																			// Input for flag row
	int flagY;																			// Input for flag column

	Map map(mines);
	map.printMineLoc();
	map.printLayout();

	cout << endl;
	cout << endl;
	cout << "Welcome to minesweeper \n";
	cout << "--------------------------------------------------------\n";

	while (spaces > mines && playerDigFlag != "q") {									// Repeats getting user input, asks for dig or flag
		cout << "d to dig\n";
		//cout << "f to flag\n";
		cout << "q to quit\n";
		cin >> playerDigFlag;

		if (playerDigFlag == "d")
		{
			cout << endl;
			cout << "Enter row to dig " << endl;
			cin >> digX;

			handleBadInput(digX);

			cout << "Enter column to dig\n";
			cin >> digY;

			handleBadInput(digY);

			while (digX > 9 || digX < 0 || digY > 9 || digX < 0)
			{
				cout << "Please enter in the range 0 - 9 " << endl;
				cout << "Enter row to dig " << endl;
				cin >> digX;
				handleBadInput(digX);

				cout << "Enter column to dig\n";
				cin >> digY;
				handleBadInput(digY);

			}

			if (map.dig(digX, digY) == false)												// End game if user selects mine
			{
				map.printLayout();
				cout << endl;
				cout << "*** KABOOM ***, You lose!" << endl;
				break;
			}
			spaces--;																		// Decrements spaces on board when dug 
			map.dig(digX, digY);
			cout << endl;
			map.printLayout();
			cout << endl;

		}

		else if (playerDigFlag == "q")
		{
			cout << "Quitting game..........." << endl;
			cout << "GoodBye...";
		}

		else
			cout << "ERROR: Please enter in valid input \n";

	}

	if (spaces == mines)
	{
		cout << endl;
		cout << "*** You win! ***" << endl;
	}


	return 0;
}

void handleBadInput(int input) {
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "please use only numeric inputs!" << endl;
			cin >> input;
		}
		if (!cin.fail()) {
			break;
		}
	}
}
