#ifndef	__HUMAN_PLAYER
#define __HUMAN_PLAYER

#include "osgGraphics.h"

#include "player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(int id, int boardSize) : Player(id, boardSize) { _boardPanel = new BoardPanel(boardSize); };
	
	// This direction use BoardPanel::MOVE_UP/DOWN/LEFT/RIGHT
	void move(int direction);

	/****************************
	 *
	 *	void placeShips();
	 *
	 *	void placeShip(Ship *ship);
	 *
	 ****************************/
	bool isAHit(Coords* coords);

	osg::Group* getOSGRoot();

	void placeShip(Ship *ship);

	void displayShip(Ship ship);
	int getBoardSize();
	
protected:
	BoardPanel* _boardPanel;
};


#endif