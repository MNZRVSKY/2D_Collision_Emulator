#include "Point.h"

Point::Point( float x, float y )
	:mX( x ), mY( y )
{
}

Point::Point( const Point& p )
	:mX( p.x() ), mY( p.y() )
{
}

Point::~Point()
{
}

Point& Point::operator=( const Point& p )
{
	mX = p.x();
	mY = p.y();
	
	return *this;
}

float Point::x() const
{
	return mX;
}

float Point::y() const
{
	return mY;
}

void Point::setX( float x )
{
	mX = x;
}

void Point::setY( float y )
{
	mY = y;
}
