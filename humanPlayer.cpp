#include "humanPlayer.h"

void HumanPlayer::move(int direction)
{
	_boardPanel->moveCursor(direction);
}

bool HumanPlayer::isAHit(Coords* coords)
{
	bool ret = _boardPanel->isAHit(coords);
	Player::isAHit(coords);
	return ret;
}

osg::Group* HumanPlayer::getOSGRoot()
{
	return _boardPanel->getRoot();
}

bool HumanPlayer::placeShip (Ship *ship)
{
	ships.push_back(*ship);
	return _boardPanel->placeShipAtCurrentPosition(*ship);
}

void HumanPlayer::displayShip (Ship ship)
{
	int length = ship.getLength();
	bool isVertical = ship.isVertical();
	int row = ship.getSternRow();
	int col = ship.getSternCol();

	_boardPanel->showShipPosition(length, isVertical, row, col);
}

int HumanPlayer::getBoardSize()
{
	return _boardPanel->getBoardSize();
}