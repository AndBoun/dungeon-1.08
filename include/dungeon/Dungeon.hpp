//
// Created By Andrew Boun on 4/1/2025
//

#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <array>
#include <vector>
#include <memory>

#include <dungeon/base/Cell.hpp>
#include <dungeon/base/Room.hpp>
#include <dungeon/base/Stair.hpp>

#include <character/Character.hpp>
#include <character/PC.hpp>
#include <character/NPC.hpp>
#include <character/NPCDescription.hpp>
#include <item/Item.hpp>
#include <item/ItemDescription.hpp>

#include <utils/Point.hpp>

const char DEFAULT_NUM_MONSTERS = 10;

const int PLAYER_ID = 0; // Player ID

const char ROCK = ' '; // Rock
const char FLOOR = '.'; // Floor
const char UP_STAIR = '<'; // Up stair
const char DOWN_STAIR = '>'; // Down stair
const char CORRIDOR = '#'; // Corridor
const char PLAYER = '@'; // Player

const int DUNGEON_WIDTH = 80; // Width of the dungeon
const int DUNGEON_HEIGHT = 21; // Height of the dungeon
const int PLACABLE_WIDTH = 78; // Width of the playable area
const int PLACABLE_HEIGHT = 19; // Height of the playable area

const int MAX_HARDNESS = 255; // Maximum hardness of a cell
const int MIN_HARDNESS = 0; // Minimum hardness of a cell

const int MAX_ROOMS = 120; // Maximum number of randomly generated rooms
const int MIN_ROOMS = 6; // Minimum number of randomly generated rooms
const int MIN_ROOM_WIDTH = 4; // Minimum width of a room
const int MIN_ROOM_HEIGHT = 3; // Minimum height of a room

const int MIN_DOWN_STAIRS = 1;
const int MAX_DOWN_STAIRS = 4;
const int MIN_UP_STAIRS = 1;
const int MAX_UP_STAIRS = 4;

const int MAX_ATTEMPTS = 2000; // Maximum attempts to place a room

const int MOVEMENT_INVALID = 0;
const int MOVEMENT_SUCCESS = 1;
const int MOVEMENT_STAIRS = -2;

class Dungeon
{
public:
    std::vector<NPCDescription> npcDescList;
    std::vector<ItemDescription> itemDescList;


    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> grid;
    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> fog;
    std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> nonTunnelingDistanceMap;
    std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> tunnelingDistanceMap;
    
    std::vector<Room> rooms;
    std::vector<Stair> up_stairs;
    std::vector<Stair> down_stairs;
    std::vector<NPC*> npcs;

    PC pc;
    int numMonsterAlive;

    bool isFog = true; // Flag to indicate if fog of war is enabled
    
    // Constructor and Destructor
    Dungeon();
    ~Dungeon();

    // Get Arrays
    const std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& getGrid() { return grid; }
    const std::vector<Room>& getRooms () { return rooms; }
    const std::vector<Stair>& getUpStairs () { return up_stairs; }
    const std::vector<Stair>& getDownStairs () { return down_stairs; }
    const std::vector<NPC*>& getNPCs () { return npcs; }
    const std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& getNonTunnelingDistanceMap() { return nonTunnelingDistanceMap; }
    const std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& getTunnelingDistanceMap() { return tunnelingDistanceMap; }
    PC& getPC() { return pc; }
    int getNumMonsters() { return numMonsterAlive; }
    const std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& getFog() { return fog; }
    bool getFogStatus() { return isFog; }
    

    // Modify Arrays
    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& modifyGrid() { return grid; }
    std::vector<Room>& modifyRooms () { return rooms; }
    std::vector<Stair>& modifyStairs () { return up_stairs; }
    std::vector<Stair>& modifyDownStairs () { return down_stairs; }
    std::vector<NPC*>& modifyNPCs () { return npcs; }
    std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& modifyNonTunnelingDistanceMap() { return nonTunnelingDistanceMap; }
    std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& modifyTunnelingDistanceMap() { return tunnelingDistanceMap; }
    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& modifyFog() { return fog; }
    void setFogStatus(bool status) { isFog = status; }


    void generateRandomDungeon();

    bool generateRandomRoom();
    bool placeRoom(Room &room);

    bool placeStair(int x, int y, char stairType);
    bool generateRandomStair(char stairType);

    bool placeCharacterRandomly(Character *character);
    bool placeCharacterRandomly(Character &character);
    bool placeCharacter(Character *character, int x, int y);
    bool placeCharacter(Character &character, int x, int y);
    
    bool placeNPCsRandomly(int numNPCs = DEFAULT_NUM_MONSTERS);

    int startGameplay(int numNPCs = DEFAULT_NUM_MONSTERS);
    int movePC(int x, int y, bool teleport = false);
    bool moveNPC(NPC *npc);
    bool killNPC(int x, int y);
    bool killPC();
    
    void resetDungeon();

    void printDungeon() const;
    void printDistanceMap(const std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &distanceMap) const;

    bool isUpStair(int x, int y) const;
    bool isUpStair(Point p) const;
    bool isDownStair(int x, int y) const;
    bool isDownStair(Point p) const;
    
    int getNPCID(int x, int y) const;
    int getNPCID(Point p) const;

    NPC* pickRandomNPC();

private:
    void initializeCells();

    bool canInsertRoom(Room &room);
    bool generateRooms();

    void generateStairs();

    void generateCorridors();

    int calculateTiming(int speed) { return 1000 / speed; }


    bool hasLineOfSight(int x, int y);
    int is_valid_move_non_tunnel(int x, int y);
    int is_valid_move_tunnel(int x, int y);
    Point get_next_random_move(int x, int y, int tunneling);
    Point get_next_intelligent_move(NPC *npc, int tunneling);
    Point get_next_unintelligent_move(NPC *npc, int tunneling);
    int move_non_tunnel(NPC *npc, int new_x, int new_y);
    int move_tunnel(NPC *npc, int new_x, int new_y);

    // void init_fog_grid();
    void update_fog_grid();
    void reset_fog_grid(); // reset to original grid, then update fog grid
};

#endif