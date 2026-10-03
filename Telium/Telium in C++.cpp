// Telium in C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> 
#include <string> 
#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <limits>

using namespace std;

void Clear_Console() {
    //Clears the Console
    system("cls");
}

int Random_Number(int Number) {
    //Generates a random Number from 0 - "Number"
    srand(time(NULL));
    int Rand_Num = rand() % Number;
   
    return Rand_Num;
}

int Choose_Radnom_Item_From_List(list<int> List1) {
    int Rand_Num = Random_Number(List1.size());
    int Placeholder = -1;
    int Item;

    for (int i : List1) {
        Placeholder++;
        if (Rand_Num == Placeholder) {
            Item = i;
        }
    }
    return Item;
}

int Select_Difficulty() {
    //Selects the Difficulty for this game and returns it to main
    int Difficulty;
    cout << "1 - Easy" << endl << "2 - Medium" << endl << "3 - Hard" << endl << "4 - Super Hard" << endl;
    cout << "Select your Difficulty:  ";
    cin >> Difficulty;
    Clear_Console();

    return Difficulty;
}

int Display_Map() {
    //Displays the Map
    cout << "       10 ------------ 11       " << endl;
    cout << "       |               |        " << endl;
    cout << "17 --- 9 ----- 2 ----- 3 --- 12 " << endl;
    cout << "|      |       |       |     |  " << endl;
    cout << "|      8 ----- 1 ----- 4     |  " << endl;
    cout << "|      |       |       |     |  " << endl;
    cout << "16 --- 7 ----- 6 ----- 5 --- 13 " << endl;
    cout << "       |               |        " << endl;
    cout << "       15 ------------ 14       " << endl << endl;

    return 0;
}

list<int> Set_Up_Map() {
    //Randomly Places all the items across the map (exluding 1)
    list<int> Final_Setup;
    list<int> Available_Rooms = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    srand(time(NULL));

    //Determines where the quees will be placed, can only be placed on the outside rooms (10-17)
    int Queen_Spawn = Random_Number(7) + 11;
    Final_Setup.push_back(Queen_Spawn);

    //Determines where the 5 Aliens will be placed
    int Num_Of_Aliens = 5;
    int Alien_Spawn;
    for (int i = 0; i < Num_Of_Aliens; i++) {
        Alien_Spawn = (rand() % 16) + 2;
        Final_Setup.push_back(Alien_Spawn);
    }

    //Determines where the 3 fuel tanks will be placed
    int Num_Of_Fuel_Tanks = 3;
    int Fuel_Spawn;
    for (int i = 0; i < Num_Of_Fuel_Tanks; i++) {
        Fuel_Spawn = (rand() % 16) + 2;
        Final_Setup.push_back(Fuel_Spawn);

    }

    //Determines where the 2 connected vents will be placed
    int Num_Of_Vents = 2;
    int Vent_Spawn;
    for (int i =0; i < Num_Of_Vents; i++) {
        Vent_Spawn = (rand() % 16) + 1;
        Final_Setup.push_back(Vent_Spawn);
    }

    //Returns a list with the hexes of all the placements are, in this order: (Queen, Alien, Alien, Alien, Alien, Alien, Fuel, Fuel, Fuel, Vent, Vent)
    return Final_Setup;
}

list<int> Give_Possible_Moves(int cell) {
    //Takes a cell, and returns all the cells that can be moved to from that cell
    cout << endl;
    list<int> Available_Moves;

    // Cell number is the leftmost value on each row, then it is the cells that can be moved from that cell on the rest of that row 
    int matrix[18][5]{
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
        {18,18,0,0,0},
    };

    //Goes through the matrix until it find the requested cell number, then loops through that row and adds the numbers of the cells that can be moved to to the Available_Moves list
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
    
    return Available_Moves;
}

