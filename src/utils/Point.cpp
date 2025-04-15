//
// Created By Andrew Boun on 4/1/2025
//

#include <utils/Point.hpp>

Point::Point() : x(0), y(0) {}
Point::Point(int x, int y) : x(x), y(y) {}
Point::~Point() {}
int Point::getX() const { return x; }
int Point::getY() const { return y; }
void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }
void Point::setPoint(int x, int y) { this->x = x; this->y = y; }