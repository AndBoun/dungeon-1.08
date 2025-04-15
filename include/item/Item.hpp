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

class Item
{
public:
    std::string name;
    std::string desc;
    std::string type;
    std::string color;
    Dice hit;
    Dice dam;
    Dice dodge;
    Dice def;
    Dice weight;
    Dice speed;
    Dice attr;
    Dice val;
    std::string art;
    int rrty;

    Item();
    Item(std::string name, std::string desc, std::string type, std::string color,
         Dice hit, Dice dam, Dice dodge, Dice def, Dice weight, Dice speed,
         Dice attr, Dice val, std::string art, int rrty);
    ~Item();

    static std::vector<Item> itemParser();
    std::ostream &print(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Item &item) { return item.print(os); }

private:
    static std::optional<Item> parseItem(std::ifstream &file);

};

#endif