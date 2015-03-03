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
string file;
Puzzle<int> mySudoku("easy.txt");
cout << endl << "easy.txt" << endl;
mySudoku.play();
cout << endl << "----------------------------" << endl << endl;
Puzzle<int> mySudoku1("medium.txt");
cout << endl << "medium.txt" << endl;
mySudoku1.play();
cout << endl << "----------------------------" << endl << endl;
Puzzle<int> mySudoku2("cc1.txt");
cout << endl << "cc1.txt" << endl;
mySudoku2.play();
cout << endl << "----------------------------" << endl << endl;
cout << "Type file to use: (type q to quit): ";
cin >> file;
string quit;
quit = 'q';
if(file == quit){
	return 1;
}
else{
	Puzzle<int> mySudokuEnter(file.c_str());
	cout << endl << file << endl;
	mySudokuEnter.play();
}
return 0;
}
