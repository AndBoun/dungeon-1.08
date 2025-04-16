//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <math.h>

NPC* Dungeon::pickRandomNPC()
{
    do {
        int randomIndex = rand() % npcDescList.size();
        int rrty = rand() % 100;

        NPCDescription npcDesc = npcDescList[randomIndex];
        
        if (npcDesc.rrty > rrty && npcDesc.canBeGenerated) {

            // Prevent placing unique NPCs multiple times
            bool uniqueNPCExists = false;
            for (const auto& npc : npcs) {
                if (npc->unique && npc->descID == randomIndex) {
                    uniqueNPCExists = true;
                    break;
                }
            }
            if (uniqueNPCExists) {
                continue; // Skip this NPC if it's unique and already exists
            }

            NPC *npc = NPCDescription::createNPC(npcDescList[randomIndex], 0, randomIndex);
            return npc;
        }
    } while (true);
    return nullptr;
}

bool Dungeon::placeNPCsRandomly(int numNPCS)
{
    for (int i = 0; i < numNPCS; i++) {
        NPC *npc = pickRandomNPC();
        npc->ID = i;

        if (placeCharacterRandomly(npc)) {
            npcs.push_back(npc);
        }
    }
    return true;
}

bool Dungeon::placeCharacterRandomly(Character *character){
    do {
        int x = rand() % PLACABLE_WIDTH + 1;
        int y = rand() % PLACABLE_HEIGHT + 1;
        if (grid[y][x].getType() == FLOOR && x > 0 && y > 0 && getNPCID(x, y) == -1 && pc.getPosition() != Point(x, y)) {
            if (placeCharacter(character, x, y)){
                return true; // Successfully placed
            }
        }
    } while (true);
    return true;
}

bool Dungeon::placeCharacterRandomly(Character &character){
    do {
        int x = rand() % PLACABLE_WIDTH + 1;
        int y = rand() % PLACABLE_HEIGHT + 1;
        if (grid[y][x].getType() == FLOOR && x > 0 && y > 0 && getNPCID(x, y) == -1 && pc.getPosition() != Point(x, y)) {
            if (placeCharacter(character, x, y)){
                return true; // Successfully placed
            }
        }
    } while (true);
    return true;
}

bool Dungeon::placeCharacter(Character *character, int x, int y){
    if (x < 1 || x >= PLACABLE_WIDTH || y < 1 || y >= PLACABLE_HEIGHT) {
        return false; // Out of bounds
    }
    if (grid[y][x].getType() != FLOOR) {
        return false; // Not a valid cell
    }

    character->setPosition(Point(x, y));
    return true;
}

bool Dungeon::placeCharacter(Character &character, int x, int y){
    if (x < 1 || x >= PLACABLE_WIDTH || y < 1 || y >= PLACABLE_HEIGHT) {
        return false; // Out of bounds
    }
    if (grid[y][x].getType() != FLOOR) {
        return false; // Not a valid cell
    }

    character.setPosition(Point(x, y));
    return true;
}