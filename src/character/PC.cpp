//
// Created By Andrew Boun on 4/2/2025
//

#include <character/PC.hpp>

PC::PC() : Character(Point(), PC_SPEED, '@', true, 0) {}
PC::PC(Point position)
    : Character(position, PC_SPEED,'@', true, 0) {}
PC::~PC() {}
