#pragma once

#include "Point.h"
#include <Windows.h>

class Shape {
public:
	Shape();
	virtual ~Shape() = 0;
	virtual Shape* copy() = 0;
	virtual void draw(HDC hdc) = 0;
};
