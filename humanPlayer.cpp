#include "humanPlayer.h"

void HumanPlayer::move(int direction)
{
	_boardPanel->moveCursor(direction);
}

bool HumanPlayer::isAHit(Coords* coords)
{
	bool ret = _boardPanel->isAHit(coords);
	//Player::isAHit(coords);
	return ret;
}

osg::Group* HumanPlayer::getOSGRoot()
{
	return _boardPanel->getRoot();
}

void HumanPlayer::showShip(Ship &ship)
{
	_boardPanel->showShipPosition(ship.getLength(), ship.isVertical(), ship.getSternRow(), ship.getSternCol());
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

int HumanPlayer::getCursorCol()
{
	return _boardPanel->getCursorCol();
}

int HumanPlayer::getCursorRow()
{
	return _boardPanel->getCursorRow();
}

char HumanPlayer::getBoardValue(int row, int col)
{
	int boardSize = _boardPanel->getBoardSize();
    if (row < 0 || col < 0 || row > boardSize || col > boardSize) { 
		return '*';
	}
	return _boardPanel->getValue(row, col);
}