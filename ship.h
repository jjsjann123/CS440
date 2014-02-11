/* TODO:
 *
 */
#ifndef SHIP_H
#define SHIP_H
#include <vector>

enum ShipType {
    CARRIER     = 5, 
    BATTLESHIP  = 4, 
    DESTROYER   = 3, 
    PATROL      = 2, 
    ORE         = 1
};

//A ship is a vector of ShipData
//used to tell where ship sits and where it has been hit
struct ShipData {
    int row, col;
    bool beenHit;
};

class Ship {
public:
    Ship(ShipType type, char id); 

    //setters/getters
    int getSternRow()       { return sternRow; }
    int getSternCol()       { return sternCol; }
    int getLength()         { return length; }
    bool isVertical()       { return vertical; }
    char getID()            { return ID; }
    
    //Assigns each cell of the ship (ShipData vector) to a board cell and marks as not hit
    void setShipData(bool isVertical, unsigned int sternRow, unsigned int sternCol);

private:
    char ID;
    unsigned int length;
    bool vertical;
    int sternRow, sternCol;

    //a ship is a vector of ShipData
    std::vector<ShipData> shipData;
};

#endif
