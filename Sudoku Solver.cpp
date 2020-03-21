#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Sudokusquare{
public:
	//constructors
	Sudokusquare(){}
	Sudokusquare(int col, int rows, int actual) {	// if  not set a number is given then vector 
		column = col; row = rows; Actualnumber = actual;
		if (actual == 0){
			for (int i = 1; i < 10; i++){
				PossibleNumbers.push_back(i);
			}
		}
		if (col >= 0 && col <= 2){ // set each individual square into their big squares also for easier use later
			if (row >= 0 && row <= 2){
				bigsquare = 1;
			}
			if (row >= 3 && row <= 5){
				bigsquare = 2;
			}
			if (row >= 6 && row <= 8){
				bigsquare = 3;
			}
		}
		if (col >= 3 && col <= 5){
			if (row >= 0 && row <= 2){
				bigsquare = 4;
			}
			if (row >= 3 && row <= 5){
				bigsquare = 5;
			}
			if (row >= 6 && row <= 8){
				bigsquare = 6;
			}
		}
		if (col >= 6 && col <= 8){
			if (row >= 0 && row <= 2){
				bigsquare = 7;
			}
			if (row >= 3 && row <= 5){
				bigsquare = 8;
			}
			if (row >= 6 && row <= 8){
				bigsquare = 9;
			}
		}

	}
	~Sudokusquare(){}
	//different variables for each Sudokusquare
	vector <int> PossibleNumbers; // vector containing all possible numbers for that square;
	int column;						// column from 1-9
	int row;						// row from 1-9
	int bigsquare;					// way of ordering the big squares from top left to bottom right
	int Actualnumber;				// if found the actual number of the square is written


	//functions
	int givenumber(){					// returns the number present in that square
		return Actualnumber;
	}
	int givesquare(){
		return bigsquare;
	}
	void setsquare(int NumSet){			// sets the number within a square (only to be used to 
		Actualnumber = NumSet;

	}
	bool hasnumber(){
		if (Actualnumber > 0){
			return true;
		}
		else return false;
	}
	void RemoveImossible(int Number_to_remove){ // remove a specific number from a vector if found to be impossible
		int vectorsize = PossibleNumbers.size();	// iterates through to find the number then removes it.
		for (int i = 0; i < vectorsize; i++){	
			if (PossibleNumbers[i] == Number_to_remove){
				PossibleNumbers.erase(PossibleNumbers.begin() + i);
					break;
			}
		}
	}
};

