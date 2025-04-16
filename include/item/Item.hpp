//
// Created By Andrew Boun on 4/2/2025
//

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <utils/Dice.hpp>
#include <vector>
#include <optional>
#include <set>
#include <utils/Point.hpp>

class Item
{
public:
    Point pos;
    // std::string name;
    // std::string desc;
    std::string type;
    int color;
    int hit;
    Dice dice_dam;
    int dodge;
    int def;
    int weight;
    int speed;
    int attr;
    int val;
    bool art;
    int rrty;
    char symbol;

    int ID;
    int descID;

    Item();
    Item(std::string type, int color,
         int hit, Dice dice_dam, int dodge, int def, int weight, int speed,
         int attr, int val, bool art, int rrty);
    ~Item();



};

#endif