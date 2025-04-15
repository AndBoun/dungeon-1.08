//
// Created By Andrew Boun on 4/2/2025
//

#include <character/NPC.hpp>
#include <dungeon/Dungeon.hpp>
#include <math.h>

NPC::~NPC() {}

NPC::NPC() : Character(Point(), 0, '!', false, 0) {}

NPC::NPC(Point position, bool isAlive, int ID){
    intelligent = rand() % 2, telepathy = rand() % 2;
    tunneling = rand() % 2, erratic = rand() % 2;

    // intelligent = 1, telepathy = 1;
    // tunneling = 1, erratic = 1;

    speed = (rand() % 16) + 5;
    // speed = Dice(0, 1, 16);

    this->position = position;

    pcPosition = Point(-1, -1); // PC position is unknown

    int traits = 
        intelligent +
        (telepathy << 1) +
        (tunneling << 2) +
        (erratic << 3);

    if (traits < 10) {
        symbol = '0' + traits; // 0-9
    } else {
        symbol = 'A' + (traits - 10); // A-F
    }


    this->alive = isAlive;
    this->ID = ID;
}

int Dungeon::getNPCID(int x, int y) const{
    for (size_t i = 0; i < npcs.size(); i++){
        if (npcs[i].getPosition().getX() == x && npcs[i].getPosition().getY() == y){
            return i;
        }
    }
    return -1;
}

int Dungeon::getNPCID(Point p) const{
    return getNPCID(p.getX(), p.getY());
}

std::ostream &NPC::print(std::ostream &os) const {
    os << NPC_BEGIN_MONSTER;
    os << "\n" << NPC_NAME << " " << name;
    os << "\n" << NPC_DESC << "\n" << desc;
    os << ".";
    os << "\n" << NPC_COLOR << " ";
    for (const auto &c : color) {
        os << c << " ";
    }
    os << "\n" << NPC_SPEED << " " << dice_speed;
    os << "\n" << NPC_ABIL << " ";
    for (const auto &a : abil) {
        os << a << " ";
    }
    os << "\n" << NPC_HP << " " << dice_hp;
    os << "\n" << NPC_DAM << " " << dice_dam;
    os << "\n" << NPC_SYMB << " " << symb;
    os << "\n" << NPC_RRTY << " " << rrty;
    os << "\n" << NPC_END << "\n";
    return os;
}