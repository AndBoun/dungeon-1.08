//
// Created By Andrew Boun on 4/1/2025
//

#ifndef STAIR_HPP
#define STAIR_HPP

#include <dungeon/base/Cell.hpp>
#include <utils/Point.hpp>

class Stair : public Cell
{
protected:
    Point location; // Location of the stair

public:
    Stair();
    Stair(int x, int y, char type);
    ~Stair();

    int getX() const;
    int getY() const;
    char getType() const;

    void setX(int x);
    void setY(int y);
};

#endif