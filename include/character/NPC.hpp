//
// Created By Andrew Boun on 4/2/2025
//

#ifndef NPC_HPP
#define NPC_HPP
#include <character/Character.hpp>
#include <string>
#include <vector>
#include <set>
#include <utils/Dice.hpp>
#include <optional>
#include <ncurses.h>

const std::string NPC_HEADER = "RLG327 MONSTER DESCRIPTION 1";
const std::string NPC_BEGIN_MONSTER = "BEGIN MONSTER";
const std::string NPC_END = "END";
const std::string NPC_NAME = "NAME";
const std::string NPC_DESC = "DESC";
const std::string NPC_COLOR = "COLOR";
const std::string NPC_SPEED = "SPEED";
const std::string NPC_ABIL = "ABIL";
const std::string NPC_HP = "HP";
const std::string NPC_DAM = "DAM";
const std::string NPC_SYMB = "SYMB";
const std::string NPC_RRTY = "RRTY";


class NPC : public Character
{
public:
    int intelligent = 0; // 0 or 1
    int telepathy = 0; // 0 or 1
    int tunneling = 0; // 0 or 1
    int erratic = 0; // 0 or 1
    int passive = 0; // 0 or 1
    int pickUp = 0; // 0 or 1
    int destroy = 0; // 0 or 1
    int unique = 0; // 0 or 1
    int boss = 0; // 0 or 1
    Point pcPosition; // Position of the PC

    int descID; //used to identify the monster from the description file

    // std::string name;
    // std::string desc;
    std::vector<int> color;
    // int speed; declared in character
    // std::vector<std::string> abil; declared with above ints
    int hp;
    Dice dice_dam;
    // char symbol; declared in character
    int rrty;

    


    NPC();
    NPC(Point position, bool isAlive, int ID);
    ~NPC();


    // Getters
    int getIntelligent() const { return intelligent; }
    int getTelepathy() const { return telepathy; }
    int getTunneling() const { return tunneling; }
    int getErratic() const { return erratic; }
    const Point& getPCPostion() const { return pcPosition; }

    // Setters
    void setPCPosition(const Point& position) { pcPosition = position; }
};

#endif