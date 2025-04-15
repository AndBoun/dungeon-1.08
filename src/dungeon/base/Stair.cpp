//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/base/Stair.hpp>
#include <utils/Point.hpp>

// Constructor
Stair::Stair() : Cell(), location() {}
Stair::Stair(int x, int y, char type) : Cell(0, type) { location = Point(x, y);}

// Destructor
Stair::~Stair() {}

// Getters and Setters
int Stair::getX() const { return location.getX(); }
int Stair::getY() const { return location.getY(); }
char Stair::getType() const { return type; }

void Stair::setX(int x) { location.setX(x); }
void Stair::setY(int y) { location.setY(y); }
