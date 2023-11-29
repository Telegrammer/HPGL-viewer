#include "PolyLine.h"
#include <cassert>
#include <vector>

PolyLine::PolyLine()
{
}

PolyLine::PolyLine(const std::vector<Point*>& points) {
	for (int i = 0; i < points.size(); i++) {
		this->points.push_back(points[i]->copy());
	}
}

PolyLine::PolyLine(const PolyLine& other) {
	for (int i = 0; i < other.points.size(); i++) {
		points.push_back(other.points[i]->copy());
	}
}


PolyLine* PolyLine::copy()
{
	return new PolyLine(*this);
}

PolyLine::~PolyLine() {
	for (int i = 0; i < points.size(); i++) {
		delete points[i];
	}
	points.clear();
}

PolyLine& PolyLine::operator=(const PolyLine& other)
{
	return *this;
}

void PolyLine::draw(HDC hdc)
{
	MoveToEx(hdc, points[0]->getX(), points[0]->getY(), NULL);
	for (int i = 1; i < points.size(); i++) {
		LineTo(hdc, points[i]->getX(), points[i]->getY());
	}
}
