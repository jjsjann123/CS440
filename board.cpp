/* TODO:
 * 
 */
#include "board.h"
#include <iostream>

using namespace std;

Board::Board(unsigned int size) {
    boardSize = size;
    board.resize(size, vector<char>(size, '-'));
}

//Get cell's value
int Board::getValue(unsigned int row, unsigned int col) {
    if (row > boardSize || col > boardSize) {
        cout << "Error: Board::getValue out of boardSize range" << endl;
        exit(1);
    }
    return board[row][col];
}

//Set cell's value
void Board::setValue(unsigned int row, unsigned int col, char val) {
    if (row > boardSize || col > boardSize) {
        cout << "Error: Board::setValue out of boardSize range" << endl;
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
bool Board::isAHit(unsigned int row, unsigned int col) {
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
bool Board::isValidPosition(int length, bool isVertical, unsigned int row, unsigned int col) {

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
