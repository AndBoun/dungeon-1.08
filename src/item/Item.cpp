//
// Created By Andrew Boun on 4/2/2025
//

#include <item/Item.hpp>

Item::Item()
    : name(""), desc(""), type(""), color(""),
      dice_hit(0, 0, 0), dice_dam(0, 0, 0), dice_dodge(0, 0, 0), dice_def(0, 0, 0),
      dice_weight(0, 0, 0), dice_speed(0, 0, 0), dice_attr(0, 0, 0), dice_val(0, 0, 0),
      art(""), rrty(0) {}

Item::Item(std::string name, std::string desc, std::string type, std::string color,
           Dice dice_hit, Dice dice_dam, Dice dice_dodge, Dice dice_def, Dice dice_weight, Dice dice_speed,
           Dice dice_attr, Dice dice_val, std::string art, int rrty) : name(name), desc(desc), type(type), color(color),
                                                                       dice_hit(dice_hit), dice_dam(dice_dam), dice_dodge(dice_dodge), dice_def(dice_def),
                                                                       dice_weight(dice_weight), dice_speed(dice_speed), dice_attr(dice_attr), dice_val(dice_val),
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
       << ITEM_HIT << " " << dice_hit << "\n"
       << ITEM_DAM << " " << dice_dam << "\n"
       << ITEM_DODGE << " " << dice_dodge << "\n"
       << ITEM_DEF << " " << dice_def << "\n"
       << ITEM_WEIGHT << " " << dice_weight << "\n"
       << ITEM_SPEED << " " << dice_speed << "\n"
       << ITEM_ATTR << " " << dice_attr << "\n"
       << ITEM_VAL << " " << dice_val << "\n"
       << ITEM_ART << " " << art << "\n"
       << ITEM_RRTY << " " << rrty << "\n"
       << ITEM_END << "\n";
    return os;
}