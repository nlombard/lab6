//Puzzle.h
//Nicholas Lombardo
//Puzzle class for Sudoku game
//stores puzzle and couts puzzle

#ifndef PUZZLE_H
#define PUZZLE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

template<typename T>
class Puzzle{	
	public:
		Puzzle(string); //constructor
		void displayBoard(); //display function for printing board
		void display3dCol(int, int);
		int checkValid(int, int, int); //checks whether placing certain number in grid is valid
		int checkGrid(int,int,int); //checks if mini grid is valid for placement of number
		void play(); //main game to play calls other functions to simulate soduku
		void checkPoss();
		void removeNum(int, int, int);
		void placeNum(int, int, int);
		int didWin3D(); //did win function to check if there are no zeros on the board
		void checkSingleValue(); //check whole board for single values
		void singleton();
		int find1(int[10]);
		void singletonRow();
		void singletonCol();
		void singletonGrid();
	private:
		vector<vector<  T > > Board; //storage for Board, a 2D vector
		vector<vector<vector<  T > > > Poss;
		vector<vector < T > > OriginalBoard; //storage for OriginalBoard, a 2D vector of original values
};

//Function Implementations
template <typename T>
Puzzle<T>::Puzzle(string dataFile){ //constructor
	int i = 0, j = 0;
	T value; //value of data type T from template
	ifstream infile; //creates stream variable
	vector<T> rowVec; //vector for storage of row, then put into vector of vector
	vector<vector < T > > twoDimBoard;
	infile.open(dataFile.c_str()); //open datafile for read in
	for (int i = 0; i < 9; i++){
		for( int j = 0; j < 9; j++) {
			infile >> value; //read in value
			rowVec.push_back(value); //put into vector
		}
		Board.push_back(rowVec); //put vector into board
		rowVec.clear(); //clear storage vector for next row
	}
	OriginalBoard = Board; //set OrignalBoard equal to the Board read in with no user changes
	Poss.push_back(Board);

	//initalize 3d rows!
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			for(int k = 0; k < 9; k ++){
					if(Board[j][k] == 0)
						rowVec.push_back(i+1); //now board has corresponding values for the corresponding spots on 3d vector ie. pos 8 has a value of 8.		
					else
						rowVec.push_back(0); //no values because number is already set
			}	
			twoDimBoard.push_back(rowVec);
			rowVec.clear();
		}
		Poss.push_back(twoDimBoard);
		rowVec.clear();
		twoDimBoard.clear();
	}
}
template <typename T>
void Puzzle<T>::displayBoard(){	//display function
	cout << "    "; //formating
	for (int k = 1; k < 10; k++){
		cout << k << " "; //output numbers for grid
		if(k%3 == 0){ //every 3 add two spaces
			cout << "  ";
		}
	}
	cout << endl << "    - - -   - - -   - - -" <<  endl; //formating
	for (int i = 0; i < 9; i++){
		cout << i + 1 << " | "; //output for grid
			for( int j = 0; j < 9; j++) {
			cout << Poss[0][i][j] << " "; //display board number and space
			if(j%3 == 2){
			cout << "| "; //every three add a pipe for seperation of output
			}
		}
		if(i%3 == 2){
			cout << endl << "    - - -   - - -   - - -"; //formating
		}
			cout << endl;
	}
	cout << endl;
}
template <typename T>
int Puzzle<T>::checkValid(int x, int y, int z){
	if((x < 0)||(x > 9)||(y < 0)||(y > 9)||(z>9)||(z<0)){
	//	cout << "Error: row or col and/or num out of range!" << endl;
		return 0; //leave if numbers are out of bounds		
	}
	int countRow[10]; //initalize count array
	int countCol[10]; //initalize count array
	for(int i=0;i<10;i++){
		countRow[i] = 0; //set values to 0
		countCol[i] = 0; //set values to 0
	}
	if(Poss[0][x][y] != 0){
	//	cout << "Error: cannot change original values." << endl;
		return 0; //cannot place invalid
	}
	for(int i=0;i<9;i++){
		countRow[Poss[0][x][i]]++; //increment count	
	}
	if(countRow[z]>=1){
		if(z == 0){
			return 1; // allow reset to 0 even if there are zeros in the row
		}
	//	cout << "Error: number already exists in row!" << endl;
		return 0; //cannot place invalid because more than one in row
	}
	for(int i=0;i<9;i++){
		countCol[Poss[0][i][y]]++; //increment count
	}
	if(countCol[z]>=1){
		if(z == 0){
			return 1; //allow reset to 0 even if there are zeros in the col
		} 
	//	cout << "Error: number already exists in col!" << endl;
		return 0; //cannot place invalid because more than one in row
	}
	if(checkGrid(x,y,z) == 0){
	//	cout << "Error: number already exists in Grid" << endl;
		return 0; //return if number is in Grid
	}
	return 1; // if no errors then it can be placed
}
template <typename T>
int Puzzle<T>::checkGrid(int x, int y, int z){
	int i = (x/3)*3; //start position using integer division to find correct Grid
	int j = (y/3)*3;
	int count[10];
	for(int l = 0; l < 10; l++){
		count[l] = 0; //initalize count values to zero
	}
	for(int it1 = 0; it1 < 3; it1++){
		for(int k = 0; k < 3; k++){
			count[Poss[0][i][j]]++;
			j++; //increment i and j to next spots
		}
		i++; // increment row
		j = (y/3)*3; //reset column
	}
	if(count[z]>=1){
		if(z == 0){
			return 1; //allow for 0 to be placed in Grid
		}
		return 0;
	}
	return 1; // if no errors then return 1
}
template <typename T>
void Puzzle<T>::play(){
	int count = 1;
	displayBoard();
	while(!didWin3D()){
		cout << "Round: " << count << endl;
		checkPoss();
		checkSingleValue();
		singletonRow();
		//singletonCol();
		//singletonGrid();
		displayBoard();
		count ++;
	}
}
template <typename T>
void Puzzle<T>::display3dCol(int r, int c){
	cout << "At locatioin " << r+1 << ", " << c+1 << " :" << endl;
	for(int i = 0; i < 10; i ++){
		cout << Poss[i][r][c] << endl;
	}
}
	
