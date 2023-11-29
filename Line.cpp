#include "Line.h"
#include <assert.h>
#include <cassert>
#include <vector>

Line::Line(const Point& start, const Point& end) : start(new Point(start)), end(new Point(end)) {
}

Line::Line(const std::vector<Point*>& points)
{
	this->start = points[0]->copy();
	this->end = points[1]->copy();
}

Line::Line(const Line& other) {
	start = other.start->copy();
	end = other.end->copy();
}

Line* Line::copy() {
	return new Line(*this);
}

Line::~Line() {
	delete start;
	delete end;
}

Line& Line::operator=(const Line& other)
{
	if (this != &other) {
		delete start;
		delete end;
		start = other.start->copy();
		end = other.end->copy();
	}
	return *this;
}

void Line::draw(HDC hdc)
{
	MoveToEx(hdc, start->getX(), start->getY(), NULL);
	if (*start == *end) {
		Rectangle(hdc, start->getX(), start->getY(), end->getX() + 2, end->getY() + 2);
	}
	else {
		LineTo(hdc, end->getX(), end->getY());
	}
}

Point& Line::first()
{
	return *this->start->copy();
}

Point& Line::second()
{
	return *this->end->copy();
}


