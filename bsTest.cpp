#include "player.h"
#include "board.h"
#include "ship.h"
#include <iostream>
//#include <chrono>
//#include <thread>
using namespace std;

int main(int argc, char **argv) {
    int boardSize = 10;     
    Player player1(1, boardSize);
    Player player2(2, boardSize);

    //display boards and place ships
    player1.displayBoard();
    player2.displayBoard();
    player1.placeShips();
    player2.placeShips();
    
    //chrono::milliseconds dura(1000);

    //take turns attacking
    bool whosTurn = true;
    while (1) {
        cout << "\n________________________________\n";
        player1.displayBoard();
        cout << endl;
        player2.displayBoard();
        if (whosTurn) {
            whosTurn = false;

            //player1 attacks
            cout << "\nPLAYER " << player1.getID() << " ATTACK: " << endl;
            if (player2.isAHit(player1.attack())) {
                cout << "\n**************\n";
                cout << "PLAYER " << player1.getID() << " HITS" << endl;
                cout << "**************\n";
            }
            else { 
                cout << "\n****************\n";
                cout << "PLAYER " << player1.getID() << " MISSES" << endl;
                cout << "****************\n";
            }
        }
        else {
            whosTurn = true;

            //player2 attacks
            cout << "\nPLAYER " << player2.getID() << " ATTACK: " << endl;
            if (player1.isAHit(player2.attack())) {
                cout << "\n**************\n";
                cout << "PLAYER " << player2.getID() << " HITS" << endl;
                cout << "**************\n";
            }
            else {
                cout << "\n****************\n";
                cout << "PLAYER " << player2.getID() << " MISSES" << endl;
                cout << "****************\n";
            }
        }
     //   this_thread::sleep_for(dura);

    }   
}
