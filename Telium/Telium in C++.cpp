// Telium in C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> 
#include <string> 
#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

void Clear_Console() {
    system("cls");
}

using namespace std;

int Select_Difficulty() {
    int Difficulty;
    cout << "1 - Easy" << endl << "2 - Medium" << endl << "3 - Hard" << endl << "4 - Super Hard" << endl;
    cout << "Select your Difficulty:  ";
    cin >> Difficulty;
    Clear_Console();

    return Difficulty;
}

int Display_Map() {
    cout << "       10 ------------ 11       " << endl;
    cout << "       |               |        " << endl;
    cout << "17 --- 9 ----- 2 ----- 3 --- 12 " << endl;
    cout << "|      |       |       |     |  " << endl;
    cout << "|      8 ----- 1 ----- 4     |  " << endl;
    cout << "|      |       |       |     |  " << endl;
    cout << "16 --- 7 ----- 6 ----- 5 --- 13 " << endl;
    cout << "       |               |        " << endl;
    cout << "       15 ------------ 14       " << endl;

    return 0;
}

list<int> Give_Possible_Moves(int cell) {

    cout << cell << endl;
    cout << endl;
    list<int> Available_Moves;

    int matrix[17][5]{
        {1,2,4,6,8},
        {2,1,3,9,0},
        {3,2,4,11,12},
        {4,1,3,5,0},
        {5,4,6,13,14},
        {6,1,5,7,0},
        {7,6,8,15,16},
        {8,1,7,9,0},
        {9,2,8,10,17},
        {10,9,11,0,0},
        {11,3,10,0,0},
        {12,3,13,0,0},
        {13,5,12,0,0},
        {14,5,15,0,0},
        {15,7,14,0,0},
        {16,7,17,0,0},
        {17,9,16,0,0},
    };
    for (int i = 0; i < 17; i++) {
        if (matrix[i][0] == cell) {
            for (int j = 0; j < 5; j++) {
                if (matrix[i][j] == 0) {
                    ;
                }
                else if (matrix[i][j] == cell) {
                    ;
                }
                else {
                    Available_Moves.push_back(matrix[i][j]);
                }
            }
            break;
        }
    }
    for (int Moves : Available_Moves) {
        cout << Moves << endl;
    }

    return Available_Moves;
}

int move(int Current_Cell) {

    list<int> Available_Moves;
    Available_Moves = Give_Possible_Moves(Current_Cell);

    bool Correct_Choice = false;
    int Cell_Choice = 0;


    while (Correct_Choice == false) {

        cout << "Enter the cell you would like to move to:  ";
        cin >> Cell_Choice;

        for (int Moves : Available_Moves) {
            if (Cell_Choice == Moves) {
                Correct_Choice = true;
            }
        }
    }


    return Cell_Choice;
}

int main() {
    int Difficulty = Select_Difficulty();
    Display_Map();

    int Current_Cell = 1;

    Current_Cell = move(Current_Cell);

    cout << Current_Cell;

    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
