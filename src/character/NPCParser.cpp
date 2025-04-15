//
// Created by Andrew Boun on 4/8/25.
//

#include <character/NPC.hpp>

#include <fstream>
#include <iostream>
#include <sstream>


std::vector<NPC> NPC::NPCParser(){
    std::vector<NPC> npcs;

    const char* home = std::getenv("HOME");
    std::string filePath = std::string(home) + "/.rlg327/monster_desc.txt";

    std::ifstream file(filePath);

    std::string line;
    std::getline(file, line);

    if (line != NPC_HEADER){ 
        std::cerr << "Invalid file format" << std::endl;
        exit(0);
    }

    while (std::getline(file, line)){
        if (line == NPC_BEGIN_MONSTER){
            auto monster = parseMonster(file);
            if (monster){
                NPC npc = monster.value();
                npcs.push_back(npc);
            }
        }
    }

    return npcs;
}

std::optional<NPC> NPC::parseMonster(std::ifstream &file){
    NPC npc;
    std::string line;

    bool name, desc, color, speed, abil, hp, dam, symb, rrty;
    name = desc = color = speed = abil = hp = dam = symb = rrty = false;

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string word;
        ss >> word;

        if (word == NPC_NAME){
            if (name) return std::nullopt;
            npc.name = handleName(ss);
            if (npc.name.empty()) return std::nullopt;
            name = true;
        }
        else if (word == NPC_DESC){
            if (desc) return std::nullopt;
            npc.desc = handleDescription(file);
            if (npc.desc.empty()) return std::nullopt;
            desc = true;
        }
        else if (word == NPC_COLOR){
            if (color) return std::nullopt;
            if (auto tempList = handleDeliniatedList(ss, validColors)){ // true for color mode
                npc.color = tempList.value();
                color = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == NPC_SPEED){
            if (speed) return std::nullopt;
            if (auto tempDice = handleDice(ss)){
                npc.speed = tempDice.value();
                speed = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == NPC_ABIL){
            if (abil) return std::nullopt;
            if (auto tempList = handleDeliniatedList(ss, validAbilities)){ // false for color mode, true for ability mode
                npc.abil = tempList.value();
                abil = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == NPC_HP){
            if (hp) return std::nullopt;
            if (auto tempDice = handleDice(ss)){
                npc.hp = tempDice.value();
                hp = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == NPC_DAM){
            if (dam) return std::nullopt;
            if (auto tempDice = handleDice(ss)){
                npc.dam = tempDice.value();
                dam = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == NPC_SYMB){
            std::string symbStr;
            if (symb) return std::nullopt;
            ss >> symbStr;
            if (symbStr.length() > 1 || symbStr.empty()) return std::nullopt;
            npc.symb = symbStr[0];
            symb = true;
        }
        else if (word == NPC_RRTY){
            if (rrty) return std::nullopt;
            ss >> npc.rrty;
            if (npc.rrty < 0 || npc.rrty > 100) return std::nullopt;
            rrty = true;
        } 
        else if (word == NPC_END) {
            break;
        }
        else if (word == NPC_BEGIN_MONSTER){
            // if we encounter another BEGIN_MONSTER,
            // stop parsing current monster, recursively call parseMonster
            // to parse the next monster
            return parseMonster(file);
        }
        else {
            return std::nullopt;
        }
    }

    if (!name || !desc || !color || !speed || !abil || !hp || !dam || !symb || !rrty){
        std::cerr << "Missing required fields" << std::endl;
        return std::nullopt;
    }

    return npc;
}

std::string NPC::handleName(std::stringstream &ss){
    std::string tempStr;
    std::string name;

    if (ss.eof()) return "";

    ss >> tempStr;
    name += tempStr;

    while (ss >> tempStr){
        name += " " + tempStr;
    }

    return name;
}

std::string NPC::handleDescription(std::ifstream &file){
    std::string line;
    std::string desc;

    if(file.eof()) return "";

    while (std::getline(file, line)){
        if (line == ".") break;
        if (line.length() > 77){
            std::cerr << "Description line too long" << std::endl;
            return "";
        }
        desc += line + "\n";
    }

    return desc;
}

std::optional<std::vector<std::string>> NPC::handleDeliniatedList(std::stringstream &ss, const std::set<std::string> &validSet){
    std::vector<std::string> list;
    std::string word;

    if (ss.eof()) return std::nullopt;

    while (ss >> word){
        if (validSet.find(word) == validSet.end()) {
            return std::nullopt;
        }
        list.push_back(word);
    }

    return list;
}

std::optional<Dice> NPC::handleDice(std::stringstream &ss){
    std::string diceStr;
    ss >> diceStr;

    size_t plusPos = diceStr.find('+');
    size_t dPos = diceStr.find('d');
    if (
        diceStr.empty() ||
        plusPos == std::string::npos ||
        dPos == std::string::npos
    ) {
            return std::nullopt;
    }

    try {
        // Extract base (before '+')
        int base = std::stoi(diceStr.substr(0, plusPos));
        
        // Extract numDice (between '+' and 'd')
        int numDice = std::stoi(diceStr.substr(plusPos + 1, dPos - plusPos - 1));
        
        // Extract numSides (after 'd')
        int numSides = std::stoi(diceStr.substr(dPos + 1));
        
        // Create Dice object and assign to NPC
        return Dice(base, numDice, numSides);
    } 
    catch (const std::exception& e) {
        // Handle conversion errors
        return std::nullopt;
    }

}