int move(int Current_Cell) {
    //Used to move the player throughout the rooms

    list<int> Available_Moves;
    //Uses the Give_Possible_Moves function to get a list of the cells that can be moved to from the current cell
    Available_Moves = Give_Possible_Moves(Current_Cell);

    bool Correct_Choice = false;
    int Cell_Choice = 0;

    // Stays in the while loop until the user enters a valid cell/input
    while (Correct_Choice == false) {

        cout << "Enter the cell you would like to move to:  ";

        //Stays in the secondary while loop until the user enters a valid integer
        while (!(cin >> Cell_Choice)) {
            cout << "Please enter a valid input  " << endl << "Enter the cell you would like to move to ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //Determines whether the users entry is outside the valid range
        if (Cell_Choice < 1 || Cell_Choice > 17) {
            Correct_Choice = false;
            cout << "Please enter a valid input" << endl;
        }
        else {
            //If the users entry is valid, exits the while loop 
            for (int Moves : Available_Moves) {
                if (Cell_Choice == Moves) {
                    Correct_Choice = true;
                }
            }
        }
    }

    return Cell_Choice;
}

list<int> Move_Aliens(list<int> Set_Up) {
    list<int> Alien_Loc;
    int iterator = -1;
    list<int> New_Set_Up;
    list<int> New_Alien_Loc;
    
    for (int Locs : Set_Up) {
        iterator++;
        if (iterator > 0 && iterator < 6) {
            Alien_Loc.push_back(Locs);
        }
    }
    
    for (int Locs : Alien_Loc) {
        list<int> Available_Moves = Give_Possible_Moves(Locs);
        int New_Move = Choose_Radnom_Item_From_List(Available_Moves);
        New_Alien_Loc.push_back(New_Move);
    }

    int iterator2 = -1;
    for (int i : Set_Up) {
        iterator2++;
        if (iterator2 > 0 && iterator2 < 6) {
            int Placeholder = 0;
            for (int j : New_Alien_Loc) {
                Placeholder++;
                if (Placeholder == iterator2) {
                    New_Set_Up.push_back(j);
                }
            }
        } else {
            New_Set_Up.push_back(i);
        }
    }

    return Set_Up;
}

int Check_Cell(int Cell, list<int> Set_Up) {
    //Defines lists/variables for the locations of the items, split into their respective catagories
    int Queen_Loc;
    list<int> Alien_Loc;
    list<int> Fuel_Loc;
    list<int> Vent_Loc;

    //Basiically goes through the Set_Up list and splits it into their catagories
    int iterator = -1;
    for (int Locs : Set_Up) {
        iterator++;
        if (iterator == 0) {
            Queen_Loc = Locs;
        } else if (iterator > 0 && iterator < 6) {
            Alien_Loc.push_back(Locs);
        } else if (iterator > 5 && iterator < 9) {
            Fuel_Loc.push_back(Locs);
        } else if (iterator > 8) {
            Vent_Loc.push_back(Locs);
        }
    }

    cout << Queen_Loc << endl;

    for (int Alien : Alien_Loc) {
        cout << Alien << " ";
    }

    cout << endl;

    for (int Fuel : Fuel_Loc) {
        cout << Fuel << " ";
    }

    cout << endl;
    
    for (int Vent : Vent_Loc) {
        cout << Vent << " ";
    }

    cout << endl;

    bool Is_Alien = (std::find(Alien_Loc.begin(), Alien_Loc.end(), Cell) != Alien_Loc.end());

     bool Is_Fuel = (std::find(Fuel_Loc.begin(), Fuel_Loc.end(), Cell) != Fuel_Loc.end());

    bool Is_Vent = (std::find(Vent_Loc.begin(), Vent_Loc.end(), Cell) != Vent_Loc.end());

    if (Is_Alien == true) {
        cout << "There is an enemy" << endl;
    }

    if (Is_Fuel == true) {
        cout << "There is a fuel tank" << endl;
    }

    if (Is_Vent == true) {
        cout << "There is an vent" << endl;
    }
    
    return 0;
}

int main() {
    //Starts with the user setting their difficulty
    int Difficulty = Select_Difficulty();

    //Defines the starting cell as 1
    int Current_Cell = 1;

    //Randomly places the items across the map
    list<int> Set_Up = Set_Up_Map();

    while (true) {
        //Keeps the game running for all eternity - will add the nessecary condition/s later

        //Displays the map and tells the user which cell they are currently in
        Display_Map();
        cout << "You currently are in cell " << Current_Cell;
        
        //Moves the user and checks what is in that cell
        Current_Cell = move(Current_Cell);
        Check_Cell(Current_Cell, Set_Up);

        Set_Up = Move_Aliens(Set_Up);
    }
    
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
