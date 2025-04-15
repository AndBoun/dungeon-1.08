//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/base/Room.hpp>
#include <utils/Point.hpp>
#include <iostream>

// Constructor
Room::Room() : width(0), height(0), topLeft(), center() {}
Room::Room(int x, int y, int width, int height) : width(width), height(height)
{
    topLeft = Point(x, y);
    center = Point(x + width / 2, y + height / 2);
}

// Destructor
Room::~Room(){}

// Getters and Setters
int Room::getWidth() const { return width; }
int Room::getHeight() const { return height; }
const Point& Room::getTopLeft() const { return topLeft; }
const Point& Room::getCenter() const { return center; }

void Room::setWidth(int width) { this->width = width; }
void Room::setHeight(int height) { this->height = height; }
void Room::setTopLeft(int x, int y)
{
    topLeft.setPoint(x, y);
    center.setPoint(x + width / 2, y + height / 2);
}
