//
// Created By Andrew Boun on 4/1/2025
//

#ifndef ROOM_HPP
#define ROOM_HPP

#include <utils/Point.hpp>

class Room
{
protected:
    int width;
    int height;
    Point topLeft;
    Point center;

public:
    Room();
    Room(int x, int y, int width, int height);
    ~Room();

    int getWidth() const;
    int getHeight() const;
    const Point& getTopLeft() const;
    const Point& getCenter() const;

    void setWidth(int width);
    void setHeight(int height);
    void setTopLeft(int x, int y);
};

#endif