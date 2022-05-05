#include "Map.h"
#include "Block.h"

Map::Map(int mines)
{
	bool regen = false;
	srand(time(0)); //Random number generator for placing mines
	for (int i = 0; i < mines; i++) {//loops until all mines have been placed
		do//generates a random number and test to make sure that a spot hasn't been claimed already
		{
			//generates random numbers within our boarders
			int x = rand() % gridXMax;
			int y = rand() % gridYMax;
			//test if mine has already be placed
			if (grid[x][y].hasMine == true) {
				regen = true;
				//cout << "System is going to regen a mine." << endl;
			}
			else {
				grid[x][y].hasMine = true;
				//cout << "Mine #" << i+1 << " placed at x: " << x << " y: " << y << endl;
				regen = false;
			}
		} while (regen);
	}
	//for loop for counting the mines next to current spot
	for (int i = 0; i < gridXMax; i++) //checks though the x-coords
		for (int j = 0; j < gridYMax; j++)//checks though the y-coords
			for (int x = max(i - 1, 0); x <= min(i + 1, gridXMax - 1); x++)//checks x-coords before and after current x-coords
				for (int y = max(j - 1, 0); y <= min(j + 1, gridYMax - 1); y++)//checks y-coords before and after current y-coord
					if (grid[x][y].hasMine)
						grid[i][j].nearbyMines++;
}

bool Map::dig(int coordX, int coordY)
{
	//Digs spot that we are at
	grid[coordX][coordY].isDugged = true;
	//Checks if there is a mine if so return false and so that we can end game
	if (grid[coordX][coordY].hasMine) {
		return false;
	}
	//If the spot doesn't have a mine check if we can dig out other spots nearby
	else
	{
		//Checks if the spot has nearby mines if so don't auto dig but return true to continue the game
		if (grid[coordX][coordY].nearbyMines != 0) {
			return true;
		}
		//If the spot we dug doesn't have any mines we want to dig all the nearby spots until we get to a place that has a nearby mine
		else
		{
			//We create a queue to work from
			queue<pair<int, int>> Q;
			//We push on our original spot to start the queue
			Q.push({ coordX,coordY });
			//Check that the queue isn't empty and continue the searching
			while (!Q.empty())
			{
				//update our current posistion that we are looking at with the first and second value from the queue
				int currX = Q.front().first;
				int currY = Q.front().second;
				//We remove the value since we are now working with it
				Q.pop();
				//we are going to grab all the values nearby that is directly above, below, left, and right of the current posistion
				for (int i = 1; i < 4; i++)
				{
					//We update temp coords with our current coords for searching
					int tempX = currX;
					int tempY = currY;
					//We switch based where we are in the for loop
					switch (i)
					{
					case 1:
						tempX = max(currX - 1, 0);//We grab the left most posistion limiting it to 0 so not to go out of bounds
					case 2:
						tempX = min(currX + 1, gridXMax - 1); // We grab the right most posistion limiting it to gridxmax - 1 so not to go out of bounds
					case 3:
						tempY = max(currY - 1, 0);// We grab the up most posistion limiting it to 0 so not to go out of bounds
					case 4:
						tempY = min(currY + 1, gridYMax - 1);// We grab the bottom most posistion limiting it to gridymax - 1 so not to go out of bounds
					}
					//Checks to see if the posistion that we are currently working in isn't already dug out or has a mine
					if (!grid[tempX][tempY].isDugged && !grid[tempX][tempY].hasMine) {
						//Check to see if this is  also a spot with no mines if so added it to the list
						if (grid[tempX][tempY].nearbyMines == 0) {
							Q.push({ tempX,tempY });
							grid[tempX][tempY].isDugged = true;
						}
						//Else just dig it
						else {
							grid[tempX][tempY].isDugged = true;
						}
					}
				}
			}
			//Once we finish mining all the spots we can return true to continue the game
			return true;
		}
	}
}


void Map::printMineLoc()
{
	int mines = 1;
	for (int x = 0; x < gridXMax; x++) {
		for (int y = 0; y < gridYMax; y++) {
			if (grid[x][y].hasMine) {
				cout << "Mine #" << mines << " found in location:" << endl;
				cout << "Coordinate x: " << x << " Coordinate y: " << y << endl;
				mines++;
			}
		}
	}
}


// Added by Daniel De Lima
void Map::printColumnMarks() {
	for (int i = 0; i < 10; i++) {
		//prints column marks from 0 to 10 with some spacing
		std::cout << "  " << " " << i;
	}
}

//displays the 
void Map::displayRowMarks(int row, int col) {

	//if we are on a row
	if (row % 1 == 0) {
		//if were are on column 0
		if (col == 0) {
			//display the row number if the row is less than 10;
			row < 10 ? cout << row << "" : cout << row;
		}
	}
}

void Map::printLayout() {

	//displaying column marks
	printColumnMarks();

	for (int row = 0; row < gridXMax; row++) {

		for (int col = 0; col < gridYMax; col++) {

			// print columns only until the 10th position then they go to the next line.
			if (col % 10 == 0) { std::cout << endl; }

			//displaying the row marks
			displayRowMarks(row, col);

			// if cell is not dugged display an empty cell
			if (!grid[row][col].isDugged) {
				std::cout << " [ ]";

				//if cell has a mine display an x inside the cell
			}
			else if (grid[row][col].hasMine) {
				std::cout << " [x]";
			}

			//if cell has nearby mines then display the number of nearby mines in the cell
			else if (grid[row][col].nearbyMines != 0) {

				cout << " [" << grid[row][col].nearbyMines << "]";
			}

			//else display the space that was cleared 
			else
				cout << "    ";
		}
	}
}

