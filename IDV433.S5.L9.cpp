#include <iostream>
# include <conio.h>
using namespace std;

enum Cell { Dead, Alive };
enum Formations { Glider = 1, Semiphore, Manually};

const int ROWS = 16;
const int COLS = 16; 
const char ESC = 27;

typedef Cell genType[ROWS + 1][COLS + 1]; 

void initGame(genType &gen);
void showGeneration(genType &gen);
void setInitGen(genType &gen);
void setSemaphore(genType &gen);
void setGlider(genType &gen);
void setUserFormation(genType &gen);
void update(genType &gen);
bool shouldBeAlive(genType &gen, int r, int c);
int countNeighbors(genType &gen, int r, int c);

int main()
{
	genType gen; // Matrix to hold a generation


	do
	{
		initGame(gen);
		showGeneration(gen);
		
		cout << "\n\nPress any key - ESC stops\n";
		while (_getch() != ESC) // Repeat generations
		{
			update(gen);
			showGeneration(gen);

			cout << "\n\nPress any key - ESC stops\n";
		}
		cout << "Another simulation ? (Y/N) ";
	} while (toupper(_getch()) != 'N'); 
	return 0;
}


//Updates the board. Uses a dynamic array to hold the new board while the old is uppdated.
//Then the new is copyes in to the old and removed.
void update(genType &gen) { 
	genType *prelPtr = nullptr;
	prelPtr = new genType[ROWS+1];

	for (int r = 1; r < ROWS; r++) {
		for (int c = 1; c < COLS; c++) {
			if (shouldBeAlive(gen, r, c )) {
				*prelPtr[r][c] = Alive;
			}else {
				*prelPtr[r][c] = Dead;
			}
		}
	}
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			gen[i][j] = *prelPtr[i][j];
		}
	}
	delete[] prelPtr;
	prelPtr = nullptr;
} 


//Check if a cell chould be alive or not.
bool shouldBeAlive(genType &gen, int r, int c) {
	int noNeighbors;
	noNeighbors = countNeighbors(gen, r, c);
	if (noNeighbors == 3 || noNeighbors == 2 && gen[r][c] == Alive) {
		return true;
	}
	else {
		return false;
	}
}

//Counts the nighbors of a cell
int countNeighbors(genType &gen, int r, int c) {
	int result = 0;
	for (int i = r - 1; i <= r + 1; i++) {
		for (int j = c - 1; j <= c + 1; j++) {
			if (gen[i][j] == Alive) {
				result++;
			}
		}
	}

	//so it do not count it self.
	if (gen[r][c] == Alive) {
		result--;
	}
	return result;
}

//Fills the board with dead inhabitants.
void initGame(genType &gen) {

	for (int r = 0; r < ROWS; r++) {
		for (int c = 1; c < COLS; c++) {
			gen[r][c] = Dead;
		}
	}
	setInitGen(gen);
}

//prints out the board.
void showGeneration(genType &gen) {
	cout << endl;
	for (int r = 1; r < ROWS; r++) {
		for (int c = 1; c < COLS; c++) {
			if (gen[r][c] == Alive) {
				cout << " O";
			}
			else {
				cout << " .";
			}
			
		}
		cout << endl;
	}
}


//Asks user to set a start formation.
void setInitGen(genType &gen) {
	int answer = 10;
	while (answer > 3 || answer < 0) {
		cout << "Set startformation\n 1 glider \n 2 Semaphore\n 3 Set own formation \n";
		cin >> answer;
	}
	switch (answer) {
		case Glider:
			setGlider(gen);
			break;
		case Semiphore:
			setSemaphore(gen);
			break;
		case Manually:
			setUserFormation(gen);
	}
}


void setGlider(genType &gen) {
	gen[1][2] = Alive;
	gen[2][3] = Alive;
	gen[3][1] = Alive;
	gen[3][2] = Alive;
	gen[3][3] = Alive;
}

void setSemaphore(genType &gen) {
	gen[6][1] = Alive;
	gen[6][2] = Alive;
	gen[6][3] = Alive;

}


//Takes a formation from the user. 
void setUserFormation(genType &gen) {
	int r;
	int c;
	cout << "Set formation. < row *space* coll > Finish with <0 0>: ";

	do {
		cin >> r;
		cin >> c;
		if (r < ROWS && c < COLS) {
			gen[r][c] = Alive;
		}
		else {
			cout << "A number / some cells was outside the board. It was skipped" << endl;
		}
	} while (r != 0 && c != 0);

}