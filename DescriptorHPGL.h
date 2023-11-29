#pragma once

#include <vector>
#include <string>
#include <map>
#include <Windows.h>
#include "Shape.h"

class DescriptorHPGL {
private:
	std::map<std::string, int> commandStringCodes;
	void makeFigure(const std::vector<Point*>& points, std::vector<Shape*>& shapes);
	void makePoints(std::string commandString, std::vector<Point*>& points);
public:
	DescriptorHPGL();
	~DescriptorHPGL();

	void decrypt(const std::string& fileName, std::vector<Shape*>& shapes);
};
