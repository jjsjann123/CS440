/* TODO:
 *
 */
#ifndef BOARD_H
#define BOARD_H
#include "ship.h"
#include <vector>
#include <iostream>

struct Coords {
    Coords(int Row, int Col) : 
        row(Row), col(Col) {}
    int row, col;
};

class Board {
public: 
    //Constructor: sizes the board and sets all positions to '-'
    Board(int size);

    //setters/getters
    char getValue(int row, int col);
    void setValue(int row, int col, char val);
    int getBoardSize() { return boardSize; }
    void displayBoard();

    //Returns true if position contains a ship
    virtual bool isAHit(int row, int col);
    virtual bool isAHit(Coords* coords);

    //Returns true if specified position is a valid placement on current board
    bool isValidPosition(int length, bool isVertical, int row, int col);

    //Places the ship on the board by marking position with the ship's ID
    void markShipPosition(Ship *ship);

private:
    std::vector< std::vector<char> > board;
    int boardSize;
};

#endif
