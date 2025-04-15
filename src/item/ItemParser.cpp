//
// Created By Andrew Boun on 4/2/2025
//

#include <item/Item.hpp>
#include <character/NPC.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>

std::vector<Item> Item::itemParser(){
    std::vector<Item> items;

    const char* home = std::getenv("HOME");
    std::string filePath = std::string(home) + "/.rlg327/object_desc.txt";

    std::ifstream file(filePath);

    std::string line;
    std::getline(file, line);

    if (line != ITEM_HEADER){ 
        std::cerr << "Invalid file format" << std::endl;
        exit(0);
    }

    while (std::getline(file, line)){
        if (line == ITEM_BEGIN_OBJECT){
            auto monster = parseItem(file);
            if (monster){
                Item item = monster.value();
                items.push_back(item);
            }
        }
    }

    return items;
}

std::optional<Item> Item::parseItem(std::ifstream &file){
    Item item;
    std::string line;

    bool name, desc, type, color, hit, dam, dodge, def, weight, speed, attr, val, art, rrty;
    name = desc = type = color = hit = dam = dodge = def = weight = speed = attr = val = art = rrty = false;

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string word;
        ss >> word;

        if (word == ITEM_NAME){
            if (name) return std::nullopt;
            item.name = NPC::handleName(ss);
            if (item.name.empty()) return std::nullopt;
            name = true;
        }
        else if (word == ITEM_DESC){
            if (desc) return std::nullopt;
            item.desc = NPC::handleDescription(file);
            if (item.desc.empty()) return std::nullopt;
            desc = true;
        }
        else if (word == ITEM_TYPE){ //TODO
            if (type) return std::nullopt;
            // ss >> item.type;
            auto tempType = NPC::handleDeliniatedList(ss, validTypes);
            if (!tempType || tempType.value().size() != 1) return std::nullopt;
            item.type = tempType.value()[0];
            type = true;
        }
        else if (word == ITEM_COLOR){
            if (color) return std::nullopt;
            auto colors = NPC::handleDeliniatedList(ss, validColors); // true for color mode
            if (!colors) return std::nullopt;
            item.color = colors.value()[0];
            color = true;
        }
        else if (word == ITEM_HIT){
            if (hit) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_hit = tempDice.value();
            } else {
                return std::nullopt;
            }
            hit = true;
        }
        else if (word == ITEM_DAM){
            if (dam) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_dam = tempDice.value();
                dam = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == ITEM_DODGE){
            if (dodge) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_dodge = tempDice.value();
                dodge = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == ITEM_DEF){
            if (def) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_def = tempDice.value();
                def = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == ITEM_WEIGHT){
            if (weight) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_weight = tempDice.value();
                weight = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == ITEM_SPEED){
            if (speed) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_speed = tempDice.value();
                speed = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == ITEM_ATTR){
            if (attr) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_attr = tempDice.value();
                attr = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == ITEM_VAL){
            if (val) return std::nullopt;
            if (auto tempDice = NPC::handleDice(ss)){
                item.dice_val = tempDice.value();
                val = true;
            } else {
                return std::nullopt;
            }
        }
        else if (word == ITEM_ART){
            if (art) return std::nullopt;
            ss >> item.art;
            if (!item.art.empty() && item.art != "FALSE" && item.art != "TRUE") return std::nullopt;
            art = true; 
        }
        else if (word == ITEM_RRTY){
            if (rrty) return std::nullopt;
            ss >> item.rrty;
            if (item.rrty < 0 || item.rrty > 100) return std::nullopt;
            rrty = true;
        }
        else if (word == ITEM_END) {
            break;
        }
        else if (word == ITEM_BEGIN_OBJECT){
            return parseItem(file);
        }
        else {
            return std::nullopt;
        }
    }

    if (!name || !desc || !type || !color || !hit || !dam || !dodge || !def || !weight || !speed || !attr || !val || !art || !rrty){
        std::cerr << "Missing required fields" << std::endl;
        return std::nullopt;
    }

    return item;
}