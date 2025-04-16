//
// Created By Andrew Boun on 4/15/2025
//

#ifndef ITEMDESCRIPTION_HPP
#define ITEMDESCRIPTION_HPP

#include <string>
#include <vector>
#include <set>
#include <utils/Dice.hpp>
#include <optional>
#include <item/Item.hpp>

static const std::string ITEM_HEADER = "RLG327 OBJECT DESCRIPTION 1";
static const std::string ITEM_BEGIN_OBJECT = "BEGIN OBJECT";
static const std::string ITEM_NAME = "NAME";
static const std::string ITEM_DESC = "DESC";
static const std::string ITEM_TYPE = "TYPE";
static const std::string ITEM_COLOR = "COLOR";
static const std::string ITEM_HIT = "HIT";
static const std::string ITEM_DAM = "DAM";
static const std::string ITEM_DODGE = "DODGE";
static const std::string ITEM_DEF = "DEF";
static const std::string ITEM_WEIGHT = "WEIGHT";
static const std::string ITEM_SPEED = "SPEED";
static const std::string ITEM_ATTR = "ATTR";
static const std::string ITEM_VAL = "VAL";
static const std::string ITEM_ART = "ART";
static const std::string ITEM_RRTY = "RRTY";
static const std::string ITEM_END = "END";

static const std::set<std::string> validTypes = {
    "WEAPON", "OFFHAND", "RANGED", "ARMOR", "HELMET", "CLOAK", "GLOVES",
    "BOOTS", "RING", "AMULET", "LIGHT", "SCROLL", "BOOK", "FLASK", "GOLD",
    "AMMUNITION", "FOOD", "WAND",  "CONTAINER"
};


class ItemDescription
{
public:
std::string name;
    std::string desc;
    std::string type;
    std::string color;
    Dice dice_hit;
    Dice dice_dam;
    Dice dice_dodge;
    Dice dice_def;
    Dice dice_weight;
    Dice dice_speed;
    Dice dice_attr;
    Dice dice_val;
    std::string art;
    int rrty;

    bool canBeGenerated = true;

    ItemDescription() : 
        name(""),
        desc(""),
        type(""),
        color(""),
        dice_hit(),
        dice_dam(),
        dice_dodge(),
        dice_def(),
        dice_weight(),
        dice_speed(),
        dice_attr(),
        dice_val(),
        art(""),
        rrty(0)
    {}



    ItemDescription(std::string name, std::string desc, std::string type, std::string color,
         Dice hit, Dice dice_dam, Dice dodge, Dice def, Dice weight, Dice speed,
         Dice attr, Dice val, std::string art, int rrty) :
        name(name),
        desc(desc),
        type(type),
        color(color),
        dice_hit(hit),
        dice_dam(dice_dam),
        dice_dodge(dodge),
        dice_def(def),
        dice_weight(weight),
        dice_speed(speed),
        dice_attr(attr),
        dice_val(val),
        art(art),
        rrty(rrty)
    {}

    ~ItemDescription() {};

    static Item *createItem(ItemDescription &itemDesc, int ID, int descID);

    static std::vector<ItemDescription> itemParser();
    std::ostream &print(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const ItemDescription &item) { return item.print(os); }

private:
    static std::optional<ItemDescription> parseItem(std::ifstream &file);
};

#endif