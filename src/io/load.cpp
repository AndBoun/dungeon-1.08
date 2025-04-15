//
// Created By Andrew Boun on 4/2/2025
//

#include <io/SaveLoad.hpp>
#include <iostream>

bool SaveLoad::load(Dungeon &d)
{
    f = fopen(dungeonFile.c_str(), "rb");

    std::cout << "Home: " << home << std::endl;
    std::cout << "Dungeon file: " << dungeonFile << std::endl;
    
    std::string marker = loadMarker();
    std::cout << "Marker: " << marker << std::endl;
    if (marker != EXPECTED_MARKER) {
        std::cerr << "Error: Invalid marker" << std::endl;
        return false;
    }
    
    uint32_t version = loadVersion();
    std::cout << "Version: " << version << std::endl;
    
    uint32_t size = loadSize();
    std::cout << "Size: " << size << std::endl;
    
    if (!loadPC(d)) return false;
    // std::cout << "PC: x: " << d->pc.x << " \t y: " << d->pc.y << std::endl;
    
    if (!loadHardness(d)) return false;
    
    int numRooms = loadNumRooms(d);
    std::cout << "Number of rooms: " << numRooms << std::endl;
    if (!loadRooms(d, numRooms)) return false;

    int numUpStairs = loadNumUpStairs(d);
    // std::cout << "Number of up stairs: " << d->numUpStairs << std::endl;
    if (!loadUpStairs(d, numUpStairs)) return false;
    
    int numDownStairs = loadNumDownStairs(d);
    // std::cout << "Number of down stairs: " << d->numDownStairs << std::endl;
    if (!loadDownStairs(d, numDownStairs)) return false;
    
    fillInCorridors(d);
    
    d.placeCharacter(
        d.getPC(), 
        d.getPC().getPosition().getX(), 
        d.getPC().getPosition().getY()
    );
    
    fclose(f);
    return true;
}

std::string SaveLoad::loadMarker()
{
    char marker[13]; // 12 bytes + 1 for null terminator
    
    // Read exactly 12 bytes
    if (fread(marker, sizeof(char), 12, f) != 12) {
        std::cerr << "Error: Could not read marker from file" << std::endl;
        return "";
    }
    
    // Null terminate the string
    marker[12] = '\0';
    
    return std::string(marker);
}

uint32_t SaveLoad::loadVersion()
{
    uint32_t version;
    
    // Read exactly 4 bytes
    if (fread(&version, sizeof(version), 1, f) != 1) {
        std::cerr << "Error: Could not read version from file" << std::endl;
        return 1;
    }
    
    return be32toh(version);
}

uint32_t SaveLoad::loadSize()
{
    uint32_t size;
    
    // Read exactly 4 bytes
    if (fread(&size, sizeof(size), 1, f) != 1) {
        std::cerr << "Error: Could not read size from file" << std::endl;
        return 1;
    }
    
    return be32toh(size);
}

bool SaveLoad::loadPC(Dungeon &d)
{
    uint8_t pc[2]; // player character
    
    // Read exactly 2 bytes
    if (fread(pc, sizeof(uint8_t), 2, f) != 2) {
        std::cerr << "Error: Could not read pc from file" << std::endl;
        return false;
    }
    // initialize player, set curr_cell to FLOOR temporarily, will be set correctly in load()
    // d->initPlayer(pc[0], pc[1], FLOOR);
    d.getPC().setPosition(Point(pc[0], pc[1]));
    d.placeCharacter(d.getPC(), pc[0], pc[1]);

    return true;
}

bool SaveLoad::loadHardness(Dungeon &d)
{
    std::vector<uint8_t> hardness(1680); // 1680 bytes for hardness
    
    // Read exactly 1680 bytes
    if (fread(hardness.data(), sizeof(uint8_t), 1680, f) != 1680) {
        std::cerr << "Error: Could not read hardness from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < 1680; i++) {
        Cell &cell = d.modifyGrid()[i / DUNGEON_WIDTH][i % DUNGEON_WIDTH];
        cell.setHardness(hardness[i]);
        cell.setType(ROCK);
    }
    
    return true;
}

