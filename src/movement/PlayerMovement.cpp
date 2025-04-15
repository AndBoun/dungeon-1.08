//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <pathfinding/Dijkstras.hpp>

int Dungeon:: movePC(int x, int y, bool teleport){

    int pcX = getPC().getPosition().getX();
    int pcY = getPC().getPosition().getY();
    
    // Check stairs
    if (
        (x == -2 && y == -2 && isUpStair(pcX, pcY)) || 
        (x == -3 && y == -3 && isDownStair(pcX, pcY))
    ) {
        return -2; // Up or down stairs
    }

    // Check if the move is invalid (same position, rock, or non-zero hardness)
    if (
        !teleport && (
            (x == pcX && y == pcY) || 
            (getGrid()[y][x].getType() == ROCK)   || 
            (getGrid()[y][x].getHardness() > 0)   ||
            (x < 0 || x >= DUNGEON_WIDTH - 1)  || 
            (y < 0 || y >= DUNGEON_HEIGHT - 1)
        )
    ) {
        // printf("Player made an invalid move to (%d, %d)\n", x, y);
        return 0;
    }

    if (teleport) {
        // Check if the new position is within bounds
        if (grid[y][x].getHardness() == MAX_HARDNESS || (x == pcX && y == pcY)) {
            // printf("Player made an invalid teleport move to (%d, %d)\n", x, y);
            return 0;
        }
    }

    // Check if the new cell is occupied, and kill the occupant
    if (getNPCID(x, y) != -1){
        // printf("Player killed a monster: %c\n", d->grid[y][x].type);
        killNPC(x, y);
    }

    // printf("Player moved from (%d, %d) to (%d, %d)\n", d->pc.x, d->pc.y, x, y);

    // modifyGrid()[pcY][pcX].setType(getPC().getCurrentCell().getType()); // return the cell to its original type
    // getPC().setCurrentCell(getGrid()[y][x]); // update the current cell
    // modifyGrid()[y][x].setType(PLAYER); // update the grid with the player type

    // if (teleport) {
    //     fog[pcY][pcX].setType(grid[pcY][pcX].getType()); // update the fog grid
    // }

    getPC().setPosition(Point(x, y)); // update the player position

    Dijkstras::createDistanceMap(
        *this, 
        modifyNonTunnelingDistanceMap(),
        getPC().getPosition().getX(), 
        getPC().getPosition().getY(), 
        false
    );

    Dijkstras::createDistanceMap(
        *this, 
        modifyTunnelingDistanceMap(),
        getPC().getPosition().getX(), 
        getPC().getPosition().getY(), 
        true
    );

    return 1;
}