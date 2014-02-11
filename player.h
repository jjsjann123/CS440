/* TODO: 
 * -check for sunk ship
 * -check for all ships sunk (lost game)
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "ship.h"
#include "board.h"
#include <vector>
#include <iostream>

class Player {
public:
    //Sets ID, creates a board, and adds ships to ships vector
    Player(int id, int boardSize);
    ~Player(); //destroys the board

    //displays the board and player ID
    void displayBoard(); 

    //setters/getters
    void setBoardValue(unsigned int row, unsigned int col, int val); 
    int getBoardValue(unsigned int row, unsigned int col);
    int getID() { return ID; }

    //loops through each ship and calls placeShip on it
    void placeShips();

    /*************************************** 
     * takes user input coordinates and orientation choice then calls...
     **  board->isValidPosition()    to check if coordinates are valid
     **  ship->setShipData()         to set the ships data (coordinates and hits) 
     **  board->markShipPosition()   to mark the board with ships position
     **  displayBoard()              to display the updated board with ship placed on it
     ***************************************/
    void placeShip(Ship *ship);

    //gets attack coordinates from player
    Coords* attack();

    //returns true on hit
    bool isAHit(Coords* coords) {
        return board->isAHit(coords);
    }

private:
    int ID;
    Board *board; //* for dynamic allocation via constructor
    std::vector<Ship> ships;
};

#endif
