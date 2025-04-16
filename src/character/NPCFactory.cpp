//
// Created by Andrew Boun on 4/15/25.
//

#include <character/NPCDescription.hpp>

NPC* NPCDescription::createNPC(NPCDescription &npcDesc, int ID, int descID){
    std::vector<int> color;

	NPC *npc = new NPC();
    npc->alive = true;
    npc->ID = ID;
    npc->descID = descID;
    npc->speed = npcDesc.dice_speed.getRandNum();
    npc->hp = npcDesc.dice_hp.getRandNum();
    npc->dice_dam = npcDesc.dice_dam;
    npc->symbol = npcDesc.symb;
    npc->rrty = npcDesc.rrty;
    
    // add colors
    for (const auto &c : npcDesc.color) {
        auto it = validColorsMap.find(c);
        if (it != validColorsMap.end()) {
            if (it->second == COLOR_BLACK) {
                // If the color is BLACK, set it to WHITE
                color.push_back(COLOR_WHITE);
            } else {
                // Otherwise, use the actual color value
                color.push_back(it->second);
            }
        } 
    }
    npc->color = color;

    // add abilities
    for (const auto &a : npcDesc.abil) {
        if (a == "SMART") {
            npc->intelligent = 1;
        } else if (a == "TELE") {
            npc->telepathy = 1;
        } else if (a == "TUNNEL") {
            npc->tunneling = 1;
        } else if (a == "ERRATIC") {
            npc->erratic = 1;
        } else if (a == "PASS") {
            npc->passive = 1;
        } else if (a == "PICKUP") {
            npc->pickUp = 1;
        } else if (a == "DESTROY") {
            npc->destroy = 1;
        } else if (a == "UNIQ") {
            npc->unique = 1;
        } else if (a == "BOSS") {
            npc->boss = 1;
        }
    }

    return npc;
}