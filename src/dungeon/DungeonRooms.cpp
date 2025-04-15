//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <iostream>

// Initialize cells before generating rooms
void Dungeon::initializeCells()
{
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            if (y == 0 || y == DUNGEON_HEIGHT - 1 || x == 0 || x == DUNGEON_WIDTH - 1){
                grid[y][x].setCell(MAX_HARDNESS, ROCK);
            }
            else {
                int curr_hardness = rand() % (MAX_HARDNESS - 1 - MIN_HARDNESS) + 1;
                grid[y][x].setCell(curr_hardness, ROCK);
            }
        }
    }
}

// Generate rooms, used for random generation
bool Dungeon::generateRooms(){ 
    int numRooms = MIN_ROOMS + rand() % (MAX_ROOMS - MIN_ROOMS + 1);
    for (int i = 0; i < numRooms; i++)
    {
        if (!generateRandomRoom()) {
            rooms.clear(); // Clear rooms if failed to generate
            return false;
        }
    }
    return true;
}

bool Dungeon::canInsertRoom(Room &room){
    // Get room coordinates from the topLeft point
    int roomX = room.getTopLeft().getX();
    int roomY = room.getTopLeft().getY();
    int roomWidth = room.getWidth();
    int roomHeight = room.getHeight();
    
    // Check if room is within bounds
    if (roomX + (roomWidth - 1) > PLACABLE_WIDTH || roomY + (roomHeight - 1) > PLACABLE_HEIGHT) { 
        return false;
    }

    // Check area of room and bordering area to see if it is empty
    for (int x = roomX - 1; x < roomX + roomWidth + 1; x++) {
        for (int y = roomY - 1; y < roomY + roomHeight + 1; y++) {
            if (grid[y][x].getType() == FLOOR /*|| grid[y][x].getHardness() == MAX_HARDNESS*/) {
                return false; // Room overlaps with existing floor tiles
            }
        }
    }

    return true; // Room can be inserted
}

bool Dungeon::placeRoom(Room &room)
{
    if (!canInsertRoom(room)) {
        return false; // Cannot place room
    }
    int roomX = room.getTopLeft().getX();
    int roomY = room.getTopLeft().getY();
    int roomWidth = room.getWidth();
    int roomHeight = room.getHeight();
    
    // Place floor tiles for the room
    for (int x = roomX; x < roomX + roomWidth; x++) {
        for (int y = roomY; y < roomY + roomHeight; y++) {
            grid[y][x].setCell(MIN_HARDNESS, FLOOR);
        }
    }
    
    // Add room to rooms vector
    rooms.push_back(room);
    return true;
}

bool Dungeon::generateRandomRoom(){
    int attempts = 0;
    Room room;

    do {
        attempts++;
        if (attempts >= MAX_ATTEMPTS) { // Reset if too many attempts
            return false;
        }

        int x = (rand() % PLACABLE_WIDTH) + 1;
        int y = (rand() % PLACABLE_HEIGHT) + 1;

        // Subract current coordinate from the maximum width and height
        // to get the maximum available width and height
        int max_width = PLACABLE_WIDTH - x;
        int max_height = PLACABLE_HEIGHT - y;

        int random_width = (max_width > 0) ? (rand() % max_width) : MIN_ROOM_WIDTH;
        int random_height = (max_height > 0) ? (rand() % max_height) : MIN_ROOM_HEIGHT;
        int width = (random_width < MIN_ROOM_WIDTH) ? MIN_ROOM_WIDTH : random_width;
        int height = (random_height < MIN_ROOM_HEIGHT) ? MIN_ROOM_HEIGHT : random_height;
        
        // Create the room
        room = Room(x, y, width, height);
        
    } while (!canInsertRoom(room));

    // If we got here, the room is valid - place it in the dungeon
    placeRoom(room);
    return true;
}