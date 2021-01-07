#pragma once
class Point
{
public:
	Point( float x, float y );
	Point( const Point & p );
	virtual ~Point();

	Point& operator=( const Point& p );

	float x() const;
	float y() const;
	void setX( float x );
	void setY( float y );

private:
	float mX;
	float mY;
};

