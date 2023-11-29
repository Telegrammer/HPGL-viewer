#include "Point.h"
#include <string>

Point::Point() : x(new int(0)), y(new int(0)) {
}

Point::Point(const int& x, const int& y) : x(new int(x)), y(new int(y)) {
}


Point::Point(const Point& other) : x(new int(*other.x)), y(new int(*other.y)) {
}

Point::~Point() {
	delete x;
	delete y;
}

Point* Point::copy() {
	return new Point(*this);
}

Point& Point::operator=(const Point& other) {
	if (this != &other) {
		x = new int(*other.x);
		y = new int(*other.y);
	}
	return *this;
}

int Point::getX() {
	return *x;
}

void Point::setX(const int& x) {
	*this->x = x;
}

int Point::getY()
{
	return *y;
}

void Point::setY(const int& y) {
	*this->y = y;
}

void Point::operator+=(const Point& offset)
{
	*x += *offset.x;
	*y += *offset.y;
}

void Point::operator-=(const Point& offset)
{
	*x -= *offset.x;
	*y -= *offset.y;
}

bool Point::operator==(const Point& other)
{
	return *x == *other.x && *y == *other.y;
}
