//
// Created By Andrew Boun on 4/2/2025
//

#include <item/Item.hpp>

Item::Item()
    : name(""), desc(""), type(""), color(""),
      hit(0, 0, 0), dam(0, 0, 0), dodge(0, 0, 0), def(0, 0, 0),
      weight(0, 0, 0), speed(0, 0, 0), attr(0, 0, 0), val(0, 0, 0),
      art(""), rrty(0) {}

Item::Item(std::string name, std::string desc, std::string type, std::string color,
           Dice hit, Dice dam, Dice dodge, Dice def, Dice weight, Dice speed,
           Dice attr, Dice val, std::string art, int rrty) : name(name), desc(desc), type(type), color(color),
                                                             hit(hit), dam(dam), dodge(dodge), def(def),
                                                             weight(weight), speed(speed), attr(attr), val(val),
                                                             art(art), rrty(rrty) {}

Item::~Item() {}

std::ostream &Item::print(std::ostream &os) const
{
    os << ITEM_BEGIN_OBJECT << "\n"
       << ITEM_NAME << " " << name << "\n"
       << ITEM_DESC << "\n"
       << desc
       << "." << "\n"
       << ITEM_TYPE << " " << type << "\n"
       << ITEM_COLOR << " " << color << "\n"
       << ITEM_HIT << " " << hit << "\n"
       << ITEM_DAM << " " << dam << "\n"
       << ITEM_DODGE << " " << dodge << "\n"
       << ITEM_DEF << " " << def << "\n"
       << ITEM_WEIGHT << " " << weight << "\n"
       << ITEM_SPEED << " " << speed << "\n"
       << ITEM_ATTR << " " << attr << "\n"
       << ITEM_VAL << " " << val << "\n"
       << ITEM_ART << " " << art << "\n"
       << ITEM_RRTY << " " << rrty << "\n"
       << ITEM_END << "\n";
    return os;
}