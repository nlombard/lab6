//main.cpp
//main program for Sudoku
//Nicholas Lombardo

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Puzzle.h"
#include <string>
using namespace std;

int main(){
string file; //file string for input file
//easy
Puzzle<int> mySudoku("easy.txt"); //intialize Puzzle object for easy.txt file
cout << endl << "easy.txt" << endl;
mySudoku.play(); //solve the puzzle
cout << endl << "----------------------------" << endl << endl;
//medium
Puzzle<int> mySudoku1("medium.txt"); //init Puzzle object for medium.txt file
cout << endl << "medium.txt" << endl;
mySudoku1.play(); //solve
cout << endl << "----------------------------" << endl << endl;
//hard
Puzzle<int> mySudoku2("cc1.txt"); //init Puzzle object for cc1.txt file
cout << endl << "cc1.txt" << endl;
mySudoku2.play(); //solve
cout << endl << "----------------------------" << endl << endl;

//search custom file
cout << "Type file to use: (type q to quit): ";
cin >> file;
string quit;
quit = 'q';
	if(file == quit){
		return 1;
	}
	else{
		Puzzle<int> mySudokuEnter(file.c_str()); //initalize for custom file, assumes it exists
		cout << endl << file << endl;
		mySudokuEnter.play(); //solve
	}
return 0;
}