template <typename T>
int Puzzle<T>::didWin3D(){ //did win function to check if there are no zeros on the board
	for(int i=0;i<9;i++){ //if every placement is checked then when there are no zeros left the board is solved
		for(int j=0;j<9;j++){
			if(Poss[0][i][j] == 0)
				return 0; //still an empty spot
		}
	}
	return 1; //return 1 if after the whole board is checked there is no zeros (empty spots)
}
template <typename T>
void Puzzle<T>::checkPoss(){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			for(int num=1; num<10; num++){
				if(checkValid(i,j,num)==0){
					removeNum(num,i,j);
				}
			}
		}
	}

}
template <typename T>
void Puzzle<T>::removeNum(int num, int row, int col){
	Poss[num][row][col] = 0;
}
template <typename T>
void Puzzle<T>::checkSingleValue(){ //check whole board for single values
	int count = 0;
	int num = 0;
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			for(int k=0; k<10; k++){
				if(Poss[k][i][j] != 0){
					count++; //count needs to equal one to be placed
					num = Poss[k][i][j]; //grab number to be used if count equals one below
				}
			}
			if(count == 1){
				Poss[0][i][j] = num; //if count equals one then set the number grabbed
			} //continue to check next space
			count = 0; //reset count	
		}
	}
}
template <typename T>
void Puzzle<T>::singletonRow(){	
	int count[10];
	for(int i = 0; i<10; i++){
		count[i] = 0; //initalize count to 0
	}
	int num = 0;
	int single = 0;
	for(int i=0; i<9; i++){ //row
		for(int j=0; j<9; j++){ //col 
			for(int k=0; k<10; k++){ //3d
				if(Poss[k][i][j] != 0){
					count[k]++; //count at location increased
					num = Poss[k][i][j]; //grab number to be used if count equals one below
				}
			}
		}
		single = find1(count);
		if(single != 0){
		//	for(int stack=1;stack<10;stack++){
			for(int cols=0;cols<9;cols++){ //search cols for singleton value to place
				if(Poss[single][i][cols] == single){ //if the possition in the stack of possabilities is equal to the singleton then place it	
					Poss[0][i][cols] = single;
				}
			}
		//	}
		}
		for(int i=0;i<10;i++){
			count[i] = 0; //reset count for the row
		}	
	}
}
template <typename T>
void Puzzle<T>::singletonCol(){	
	int count[10];
	for(int i = 0; i<10; i++){
		count[i] = 0; //initalize count to 0
	}
	int num = 0;
	int single = 0;
	for(int i=0; i<9; i++){ //col
		for(int j=0; j<9; j++){ //row 
			for(int k=0; k<10; k++){ //3d
				if(Poss[k][j][i] != 0){
					count[k]++; //count at location increased
					num = Poss[k][j][i]; //grab number to be used if count equals one below
				}
			}
		}
		single = find1(count);
		if(single != 0){
		//	for(int stack=1;stack<10;stack++){
			for(int rows=0;rows<9;rows++){ //search cols for singleton value to place
				if(Poss[single][rows][i] == single){ //if the possition in the stack of possabilities is equal to the singleton then place it	
					Poss[0][rows][i] = single;
				}
			}
		//	}
		}
		for(int i=0;i<10;i++){
			count[i] = 0; //reset count for the row
		}	
	}
}
template <typename T>
void Puzzle<T>::singletonGrid(){
	int sCount[10]; //singletonCount
	int i; //start position using integer division to find correct Grid
	int j;
	int startRow;
	int startCol;
	int count[10];
	int single = 0;
	
for(int x=0;x<9;x+=3){
for(int y=0;y<9;y+=3){
	i = (x/3)*3; //start position using integer division to find correct Grid
	j = (y/3)*3;
	startRow = i;
	startCol = j;	
	for(int l = 0; l < 10; l++){
		sCount[l] = 0; //initalize count values to zero
	}
	for(int it1 = 0; it1 < 3; it1++){
		for(int k = 0; k < 3; k++){
			for(int stack = 1; stack < 10; stack++){
				if(Poss[stack][i][j] != 0){
					sCount[Poss[stack][i][j]] ++; //increment the count
				}
			}
			j++; //increment i and j to next spots
		}
		i++; // increment row
		j = startCol; //reset column
	}
	single = find1(sCount);//find singleton value
	if(single != 0){
		startRow = (x/3)*3;
		startCol = (y/3)*3;
		int i1 = startRow;
		int j1 = startCol;
		for(int k1=0; k1<3;k1++){
			for(int k2=0;k2<3;k2++){
				if(Poss[single][i1][j1] == single){
					Poss[0][i1][j1] = single;
				}
			j1++;
			}
			i1++;
		}		
	}
	//look for singlton value in grid
	//place value
	}
	}
}
template <typename T>
int Puzzle<T>::find1(int count[10]){ //finds value of 1 in count
	for(int i=0;i<10;i++){
		if(count[i] == 1){
			return(i);
		}
	}
	return(0);
}
#endif
