#ifndef __OSG_GRAPHICS
#define __OSG_GRAPHICS
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <vector>
#include "board.h"
using osg::ShapeDrawable;
using std::vector;

class BoardPanel: public Board
{
	typedef vector<ShapeDrawable*> osgShapeArray;
public:
	BoardPanel(int size);
	~BoardPanel();

	enum { ATTACK_HIT, ATTACK_MISS, ATTACK_UNKNOW, SELECTING, 
		SHIP_POSITION, SHIP_POSITION_UNCONFIRMED, SHIP_INVALID, SHIP_UNOCCUPIED, SHIP_HIT };
	enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };
	
	virtual bool isAHit ( int row, int col );
	virtual bool isAHit ( Coords* coords );
	osg::Group* getRoot();

	void moveCursor(int direction);

	// Use this function to move ship around and show it to user
	// it won't add the ship into our board buffer.
	void showShipPosition(int length, bool isVertical, int row, int col);

	// Use this function to place a ship on board
	bool placeShipAtCurrentPosition(Ship ship);
	
	
	bool getVisible() { return _visible; };
	void setVisible(bool visible) { _visible = visible; };

	int getCursorRow();
	int getCursorCol();


protected:
	Coords _cursor;
	// Here val indicates whether it's a HIT or MISS:
	//		Eric used	'X' as a HIT
	//					'O' as a MISS
	// I used a enumerator instead.
	void setColor ( Coords aimCoord, int val );
	void setShipPositionColor(bool setFlag);

	// ship displaying buffer
	int _length;
	bool _isVertical;
	int _row;
	int _col;

private:
	// This would be the size of each cell for our board.
	static float _cubeSize;

	bool _visible;
	
	osg::Group* _root;
	osg::Geode* _geode;
	osg::PositionAttitudeTransform* _panelTransform;
	osgShapeArray _allies;
	osgShapeArray _enemy;
};

#endif