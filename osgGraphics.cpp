#include "osgGraphics.h"


float BoardPanel::_cubeSize = 1.0;

BoardPanel::BoardPanel( int size ) : Board(size), _cursor(size/2, size/2)
{
	ShapeDrawable *myShapeDrawable;
	osg::Box *myBox;

	_root = new osg::Group();

	_geode = new osg::Geode();
	_panelTransform = new osg::PositionAttitudeTransform();
	_panelTransform->setPosition(osg::Vec3( 0, 0, 0));
	_root->addChild( _panelTransform );
	_panelTransform->addChild( _geode );
	
	osg::StateSet* stateset = new osg::StateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	_geode->setStateSet(stateset);

	float mid = ((float) size)/ 2.0 * _cubeSize;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			myBox = new osg::Box(osg::Vec3(-mid+j*_cubeSize, 0.0f, -mid+i*_cubeSize), _cubeSize*0.8);
			myShapeDrawable = new ShapeDrawable(myBox);
			myShapeDrawable->setColor( osg::Vec4(0.3f, 0.3f, 1.0f, 1.0f) );
			_geode->addDrawable(myShapeDrawable);
			_allies.push_back(myShapeDrawable);
		}
	}
	
	setColor(_cursor, SELECTING);
}

BoardPanel::~BoardPanel()
{
}

void BoardPanel::setColor( Coords aimCoord, int val)
{
	int row, col;
	row = aimCoord.row;
	col = aimCoord.col;

	int pos = row * getBoardSize() + col;
	

	switch (val)
	{
	case ATTACK_HIT:
		_allies[pos]-> setColor ( osg::Vec4(1.0f, 0.3f, 0.3f, 1.0f) );
		break;
	case ATTACK_MISS:
		_allies[pos]-> setColor ( osg::Vec4(0.3f, 1.0f, 0.3f, 1.0f) );
		break;
	case ATTACK_UNKNOW:
		_allies[pos]-> setColor ( osg::Vec4(0.3f, 0.3f, 1.0f, 1.0f) );
		break;
	case SELECTING:
		_allies[pos]-> setColor ( osg::Vec4(1.0f, 1.0f, 1.0f, 0.8f) );
		break;
	case SHIP_POSITION:
		_allies[pos]-> setColor ( osg::Vec4(0.1f, 0.3f, 1.0f, 1.0f) );
		break;
	case SHIP_POSITION_UNCONFIRMED:
		_allies[pos]-> setColor ( osg::Vec4(0.1f, 0.3f, 1.0f, 0.5f) );
		break;
	case SHIP_INVALID:
		_allies[pos]-> setColor ( osg::Vec4(1.0f, 0.3f, 0.1f, 0.5f) );
		break;
	case SHIP_UNOCCUPIED:
		_allies[pos]-> setColor ( osg::Vec4(0.1f, 0.1f, 0.1f, 0.1f) );
		break;
	case SHIP_HIT:
		_allies[pos]-> setColor ( osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) );
		break;
	default:
		break;
	}
}

bool BoardPanel::isAHit( int row, int col )
{
	bool hit = Board::isAHit(row, col);
	if ( hit )
	{
		setColor ( Coords(row, col), ATTACK_HIT );
		return true;
	}
	setColor ( Coords(row, col), ATTACK_MISS );
	return false;
}

bool BoardPanel::isAHit( Coords* coords )
{
	return isAHit(coords->row, coords->col);
}

osg::Group* BoardPanel::getRoot()
{
	return _root;
}

void BoardPanel::moveCursor(int direction)
{
	int max = getBoardSize()-1;
	bool valid = false;
	Coords oldCursor(_cursor.row, _cursor.col);
	switch(direction)
	{
	case MOVE_UP:
		if (_cursor.row < max )
		{
			valid = true;
			_cursor.row += 1;
		}
		break;
	case MOVE_DOWN:
		if (_cursor.row > 0)
		{
			valid = true;
			_cursor.row -= 1;
		}
		break;
	case MOVE_LEFT:
		if (_cursor.col > 0)
		{
			valid = true;
			_cursor.col -= 1;
		}
		break;
	case MOVE_RIGHT:
		if (_cursor.col < max)
		{
			valid = true;
			_cursor.col += 1;
		}
		break;
	}
	if (valid)
	{
		char mark = getValue(oldCursor.row, oldCursor.col);
		switch (mark)
		{
		case 'X':
			setColor ( oldCursor, ATTACK_HIT );
			break;
		case 'O':
			setColor ( oldCursor, ATTACK_MISS );
			break;
		default:
			if(!_visible)
			{
				setColor ( oldCursor, ATTACK_UNKNOW );
			}
			else if (mark = '-')
			{
				setColor ( oldCursor, SHIP_UNOCCUPIED );
			}
			else
			{
				setColor ( oldCursor, SHIP_POSITION );
			}
		}

		setColor(_cursor, SELECTING);
	}
}

void BoardPanel::showShipPosition(int length, bool isVertical, int row, int col)
{
	int size = getBoardSize();

	if (_row < 0 || _col < 0 || _row >= size || _col >= size )
	{
		std::cout << "out of range" << std::endl;
	}
	else
	{
		setShipPositionColor(false);
		_length = length;
		_isVertical = isVertical;
		_row = row;
		_col = col;
		setShipPositionColor(true);
	}
}

bool BoardPanel::placeShipAtCurrentPosition(Ship ship)
{
	int length, row, col;
	bool isVertical;
	length = ship.getLength();
	row = ship.getSternRow();
	col = ship.getSternCol();
	isVertical = ship.isVertical();
	showShipPosition(length, isVertical, row, col);
	
	if (isValidPosition(_length, _isVertical, _row, _col))
	{
		markShipPosition(&ship);
		setShipPositionColor(false);
		return true;
	}
	else
	{
		std::cout << "invalid position to place a ship" << std::endl;
		return false;
	}
}

void BoardPanel::setShipPositionColor(bool setFlag)
{
	int color;
	if (setFlag)
	{
		if (isValidPosition(_length, _isVertical, _row, _col ))
		{
			color = SHIP_POSITION_UNCONFIRMED;
		}
		else
		{
			color = SHIP_INVALID;
		}
	}
	else
	{
		color = SHIP_UNOCCUPIED;
	}
	
	//if the ship is vertically oriented...
	if (_isVertical) {
        for (int r = _row; r < (_row+_length); ++r) 
		{
			// if it's occupied. leave it unchanged
			if (getValue(r, _col) == '-')
			{
				setColor(Coords(r, _col), color);
			}
			else
			{
				setColor(Coords(r, _col), SHIP_POSITION);
			}
        }
    }
    //if the ship is horizontally oriented...
    else {
        for (int c = _col; c < (_col+_length); ++c) 
		{
            // if it's occupied. leave it unchanged
			if (getValue(_row, c) == '-')
			{
				setColor(Coords(_row, c), color);
			}
			else
			{
				setColor(Coords(_row, c), SHIP_POSITION);
			}
        }
    }

}