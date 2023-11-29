#pragma once
#include <Windows.h>
#include <vector>
#include "Shape.h"
#include "DescriptorHPGL.h"


class Painter {
private:
	double ratioX;
	double ratioY;
	std::vector<Shape*> shapes;
public:
	Painter();
	void recieveShapes(DescriptorHPGL& descriptor, const std::string& fileName);
	Painter(DescriptorHPGL& descriptor, const std::string& fileName);
	~Painter();
	Painter(const Painter& other);
	virtual Painter* copy();
	Painter& operator=(const Painter& other);
	void draw(HDC hdc);
	double getRatioX();
	double getRatioY();
	void setRatioX(const double& newRatio);
	void setRatioY(const double& newRatio);
	void changeRatio(const double& mouseWheelMove);
};
