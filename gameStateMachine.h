#ifndef __GAME_STATE_MACHINE
#define __GAME_STATE_MACHINE
#include "humanPlayer.h"
#include <osg/Group>
#include <vector>

class GameStateMachine
{
public:
	enum { INITIALIZE, PLACESHIP, ATTACK, GAMEOVER };

	GameStateMachine();
	~GameStateMachine();
	void setRoot(osg::Group* root) { _root = root; };
	
	static void keyboardInput(char key, GameStateMachine* obj);

	void setHumanPlayer( HumanPlayer *playerOne ) { _player = playerOne; };
	
	
protected:

	int _index;

	int _size;

	void initialize(char key);
	void placeship(char key);
	void attack(char key);
	void gameover(char key);

	osg::Group* _root;

	int _state;
	HumanPlayer* _player;

	std::vector<Ship> _shipList;
};
#endif