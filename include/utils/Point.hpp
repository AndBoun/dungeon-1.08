//
// Created By Andrew Boun on 4/1/2025
//

#ifndef POINT_HPP
#define POINT_HPP

class Point
{

    protected:
        int x;
        int y;

    public:
        Point();
        Point(int x, int y);
        ~Point();

        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
        void setPoint(int x, int y);
};

#endif