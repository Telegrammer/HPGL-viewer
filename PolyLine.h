#pragma once

#include "Line.h"

class PolyLine : public Shape {
private:
	std::vector<Point*> points;
public:
	PolyLine();
	PolyLine(const std::vector<Point*>& points);
	PolyLine(const PolyLine& other);
	virtual PolyLine* copy();
	virtual ~PolyLine();
	PolyLine& operator=(const PolyLine& other);
	virtual void draw(HDC hdc);
};