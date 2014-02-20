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
		std::cout << " w key pressed" << std::endl;
		
		break;
	case 'a':
		std::cout << " a key pressed" << std::endl;
		
		break;
	case 's':
		std::cout << " s key pressed" << std::endl;
		
		break;
	case 'd':
		std::cout << " d key pressed" << std::endl;
		
		break;
	default:
		std::cout << key << std::endl;
	} 

}

void GameStateMachine::attack(char key)
{
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
	default:
		std::cout << key << std::endl;
	} 
}

void GameStateMachine::gameover(char key)
{
}