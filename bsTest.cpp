#include "player.h"
#include "board.h"
#include "ship.h"

#include <iostream>
//#include <chrono>
//#include <thread>

//#include "osgGraphics.h"
#include "gameStateMachine.h"
#include "humanPlayer.h"
#include "osgUI.h"
#include <osg/Geode>
#include <osgViewer/Viewer>

using namespace std;

int main(int argc, char **argv) {
    int boardSize = 10;

	osgViewer::Viewer viewer;
	osg::Group* root = new osg::Group();

	GameStateMachine myGameStateMachine;
	myGameStateMachine.setRoot( root );
	
	MyKeyboardEventHandler* myHandler = new MyKeyboardEventHandler();
	myHandler->setKeyboardCallbackHandler(&GameStateMachine::keyboardInput, &myGameStateMachine);
	/*
	root->addChild( player1.getOSGRoot() );
	HumanPlayer player1(1, 10);
	*/
	osg::Geode* testGeode = new osg::Geode();
	testGeode->addDrawable( new osg::ShapeDrawable( new osg::Sphere( osg::Vec3(0, 0, 0), 3)));
	root->addChild(testGeode);
	
	
	viewer.setSceneData( root );
	viewer.addEventHandler(myHandler);
	viewer.setUpViewInWindow(0, 0, 640, 480);
	viewer.realize();


/*	player1.isAHit(loc1);
	loc1->col = 3;
	player1.isAHit(loc1);
	loc1->col = 4;
	player1.isAHit(loc1);*/
	
	viewer.run();
	
	return 0;

	/*
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

	*/
}
