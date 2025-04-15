//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/base/Cell.hpp>
#include <iostream>

// Constructor
Cell::Cell() : hardness(0), type(' ') {}
Cell::Cell(int hardness, char type) : hardness(hardness), type(type) {}

// Destructor
Cell::~Cell() {}

// Getters and Setters
int Cell::getHardness() const { return hardness; }
char Cell::getType() const { return type; }
void Cell::setHardness(int hardness) { this->hardness = hardness; }
void Cell::setType(char type) { this->type = type; }
void Cell::setCell(int hardness, char type)
{
    this->hardness = hardness;
    this->type = type;
}
