#pragma once



class Point {
private:
	int* x;
	int* y;
public:
	Point();
	Point(const int& x, const int& y);
	Point(const Point& other);
	virtual ~Point();
	virtual Point* copy();
	Point& operator=(const Point& other);
	int getX();
	void setX(const int& x);
	int getY();
	void setY(const int& y);
	void operator+=(const Point& offset);
	void operator-=(const Point& offset);
	bool operator==(const Point& other);
};