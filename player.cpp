/* TODO: 
 *
 */
#include "player.h"
#include <iostream>
using namespace std;

//Constructor creates new board and ships for the player
Player::Player(int id, int boardSize) {
    ID = id;
    board = new Board(boardSize);

    //capital words are enums defined in ship.h
    //ships.push_back(Ship(CARRIER, '5'));
    //ships.push_back(Ship(BATTLESHIP, '4'));
    //ships.push_back(Ship(DESTROYER, '3'));
    ships.push_back(Ship(PATROL, '2'));
}

//Destructor destroys board
Player::~Player() {
    delete board;
}

//Displays the board and player ID
void Player::displayBoard() {
    cout << "PLAYER " << ID << endl;
    board->displayBoard();
}

void Player::setBoardValue(unsigned int row, unsigned int col, int val) {
    board->setValue(row, col, val);
}

int Player::getBoardValue(unsigned int row, unsigned int col) {
    return board->getValue(row, col);
}

//Loops through each ship in the ship vector and calls placeShip with it
void Player::placeShips() {
    cout << "\nPlayer " << ID << ", place your ships: " << endl << endl;

    bool shipIsPlaced;
    vector<Ship>::iterator it;

    //loop through each ship and place it with placeShip()
    for (it = ships.begin(); it != ships.end(); ++it) {
        placeShip(&(*it));
    }
}

/*************************************** 
 * takes user input coordinates and orientation choice then calls...
 **  board->isValidPosition()    to check if coordinates are valid
 **  ship->setShipData()         to set the ships data (coordinates and hits) 
 **  board->markShipPosition()   to mark the board with ships position
 **  displayBoard()              to display the updated board with ship placed on it
 **************************************/
void Player::placeShip(Ship *ship) {
    int boardSize = board->getBoardSize();
    int shipLength = ship->getLength();
    bool shipIsPlaced = false;
    bool isVertical = false;
    unsigned int row = 0, col = 0;

    //until we have a legal placement...
    while(!shipIsPlaced) {
        //tell the user which ship they are placing
        switch(ship->getLength()) {
            case 5:
                cout << "Carrier(5): " << endl;
                break;
            case 4:
                cout << "Battleship(4): " << endl;
                break;
            case 3:
                cout << "Destroyer(3): " << endl;
                break;
            case 2:
                cout << "Patrol(2): " << endl;
                break;
            case 1:
                cout << "Ore(1): " << endl;
                break;
            default:
                cout << "No matching ship of length " << shipLength << endl;
                exit(-1);
                break;
        }
        
        //Take input of orientation and coordinates from user
        //valid means user input is usable and abides by the requirements
        bool valid = false;
        while (!valid) {
            //orientation must be numbers only 0 or 1
            valid = true;
            cout << "\tVertical orientation? (0: no, 1: yes) -> ";
            cin >> isVertical;
            if (!cin.good())  
                valid = false;

            //row must be numbers only 0 - boardsize-1
            if (valid) {
                cout << "\tRow of stern (0 - " << boardSize-1 << "): ";
                cin >> row;
                if (!cin.good() || row > boardSize-1) 
                    valid = false;
            }

            //column must be numbers only 0 - boardsize-1
            if (valid) {
                cout << "\tCol of stern (0 - " << boardSize-1 << "): ";
                cin >> col;
                if (!cin.good() || col > boardSize-1)
                    valid = false;
            } 

            //if input was no good, flush buffer so we can try again
            if (!valid) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tInvalid input, re-enter\n\n";
            }
        }

        // Check if position is valid
        if (board->isValidPosition(shipLength, isVertical, row, col)) {
            //set the ShipData
            ship->setShipData(isVertical, row, col);

            //place ship on the board
            board->markShipPosition(ship);

            displayBoard();
            shipIsPlaced = true;
        }
        else {
            cout << "Position is invalid. Try again\n\n";
            displayBoard();
        }
    }
}

//Gets attack coordinates from player and returns them via Coords struct*
Coords* Player::attack() {
    int boardSize = board->getBoardSize();
    unsigned int row=0, col=0; 
    bool valid = false;

    //Take input of attack coordinates from user
    while (!valid) {
        valid = true;

        //row must be numbers only 0 - boardsize-1
        cout << "\tRow: ";
        cin >> row;
        if (!cin.good() || row > boardSize-1) 
            valid = false;

        //column must be numbers only 0 - boardsize-1
        if (valid) {
            cout << "\tCol: ";
            cin >> col;
            if (!cin.good() || col > boardSize-1)
                valid = false;
        } 

        //if input was no good, flush buffer so we can try again
        if (!valid) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\tInvalid coordinates, re-enter\n\n";
        }
    }
    return new Coords(row, col);
}

//returns true on hit
bool Player::isAHit(Coords* coords) {
    bool hit;
    if (board->isAHit(coords)) {
        hit = true;
        //find ship that was hit and mark it
        markShip(coords);
        return true;
    }
    else {
        hit = false;
    }
    return false;
}

//Searches through ships to find cell at coords and mark as hit
void Player::markShip(Coords* coords) {
   std::vector<Ship>::iterator ships_it;
   std::vector<ShipData>::iterator data_it;
   for (ships_it = ships.begin(); ships_it != ships.end(); ships_it++) {
       //Find the ship that the coords match
       if (ships_it->markAsHit(coords->row, coords->col)) {
           return;
       }
   }

}
