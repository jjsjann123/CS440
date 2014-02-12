/* TODO:
 * 
 */
#include "ship.h"
#include <iostream>
using namespace std;

Ship::Ship(ShipType type, char id) {
    length = type;
    ID = id; 
    vertical = false;
    shipData.resize(type);
    sternRow = sternCol = 0;
    numHits = 0;
    sunk = false;
}


//Assigns each cell of the ship (ShipData vector) to a board cell and marks as not hit
void Ship::setShipData(bool isVertical, unsigned int row, unsigned int col) {
    vertical = isVertical; 
    sternRow = row;
    sternCol = col;
    std::vector<ShipData>::iterator it;
    for (it = shipData.begin(); it != shipData.end(); ++it) {
        if (isVertical) { 
            it->row = row++;
            it->col = col;
        }
        else {
            it->row = row;
            it->col = col++;
        }
        it->beenHit = false;
    }
}

//Searches the ships cells for row, col and marks as hit
bool Ship::markAsHit(int row, int col) {
    std::vector<ShipData>::iterator it;
    for (it = shipData.begin(); it != shipData.end(); ++it) {
        if (it->row == row && it->col == col) {
            //mark hit and check if ship was sunk
            //If sunk, set sunk=true and display message
            it->beenHit = true;
            numHits++;
            hasBeenSunk();
            return true;
        }
    }
    return false;
}

bool Ship::hasBeenSunk() {
    if (numHits != length) {
        return false;
    }
    switch(length) {
        case 5:
            cout << "Carrier(5): ";
            break;
        case 4:
            cout << "Battleship(4): ";
            break;
        case 3:
            cout << "Destroyer(3): ";
            break;
        case 2:
            cout << "Patrol(2): ";
            break;
        case 1:
            cout << "Ore(1): ";
            break;
        default:
            cout << "Error in Ship::hasBeenSunk()\n";
            exit(-1);
            break;
    }
    cout << "has been sunk!\n";

   sunk = true;
   return true;
}
