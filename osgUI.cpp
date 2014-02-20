#include "osgUI.h"
#include <iostream>

bool MyKeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea,
	osgGA::GUIActionAdapter& aa)
{
	
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		char key;
		key = ea.getKey();
		this->_handler(key, _gameStateMachine);
	default:
		return false;
	}
	return false;
}