int SaveLoad::loadNumRooms(Dungeon &d)
{
    uint16_t numRooms;
    
    if (fread(&numRooms, sizeof(uint16_t), 1, f) != 1) {
        std::cerr << "Error: Could not read num_rooms from file" << std::endl;
        return false;
    }
    
    numRooms = be16toh(numRooms);
    numRooms = static_cast<int>(numRooms);
    
    return numRooms;
}

bool SaveLoad::loadRooms(Dungeon& d, int numRooms)
{
    std::vector<uint8_t> rooms(numRooms * 4); // 4 bytes per room
    
    if (fread(rooms.data(), sizeof(uint8_t), numRooms * 4, f) != (uint32_t)numRooms * 4) {
        std::cerr << "Error: Could not read rooms from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < numRooms; i++) {
        Room room = Room(
            static_cast<int>(rooms[i * 4]), // x
            static_cast<int>(rooms[i * 4 + 1]), // y
            static_cast<int>(rooms[i * 4 + 2]), // width
            static_cast<int>(rooms[i * 4 + 3]) // height
        );
        
        d.placeRoom(room);
    }
    
    return true;
}

int SaveLoad::loadNumUpStairs(Dungeon& d)
{
    uint16_t numUpStairs;
    
    if (fread(&numUpStairs, sizeof(uint16_t), 1, f) != 1) {
        std::cerr << "Error: Could not read num_up_stairs from file" << std::endl;
        return -1;
    }
    
    numUpStairs = be16toh(numUpStairs);
    numUpStairs = static_cast<int>(numUpStairs);
    
    return numUpStairs;
}

bool SaveLoad::loadUpStairs(Dungeon& d, int numUpStairs)
{
    std::vector<uint8_t> upStairs(numUpStairs * 2); // 2 bytes per up_stairs
    
    if (fread(upStairs.data(), sizeof(uint8_t), numUpStairs * 2, f) != (uint32_t)numUpStairs * 2) {
        std::cerr << "Error: Could not read up_stairs from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < numUpStairs; i++) {
        d.placeStair(
            static_cast<int>(upStairs[i * 2]), // x
            static_cast<int>(upStairs[i * 2 + 1]), // y
            UP_STAIR // type
        );
    }
    
    return true;
}

int SaveLoad::loadNumDownStairs(Dungeon& d)
{
    uint16_t numDownStairs;
    
    if (fread(&numDownStairs, sizeof(uint16_t), 1, f) != 1) {
        std::cerr << "Error: Could not read num_down_stairs from file" << std::endl;
        return -1;
    }
    
    numDownStairs = be16toh(numDownStairs);
    numDownStairs = static_cast<int>(numDownStairs);
    
    return numDownStairs;
}

bool SaveLoad::loadDownStairs(Dungeon& d, int numDownStairs)
{
    std::vector<uint8_t> downStairs(numDownStairs * 2); // 2 bytes per down_stairs
    
    if (fread(downStairs.data(), sizeof(uint8_t), numDownStairs * 2, f) != (uint32_t)numDownStairs * 2) {
        std::cerr << "Error: Could not read down_stairs from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < numDownStairs; i++) {
        d.placeStair(
            static_cast<int>(downStairs[i * 2]), // x
            static_cast<int>(downStairs[i * 2 + 1]), // y
            DOWN_STAIR // type
        );
    }
    
    return true;
}

bool SaveLoad::fillInCorridors(Dungeon& d)
{
    for (int i = 0; i < DUNGEON_HEIGHT; i++) {
        for (int j = 0; j < DUNGEON_WIDTH; j++) {
            if (d.getGrid()[i][j].getType() == ROCK && d.getGrid()[i][j].getHardness() == 0) {
                d.modifyGrid()[i][j].setType(CORRIDOR);
            }
        }
    }
    
    return true;
}
