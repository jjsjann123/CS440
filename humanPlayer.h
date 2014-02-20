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
	int getCursorCol();
	int getCursorRow();


	char getBoardValue(int row, int col);

	/****************************
	 *
	 *	void placeShips();
	 *
	 *	void placeShip(Ship *ship);
	 *
	 *  is no longer used.
	 *
	 ****************************/

	bool isAHit(Coords* coords);

	osg::Group* getOSGRoot();

	void showShip(Ship &ship);
	bool placeShip(Ship *ship);

	void displayShip(Ship ship);
	int getBoardSize();
	
protected:
	// Moved to parent class Player
	BoardPanel* _boardPanel;
};


#endif