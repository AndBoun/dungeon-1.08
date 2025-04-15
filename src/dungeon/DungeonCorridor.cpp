//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <iostream>

void Dungeon::generateCorridors()
{
    for (size_t i = 0; i < rooms.size() - 1; i++)
    {
        int x1 = rooms[i].getCenter().getX();
        int y1 = rooms[i].getCenter().getY();
        int x2 = rooms[i + 1].getCenter().getX();
        int y2 = rooms[i + 1].getCenter().getY();

        // 0 for horizontal, 1 for vertical, 2 for diagonal
        int direction = rand() % 3;

        while (x1 != x2 || y1 != y2){
            if (direction == 0 && x1 != x2){
                if (x1 < x2) x1++; 
                else x1--;
    
            } else if (direction == 1 && y1 != y2){
                if (y1 < y2) y1++;
                else y1--;
    
            } else {
                if (x1 != x2){
                    if (x1 < x2) x1++;
                    else x1--;
    
                    // Ensure diagonal movement is possible by only
                    // up and down movements by adding an extra corridor
                    if (grid[y1][x1].getType() == ROCK) {
                        grid[y1][x1].setType(CORRIDOR);
                        grid[y1][x1].setHardness(MIN_HARDNESS);
                    }
                }
    
                if (y1 < y2){
                    y1++;
                } else if (y1 > y2){
                    y1--;
                }
            }
    
            if (grid[y1][x1].getType() == ROCK) {
                grid[y1][x1].setType(CORRIDOR);
                grid[y1][x1].setHardness(MIN_HARDNESS);
            }
        }
    }
}
