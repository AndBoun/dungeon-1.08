//
// Created By Andrew Boun on 4/2/2025
//

#ifndef PC_HPP
#define PC_HPP
#include <character/Character.hpp>
#include <utils/Point.hpp>
#include <dungeon/base/Cell.hpp>

const int PC_SPEED = 10; // Speed of the player character

class PC : public Character
{
public:
    PC();
    PC(Point position);
    ~PC();
};

#endif