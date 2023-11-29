#include "Painter.h"
#include "DescriptorHPGL.h"

Painter::Painter() : ratioX(1.0), ratioY(1.0)
{
}

void Painter::recieveShapes(DescriptorHPGL& descriptor, const std::string& fileName)
{
	descriptor.decrypt(fileName, shapes);
}

Painter::Painter(DescriptorHPGL& descriptor, const std::string& fileName) : ratioX(1.0), ratioY(1.0) {
	recieveShapes(descriptor, fileName);
}

Painter::~Painter()
{
	for (int i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}
}

Painter::Painter(const Painter& other)
{
	ratioX = other.ratioX;
	ratioY = other.ratioY;
	for (int i = 0; i < other.shapes.size(); i++) {
		shapes.push_back(other.shapes[i]->copy());
	}
}

Painter* Painter::copy()
{
	return new Painter(*this);
}

Painter& Painter::operator=(const Painter& other)
{
	if (this != &other) {
		for (int i = 0; i < shapes.size(); i++) {
			delete shapes[i];
		}
		shapes.clear();
		ratioX = other.ratioX;
		ratioY = other.ratioY;
		for (int i = 0; i < other.shapes.size(); i++) {
			shapes.push_back(other.shapes[i]->copy());
		}
	}
	return *this;
}

void Painter::draw(HDC hdc)
{
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw(hdc);
	}
}

double Painter::getRatioX()
{
	return ratioX;
}

double Painter::getRatioY()
{
	return ratioY;
}

void Painter::setRatioX(const double& newRatio)
{
	ratioX = newRatio;
}

void Painter::setRatioY(const double& newRatio)
{
	ratioY = newRatio;
}

void Painter::changeRatio(const double& mouseWheelMove) {
	bool mouseWheelUp = mouseWheelMove > 0;
	switch (mouseWheelUp) {
	case true:
		--ratioX;
		--ratioY;
		break;
	case false:
		++ratioX;
		++ratioY;
		break;
	}

}

