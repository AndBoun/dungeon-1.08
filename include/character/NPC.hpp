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

const std::set<std::string> validColors = {
    "RED", "GREEN", "BLUE", "CYAN", "YELLOW", "MAGENTA", "WHITE", "BLACK"
};

const std::set<std::string> validAbilities = {
    "SMART", "TELE", "TUNNEL", "ERRATIC", "PASS", "PICKUP", "DESTROY", "UNIQ", "BOSS"
};

class NPC : public Character
{
public:
    int intelligent; // 0 or 1
    int telepathy; // 0 or 1
    int tunneling; // 0 or 1
    int erratic; // 0 or 1
    Point pcPosition; // Position of the PC

    std::string name;
    std::string desc;
    std::vector<std::string> color;
    Dice speed;
    std::vector<std::string> abil;
    Dice hp;
    Dice dam;
    char symb;
    int rrty;

    


    NPC();
    NPC(Point position, Cell cell, bool isAlive, int ID);
    ~NPC();

    static std::vector<NPC> NPCParser();

    std::ostream &print(std::ostream &os) const;
    
    // Stream insertion operator as friend function
    friend std::ostream &operator<<(std::ostream &os, const NPC &npc){ return npc.print(os); }

    // Getters
    int getIntelligent() const { return intelligent; }
    int getTelepathy() const { return telepathy; }
    int getTunneling() const { return tunneling; }
    int getErratic() const { return erratic; }
    const Point& getPCPostion() const { return pcPosition; }

    // Setters
    void setPCPosition(const Point& position) { pcPosition = position; }


    static std::string handleName(std::stringstream &ss);
    static std::optional<NPC> parseMonster(std::ifstream &file);
    static std::string handleDescription(std::ifstream &file);
    static std::optional<std::vector<std::string>> handleDeliniatedList(std::stringstream &ss, const std::set<std::string> &validSet);
    static std::optional<Dice> handleDice(std::stringstream &ss);
};

#endif