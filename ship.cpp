/* TODO:
 * 
 */
#include "ship.h"

Ship::Ship(ShipType type, char id) {
    length = type;
    ID = id; 
    vertical = false;
    shipData.resize(type);
    sternRow = sternCol = 0;
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
