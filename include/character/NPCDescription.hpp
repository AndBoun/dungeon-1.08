//
// Created By Andrew Boun on 4/15/2025
//

#ifndef NPCDescription_HPP
#define NPCDescription_HPP

#include <character/Character.hpp>
#include <character/NPC.hpp>
#include <string>
#include <vector>
#include <set>
#include <utils/Dice.hpp>
#include <optional>
#include <unordered_map>

const std::unordered_map<std::string, int> validColorsMap = {
    {"BLACK",   COLOR_BLACK},
    {"RED",     COLOR_RED},
    {"GREEN",   COLOR_GREEN},
    {"YELLOW",  COLOR_YELLOW},
    {"BLUE",    COLOR_BLUE},
    {"MAGENTA", COLOR_MAGENTA},
    {"CYAN",    COLOR_CYAN},
    {"WHITE",   COLOR_WHITE}
};

const std::set<std::string> validColors = {
    "RED", "GREEN", "BLUE", "CYAN", "YELLOW", "MAGENTA", "WHITE", "BLACK"
};

const std::set<std::string> validAbilities = {
    "SMART", "TELE", "TUNNEL", "ERRATIC", "PASS", "PICKUP", "DESTROY", "UNIQ", "BOSS"
};

class NPCDescription
{
public:
    std::string name;
    std::string desc;
    std::vector<std::string> color;
    Dice dice_speed;
    std::vector<std::string> abil;
    Dice dice_hp;
    Dice dice_dam;
    char symb;
    int rrty;

    bool canBeGenerated = true;

    NPCDescription() :
        name(""),
        desc(""),
        color(),
        dice_speed(),
        abil(),
        dice_hp(),
        dice_dam(),
        symb(' '),
        rrty(0)
    {}

    NPCDescription(const std::string &name, const std::string &desc, const std::vector<std::string> &color,
                  const Dice &dice_speed, const std::vector<std::string> &abil, const Dice &dice_hp,
                  const Dice &dice_dam, char symb, int rrty) :
        name(name),
        desc(desc),
        color(color),
        dice_speed(dice_speed),
        abil(abil),
        dice_hp(dice_hp),
        dice_dam(dice_dam),
        symb(symb),
        rrty(rrty)
    {}

    // Destructor
    ~NPCDescription() {}

    static NPC* createNPC(NPCDescription &npcDesc, int ID, int descID);

    std::ostream &print(std::ostream &os) const;
    // Stream insertion operator as friend function
    friend std::ostream &operator<<(std::ostream &os, const NPCDescription &npc){ return npc.print(os); }


    static std::vector<NPCDescription> NPCParser();

    static std::string handleName(std::stringstream &ss);
    static std::optional<NPCDescription> parseMonster(std::ifstream &file);
    static std::string handleDescription(std::ifstream &file);
    static std::optional<std::vector<std::string>> handleDeliniatedList(std::stringstream &ss, const std::set<std::string> &validSet);
    static std::optional<Dice> handleDice(std::stringstream &ss);
};

#endif // NPCDescription_HPP