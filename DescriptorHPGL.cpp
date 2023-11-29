#include "DescriptorHPGL.h"
#include "Line.h"
#include "PolyLine.h"
#include <fstream>
#include <string>

void DescriptorHPGL::makeFigure(const std::vector<Point*>& points, std::vector<Shape*>& shapes) {
    switch (points.size()) {
    case 0:
        break;
    case 1:
        shapes.push_back(new Line(*points[0], *points[0]));
        break;
    case 2:
        shapes.push_back(new Line(points));
        break;
    default:
        shapes.push_back(new PolyLine(points));
        break;
    }
}
void DescriptorHPGL::makePoints(std::string coords, std::vector<Point*>& points)
{
    int coordX, coordY;
    bool isCoordX = true;
    size_t commaIndex = coords.find(',');
    while (commaIndex != coords.npos) {
        switch (isCoordX)
        {
        case true:
            coordX = std::stoi(coords.substr(0, commaIndex));
            break;
        case false:
            coordY = std::stoi(coords.substr(0, commaIndex));
            points.push_back(new Point(coordX, coordY));
            break;
        }
        isCoordX = !isCoordX;
        coords = coords.substr(commaIndex + 1, coords.size() - commaIndex - 1);
        commaIndex = coords.find(',');
    }
    if (coords.size() != 0) {
        coordY = std::stoi(coords.substr(0, commaIndex));
        points.push_back(new Point(coordX, coordY));
    }
}
DescriptorHPGL::DescriptorHPGL()
{
    commandStringCodes = {{"PD", 0}, {"PA", 1}, {"PU", 2} };
}

DescriptorHPGL::~DescriptorHPGL()
{
    commandStringCodes.clear();
}

void DescriptorHPGL::decrypt(const std::string& fileName, std::vector<Shape*>& shapes)
{

    std::ifstream file;
    file.open(fileName);
    std::string line;
    std::vector<Point*> points;

    while (getline(file, line, ';')) {
        if (line.size() < 2) { continue; }
        if (std::isdigit(line[0])) {
            makePoints(line, points);
            continue;
        }

        std::string code = line.substr(0, 2);
        std::string coords = line.substr(2, line.size() - 2);

        std::map<std::string, int>::const_iterator it = DescriptorHPGL::commandStringCodes.find(code);
        if (it == DescriptorHPGL::commandStringCodes.end()) {
            continue;
        }
        switch (it->second) {
        case 0:
            if (points.size() > 0) {
                Point* last = new Point(*points.back());
                for (int i = 0; i < points.size(); i++) {
                    delete points[i];
                }
                points = { last };

                makePoints(coords, points);
            }
            break;
        case 1:
            makePoints(coords, points);
            break;
        case 2:
            makeFigure(points, shapes);
            for (int i = 0; i < points.size(); i++) {
                delete points[i];
            }
            points.clear();
            makePoints(coords, points);
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < points.size(); i++) {
        delete points[i];
    }
    points.clear();
    file.close();
}
