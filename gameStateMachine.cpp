#include "gameStateMachine.h"
#include <iostream>

GameStateMachine::GameStateMachine()
{
	_state = INITIALIZE;  
	_player = NULL;
}

GameStateMachine::~GameStateMachine()
{
	if (_player != NULL)
	{
		delete _player;
	}
}


void GameStateMachine::keyboardInput(char key, GameStateMachine* obj)
{
	
	std::cout << "state: " << obj->_state << std::endl;
	switch (obj->_state)
	{
	case INITIALIZE:
		obj->initialize( key );
		break;
	case PLACESHIP:
		obj->placeship( key );
		break;
	case ATTACK:
		obj->attack( key );
		break;
	case GAMEOVER:
		obj->gameover( key );
		break;
	}
}

void GameStateMachine::initialize(char key)
{
	_size = 10;

	_player = new HumanPlayer(1, _size);
	_root->addChild(_player->getOSGRoot());

	_shipList.push_back(Ship(CARRIER, 'c'));
	_shipList.push_back(Ship(DESTROYER, 'd'));

	_index = 0;

	_state = PLACESHIP;
}

void GameStateMachine::placeship(char key)
{
	int length = _shipList[_index].getLength();
	int row = _shipList[_index].getSternRow();
	int col = _shipList[_index].getSternCol();
	bool vertical = _shipList[_index].isVertical();

	int size = _player->getBoardSize();

	switch(key)
	{
	case 'w':
	case 'W':
		std::cout << " w key pressed" << std::endl;
		if ( row < size -1 )
		{
			row += 1;
			_shipList[_index].setShipData(vertical, row, col);
			_player->showShip(_shipList[_index]);
		}
		break;
	case 'a':
	case 'A':
		std::cout << " a key pressed" << std::endl;
		if ( col > 0 )
		{
			col -= 1;
			_shipList[_index].setShipData(vertical, row, col);
			_player->showShip(_shipList[_index]);
		}
		break;
	case 's':
	case 'S':
		std::cout << " s key pressed" << std::endl;
		if ( row > 0 )
		{
			row -= 1;
			_shipList[_index].setShipData(vertical, row, col);
			_player->showShip(_shipList[_index]);
		}
		break;
	case 'd':
	case 'D':
		std::cout << " d key pressed" << std::endl;
		if ( col < size -1 )
		{
			col += 1;
			_shipList[_index].setShipData(vertical, row, col);
			_player->showShip(_shipList[_index]);
		}
		break;
		//rotate
	case 'r':
	case 'R':
		std::cout << " d key pressed" << std::endl;
		vertical = !vertical;
		_shipList[_index].setShipData(vertical, row, col);
		_player->showShip(_shipList[_index]);
		break;
	case 13:
		std::cout << " enter pressed" << std::endl;
		if (_player->placeShip(&_shipList[_index]))
		{
			// Finished deployment
			// Entering Attack mode
			if (_index >= _shipList.size()-1)
			{
				_state = ATTACK;
				_index = 0;
			}
			else
			{
				_index++;
			}
		}
		break;
	default:
		std::cout << key << std::endl;
		std::cout << (int) key << std::endl;
	} 

	std::cout << "row: " << row << ", col: " << col << ", length: " << length << ", vertical?" << vertical << std::endl;

}

void GameStateMachine::attack(char key)
{
	std::cout << "entering attack" << std::endl;
	switch(key)
	{
	case 'w':
		std::cout << " w key pressed" << std::endl;
		_player->move(BoardPanel::MOVE_UP);
		break;
	case 'a':
		std::cout << " a key pressed" << std::endl;
		_player->move(BoardPanel::MOVE_LEFT);
		break;
	case 's':
		std::cout << " s key pressed" << std::endl;
		_player->move(BoardPanel::MOVE_DOWN);
		break;
	case 'd':
		std::cout << " d key pressed" << std::endl;
		_player->move(BoardPanel::MOVE_RIGHT);
		break;
	case 13:
		{
			int row = _player->getCursorRow();
			int col = _player->getCursorCol();
			char val = _player->getBoardValue(row, col);
			if ( val != 'X' && val != 'O' )
			{
				Coords coord(row, col);
				_player->isAHit(&coord);
			}
			break;
		}
	default:
		std::cout << key << std::endl;
	}
}

void GameStateMachine::gameover(char key)
{
}