class EntireBoard : public Sudokusquare{
public:
	EntireBoard(){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				Squares[i][j] = new Sudokusquare(i, j, 0);
			}
		}
	}
	~EntireBoard(){}

	Sudokusquare* Squares[9][9];
	void printboard(){
		cout << "   ||| 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||| \n"; // column numbering just for ease
		cout << "===|||===|===|===||===|===|===||===|===|===||| \n";

		for (int i = 0; i < 9; i++){
			if (i == 3 || i == 6 || i == 9){
				cout << "===|||===|===|===||===|===|===||===|===|===||| \n";
			}
			else{
				if (i != 0){
					cout << "---|||---|---|---||---|---|---||---|---|---||| \n";
				}
			}
			cout << " " << i + 1 << " |||";
			for (int j = 0; j < 9; j++){
				cout << " " << Squares[j][i]->givenumber() << " |";
				if (j == 2 || j == 5){
					cout << "|";
				}
				if (j == 8){
					cout << "|| \n";
				}
			}
		}
		cout << "===|||===|===|===||===|===|===||===|===|===||| \n";
	}
	void setsquare(int cols, int rows, int number){ // used to change the number in the square
		Squares[cols][rows]->setsquare(number);
	}

	//here are the functions that will test a square against all other squares in the same row + column and big square
	void testsquare(int cols, int rows){//
		if (!Squares[cols][rows]->hasnumber()){ // if a square does not have a number
			for (int i = 0; i < 9; i++){ // test all the rows (single column)
				if (Squares[cols][i]->hasnumber()){		// checks isnt the same square + has number
					Squares[cols][rows]->RemoveImossible(Squares[cols][i]->givenumber());
				}
			}
			for (int i = 0; i < 9; i++){ // test all the columns (single row)
				if (Squares[i][rows]->hasnumber()){
					Squares[cols][rows]->RemoveImossible(Squares[i][rows]->givenumber());
				}
			}
			for (int i = 0; i < 9; i++){ // test the big square.
				for (int j = 0; j < 9; j++){
					if (Squares[i][j]->hasnumber() &&
						((Squares[cols][rows]->givesquare()) == (Squares[i][j]->givesquare()))){
						Squares[cols][rows]->RemoveImossible(Squares[i][j]->givenumber());
					}
				}
			}
		}
	}
	// a second test used to check the other squares within the same big square(row/col too?. 
	//If there are no other available spaces must set this square to that number
	void advancedsquaretest(int cols, int rows){
		if (!Squares[cols][rows]->hasnumber()){		// if chosen square doesnt have number
			int CurrentPossibleNumbers = Squares[cols][rows]->PossibleNumbers.size();
			for (int j = 0; j < CurrentPossibleNumbers; j++){
				int SharedNumber = 0;
				for (int i = 0; i < 9; i++){			// start testing the rows
				if ((!Squares[cols][i]->hasnumber()) && (i != rows)){		// if tested square doesnt have a number either and not same square
						// gets number of possible numbers
					int TestingPossibleNumbers = Squares[cols][i]->PossibleNumbers.size();	
						for (int k = 0; k < TestingPossibleNumbers; k++){
							if ((Squares[cols][rows]->PossibleNumbers[j]) == (Squares[cols][i]->PossibleNumbers[k])){
								SharedNumber = 1;
							}
						}
							
						}
					
				}
				if (SharedNumber == 0){
					Squares[cols][rows]->setsquare(Squares[cols][rows]->PossibleNumbers[j]);
				}
			} // MOVE ONTO THE SAME ROW
			for (int j = 0; j < CurrentPossibleNumbers; j++){
				int SharedNumber = 0;
				for (int i = 0; i < 9; i++){			// start testing the rows
					if ((!Squares[i][rows]->hasnumber()) && (i != cols)){		// if tested square doesnt have a number either and not same square
						// gets number of possible numbers
						int TestingPossibleNumbers = Squares[i][rows]->PossibleNumbers.size();
						for (int k = 0; k < TestingPossibleNumbers; k++){
							if ((Squares[cols][rows]->PossibleNumbers[j]) == (Squares[i][rows]->PossibleNumbers[k])){
								SharedNumber = 1;
							}
						}

					}

				}
				if (SharedNumber == 0){
					Squares[cols][rows]->setsquare(Squares[cols][rows]->PossibleNumbers[j]);
				}
			} 
			for (int j = 0; j < CurrentPossibleNumbers; j++){
				int SharedNumber = 0;
				for (int i = 0; i < 9; i++){			// start testing the rows
					for (int l = 0; l < 9; l++){
						if ((!Squares[i][l]->hasnumber()) && !(i == cols && l == rows) // THIS
							&& (Squares[i][l]->bigsquare == Squares[cols][rows]->bigsquare)){		// if tested square doesnt have a number either and not same square
							// gets number of possible numbers
							int TestingPossibleNumbers = Squares[i][l]->PossibleNumbers.size();
							for (int k = 0; k < TestingPossibleNumbers; k++){
								if ((Squares[cols][rows]->PossibleNumbers[j]) == (Squares[i][l]->PossibleNumbers[k])){
									SharedNumber = 1;
								}
							}
						}
					}
				}
				if (SharedNumber == 0){
					Squares[cols][rows]->setsquare(Squares[cols][rows]->PossibleNumbers[j]);
				}
			}
		}
	}
	void squaretest3(int cols, int rows){			// information retrieval for the 
		if (!Squares[cols][rows]->hasnumber()){
			if (Squares[cols][rows]->PossibleNumbers.size() == 2){			// if a square has two possible numbers
				for (int i = 0; i < 9; i++){
					for (int j = 0; j < 9; j++){
						if (!Squares[i][j]->hasnumber() && !(i == cols && j == rows)){
							if (Squares[cols][rows]->PossibleNumbers == Squares[i][j]->PossibleNumbers){
								if ((i == cols) && (Squares[cols][rows]->bigsquare == Squares[i][j]->bigsquare)){
									for (int z = 0; z < 2; z++){
										for (int y = 0; y < 9; y++){
											if (y != rows && y != j){
												Squares[cols][y]->RemoveImossible((Squares[cols][rows]->PossibleNumbers[z]));
											}
										}
									}
								}
								if ((j == rows) && (Squares[cols][rows]->bigsquare == Squares[i][j]->bigsquare)){
									for (int z = 0; z < 2; z++){
										for (int y = 0; y < 9; y++){
											if (y != cols && y != i){
												Squares[y][rows]->RemoveImossible((Squares[cols][rows]->PossibleNumbers[z]));
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	void Finaltest(int col, int row){ // test if in a big square a row has 3 numbers
		if (!Squares[col][row]->hasnumber()){
			if (Squares[col][row]->PossibleNumbers.size() == 3){	// Test + 2 and  -2 rows and cols(seperate)
				int commonrow = 0;
				for (int i = 0; i < 9; i++){
					if (!Squares[col][i]->hasnumber() && i != row 
						&& Squares[col][row]->bigsquare == Squares[col][i]->bigsquare){
						if (Squares[col][row]->PossibleNumbers == Squares[col][i]->PossibleNumbers){
							commonrow++;
						}
					}
				}
				if (commonrow == 2){

				}
			}
		}
	}
};


int main()
{
	EntireBoard TestBoard;
	TestBoard.printboard();
	bool userinput(true);
	while (userinput){
		int row;
		int column;
		int numtoset;
		cout << "Write a Column. \n"; // this is where  the program asks you to input the values
		cin >> column;				// ideally i would like to change this so that it is automatic on a website.
		cout << "Write a row. \n"; cin >> row;
		cout << "Write a number to fill that cell. If zero will continue program. \n"; cin >> numtoset;
		if (numtoset == 0){
			userinput = false;
		}
		else{
			TestBoard.setsquare(column - 1, row - 1, numtoset);
			system("CLS");
			TestBoard.printboard();
		}
	}
		for (int i = 0; i < 1000; i++){ 
			for (int j = 0; j < 9; j++){
				for (int k = 0; k < 9; k++){
					TestBoard.testsquare(j, k);
					if (TestBoard.Squares[j][k]->PossibleNumbers.size() == 1){
						int Definitenumber = TestBoard.Squares[j][k]->PossibleNumbers[0];
						TestBoard.Squares[j][k]->setsquare(Definitenumber);
					}
					TestBoard.advancedsquaretest(j, k);
					TestBoard.squaretest3(j, k);
				}
			}	
		}

	system("CLS");
	TestBoard.printboard();
	system("PAUSE");
	return 0;
};
