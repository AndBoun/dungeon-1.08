//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <math.h>

bool Dungeon::placeNPCsRandomly(int numNPCS)
{
    for (int i = 0; i < numNPCS; i++) {
        NPC npc = NPC(Point(), true, i);
        if (placeCharacterRandomly(npc)) {
            npcs.push_back(npc);
        }
    }
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

bool Dungeon::placeCharacter(Character &character, int x, int y){
    if (x < 1 || x >= PLACABLE_WIDTH || y < 1 || y >= PLACABLE_HEIGHT) {
        return false; // Out of bounds
    }
    if (grid[y][x].getType() != FLOOR) {
        return false; // Not a valid cell
    }

    character.setPosition(Point(x, y));
    // character.setCurrentCell(grid[y][x]);
    // grid[y][x].setType(character.getSymbol());
    return true;
}