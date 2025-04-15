//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <iostream>

void Dungeon::generateStairs(){
    // Generate Stairs
    int num_up_stairs = MIN_UP_STAIRS + rand() % (MAX_UP_STAIRS - MIN_UP_STAIRS + 1);
    for (int i = 0; i < num_up_stairs; i++){
        generateRandomStair(UP_STAIR);
    }

    int num_down_stairs = MIN_DOWN_STAIRS + rand() % (MAX_DOWN_STAIRS - MIN_DOWN_STAIRS + 1);
    for (int i = 0; i < num_down_stairs; i++){
        generateRandomStair(DOWN_STAIR);
    }
}

bool Dungeon::generateRandomStair(char stairType){
    int x, y;
    do {
        x = (rand() % PLACABLE_WIDTH) + 1;
        y = (rand() % PLACABLE_HEIGHT) + 1;
        if (grid[y][x].getType() == FLOOR) {
            break; // Found a valid position
        }
    } while (true);

    placeStair(x, y, stairType);
    
    return true;
}

bool Dungeon::placeStair(int x, int y, char stairType){
    if (x > 0 && x < PLACABLE_WIDTH && y > 0 && y < PLACABLE_HEIGHT) {
        Stair stair = Stair(x, y, stairType);
        grid[y][x] = stair;

        if (stair.getType() == UP_STAIR) {
            up_stairs.push_back(stair);
        } else if (stair.getType() == DOWN_STAIR) {
            down_stairs.push_back(stair);
        }
        return true;
    }
    return false;
}

bool Dungeon::isUpStair(int x, int y) const {
    for (const Stair& stair : up_stairs) {
        if (stair.getX() == x && stair.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Dungeon::isUpStair(Point p) const {
    return isUpStair(p.getX(), p.getY());
}

bool Dungeon::isDownStair(int x, int y) const {
    for (const Stair& stair : down_stairs) {
        if (stair.getX() == x && stair.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Dungeon::isDownStair(Point p) const {
    return isDownStair(p.getX(), p.getY());
}