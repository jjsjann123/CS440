/* TODO:
 * 
 */
#include "board.h"
#include <iostream>

using namespace std;

Board::Board(int size) {
    if (size < 0) {
        cout << "Error: board size must be positive -> " << size << endl;
        exit(1);
    }
    boardSize = size;
    board.resize(size, vector<char>(size, '-'));
}

//Get cell's value
char Board::getValue(int row, int col) {
    if (row < 0 || col < 0 || row > boardSize || col > boardSize) {
        cout << "Error: invalid Board::getValue coordinates -> " << row << ", " << col << endl;
        exit(1);
    }
    return board[row][col];
}

//Set cell's value
void Board::setValue(int row, int col, char val) {
    if (row < 0 || col < 0 || row > boardSize || col > boardSize) {
        cout << "Error: invalid Board::setValue coordinates -> " << row << ", " << col << endl;
        exit(1);
    }
    board[row][col] = val;
}

//is a mess because of formatting, but it works
void Board::displayBoard() {
    vector< vector<char> >::iterator row;
    vector<char>::iterator col;
    int i=0, j=0;
    cout << "  ";
    for (i = 0; i < boardSize; ++i) {
        printf("%3i", i);
    }
    cout << endl;
    for (row = board.begin(); row != board.end(); ++row, ++j) {
        cout << j << " ";
        for(col = row->begin(); col != row->end(); ++col) {
            printf("%3c", *col);
        }
        cout << endl;
    }
}

//Returns true if there is a ship at the specified location
bool Board::isAHit(int row, int col) {
    if (row < 0 || col < 0 || row > boardSize || col > boardSize) {
        cout << "Error: invalid Board::isAHit coordinates -> " << row << ", " << col << endl;
        exit(1);
    }
    if (board[row][col] != '-') {
        setValue(row, col, 'X');
        return true;
    }
    setValue(row, col, 'O');
    return false;
}
//Overloaded for encapsulation purposes
bool Board::isAHit(Coords* coords) {
    unsigned int row = coords->row;
    unsigned int col = coords->col;
    delete coords;
    return isAHit(row, col);
}

//Returns true if specified position is a valid placement on current board
bool Board::isValidPosition(int length, bool isVertical, int row, int col) {
    if (row < 0 || col < 0 || row > boardSize || col > boardSize ){
        cout << "Error: Board::isValidPosition invalid coordinates -> " << row << ", " << col << endl;
        exit(1);
    }

    if (isVertical) {
        //check that the ship fits on the board
        if ((row+length) > boardSize) {
            cout << "Vertically, ship(" << length << ") doesn't fit with stern at ";
            cout << row << "," << col << " ";
            cout << "when board =  " << boardSize << endl << endl;;
            return false;
        }
        //if ship fits, check that it isn't overlapping another ship
        else {
            for (int r = row; r < (row+length); ++r) {
                if (board[r][col] != '-') {
                    cout << "Placement violation at " << r << "," << col << endl;
                    return false;
                }
            }
        } 
    } 
    else {
        //check that the ship fits on the board
        if ((col+length) > boardSize) {
            cout << "Horizontally, ship(" << length << ") doesn't fit with stern at ";
            cout << row << "," << col << " ";
            cout << "when board =  " << boardSize << endl << endl;;
            return false;
        }
        //if ship fits, make sure it isn't overlapping another ship
        else {
            for (int c = col; c < (col+length); ++c) {
                if (board[row][c] != '-') {
                    cout << "Placement violation at " << row << "," << c << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

//Places the ship on the board by marking position with the ship's ID
void Board::markShipPosition(Ship *ship) {
    int length = ship->getLength();
    bool vertical = ship->isVertical();
    int row = ship->getSternRow();
    int col = ship->getSternCol();
    char ID = ship->getID();

    //if the ship is vertically oriented...
    if (vertical) {
        for (int r = row; r < (row+length); ++r) {
            board[r][col] = ID;
        }
    }
    //if the ship is horizontally oriented...
    else {
        for (int c = col; c < (col+length); ++c) {
            board[row][c] = ID;
        }
    }
}
