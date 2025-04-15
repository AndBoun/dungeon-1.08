//
// Created By Andrew Boun on 4/2/2025
//

#include <character/PC.hpp>

PC::PC() : Character(Point(), PC_SPEED, Cell(), '@', true, 0) {}
PC::PC(Point position, Cell current_cell)
    : Character(position, PC_SPEED, current_cell, '@', true, 0) {}
PC::~PC() {}
