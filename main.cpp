//main.cpp
//main program for Sudoku
//Nicholas Lombardo

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Puzzle.h"

using namespace std;

int main(){
Puzzle<int> mySudoku("medium.txt");
cout << "Welcome to Sudoku the game, have fun!" << endl;
mySudoku.play();
cout << "Thanks for playing" << endl;
}
