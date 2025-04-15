//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <utils/priority_queue.h>
#include <iostream>
#include <unistd.h>
#include <ui/ui.hpp>

// // this function should not be called, dungeon starts empty
// void Dungeon::init_fog_grid(){
//     for (int y = 0; y < DUNGEON_HEIGHT; y++) {
//         for (int x = 0; x < DUNGEON_WIDTH; x++) {
//             Cell cell = grid[y][x];
//             fog[y][x].setCell(cell.getHardness(), cell.getType());
//         }
//     }
// }

void Dungeon::update_fog_grid(){
    // for (int y = 0; y < DUNGEON_HEIGHT; y++) {
    //     for (int x = 0; x < DUNGEON_WIDTH; x++) {
    //         char cell_type = fog[y][x].getType();
    //         if ((cell_type >= '0' && cell_type <= '9') || (cell_type >= 'A' && cell_type <= 'F')) {
    //             fog[y][x].setType(fog[y][x].getOldType()); // Restore the old type
    //         }
    //     }
    // }

    int pc_x = pc.getPosition().getX();
    int pc_y = pc.getPosition().getY();

    int start_x = std::max(0, pc_x - 2);
    int end_x = std::min(DUNGEON_WIDTH - 1, pc_x + 2);

    int start_y = std::max(0, pc_y - 2);
    int end_y = std::min(DUNGEON_HEIGHT - 1, pc_y + 2);

    for (int y = start_y; y <= end_y; y++) {
        for (int x = start_x; x <= end_x; x++) {
            // Update the fog with the actual grid cell
            fog[y][x] = grid[y][x];
            // char cell_type = fog[y][x].getType();
            // if ((cell_type >= '0' && cell_type <= '9') || (cell_type >= 'A' && cell_type <= 'F')) {
            //     fog[y][x].setOldType(npcs[getNPCID(x, y)].getCurrentCell().getType()); // Store the old type
            // }
        }
    }
}

void Dungeon::reset_fog_grid(){
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            fog[y][x].setCell(MAX_HARDNESS, ROCK); // Reset to rock
        }
    }
}