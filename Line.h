#pragma once

#include "Shape.h"
#include <vector>

class Line : public Shape {
private:
	Point* start;
	Point* end;
public:
	Line(const Point& start, const Point& end);
	Line(const std::vector<Point*>& points);
	Line(const Line& other);
	virtual Line* copy();
	virtual ~Line();
	Line& operator=(const Line& other);
	virtual void draw(HDC hdc);
	Point& first();
	Point& second();
};