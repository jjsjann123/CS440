#ifndef __OSG_UI
#define __OSG_UI
#include <osgGA\GUIEventHandler>
#include "gameStateMachine.h"

class MyKeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
	
	MyKeyboardEventHandler() {};
    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
    virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };

	void setKeyboardCallbackHandler (void (*func)(char, GameStateMachine*), GameStateMachine* stateMachine ) {_handler = func; _gameStateMachine = stateMachine;}; 

protected:

	void (*_handler) (char, GameStateMachine*);
	GameStateMachine* _gameStateMachine;
	
};

#endif