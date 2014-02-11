#include "player.h"
#include "board.h"
#include "ship.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    int boardSize = 10;     
    Player player1(1, boardSize);
    Player player2(2, boardSize);
    player1.displayBoard();
    player2.displayBoard();
    player1.placeShips();
    player2.placeShips();
    while (1) {
        //1 attacks 2
        if (player2.isAHit(player1.attack())) {
            cout << "PLAYER " << player1.getID() << " HIT" << endl;;

        }
        else {
            cout << "PLAYER " << player1.getID() << " MISS" << endl;;
        }
        player1.displayBoard();
        player2.displayBoard();

        //2 attacks 1
        if (player1.isAHit(player2.attack())) {
            cout << "PLAYER " << player2.getID() << " HIT" << endl;;

        }
        else {
            cout << "PLAYER " << player2.getID() << " MISS" << endl;;
        }
        player1.displayBoard();
        player2.displayBoard();
    }   
}
