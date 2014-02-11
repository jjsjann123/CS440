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
    Board(unsigned int size);

    //setters/getters
    int getValue(unsigned int row, unsigned int col);
    int getBoardSize() { return boardSize; }
    void setValue(unsigned int row, unsigned int col, char val);
    void displayBoard();

    //Returns true if position contains a ship
    bool isAHit(unsigned int row, unsigned int col);
    bool isAHit(Coords* coords);

    //Returns true if specified position is a valid placement on current board
    bool isValidPosition(int length, bool isVertical, unsigned int row, unsigned int col);

    //Places the ship on the board by marking position with the ship's ID
    void markShipPosition(Ship *ship);

private:
    std::vector< std::vector<char> > board;
    int boardSize;
};

#endif
