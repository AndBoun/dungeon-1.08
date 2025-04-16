//
// Created By Andrew Boun on 4/2/2025
//

#include <item/Item.hpp>

Item::Item()
    : name(""), desc(""), type(""), color(""),
      hit(0), dice_dam(0, 0, 0), dodge(0), def(0),
      weight(0), speed(0), attr(0), val(0),
      art(""), rrty(0) {}

Item::Item(std::string name, std::string desc, std::string type, std::string color,
           int hit, Dice dice_dam, int dodge, int def, int weight, int speed,
           int attr, int val, std::string art, int rrty)
    : name(name), desc(desc), type(type), color(color),
      hit(hit), dice_dam(dice_dam), dodge(dodge), def(def),
      weight(weight), speed(speed), attr(attr), val(val),
      art(art), rrty(rrty) {}

Item::~Item() {}

