//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <utils/priority_queue.h>
#include <iostream>
#include <unistd.h>
#include <ui/ui.hpp>

Dungeon::Dungeon() {}
Dungeon::~Dungeon() {}

void Dungeon::resetDungeon()
{
    // Clear rooms, stairs, and NPCs
    reset_fog_grid(); // Reset the fog grid
    rooms.clear();
    up_stairs.clear();
    down_stairs.clear();
    npcs.clear();
    generateRandomDungeon(); // Regenerate the dungeon
}

void Dungeon::generateRandomDungeon()
{
    do {
        initializeCells(); // Initialize the cells with rock
        if (!generateRooms()) continue; // Generate rooms, reset if failed
        generateCorridors();
        generateStairs();
        placeCharacterRandomly(pc); // Place the player character randomly
        fog[pc.getPosition().getY()][pc.getPosition().getX()].setType(pc.getSymbol());
        break;
    } while (true);
}

bool Dungeon::placeNPCsRandomly(int numNPCS)
{
    for (int i = 0; i < numNPCS; i++) {
        NPC npc = NPC(Point(), Cell(), true, i);
        if (placeCharacterRandomly(npc)) {
            npcs.push_back(npc);
        }
    }
    return true;
}

// this function should not be called, dungeon starts empty
void Dungeon::init_fog_grid(){
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            Cell cell = grid[y][x];
            fog[y][x].setCell(cell.getHardness(), cell.getType());
        }
    }
}

void Dungeon::update_fog_grid(){
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            char cell_type = fog[y][x].getType();
            if ((cell_type >= '0' && cell_type <= '9') || (cell_type >= 'A' && cell_type <= 'F')) {
                fog[y][x].setType(fog[y][x].getOldType()); // Restore the old type
            }
        }
    }

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
            char cell_type = fog[y][x].getType();
            if ((cell_type >= '0' && cell_type <= '9') || (cell_type >= 'A' && cell_type <= 'F')) {
                fog[y][x].setOldType(npcs[getNPCID(x, y)].getCurrentCell().getType()); // Store the old type
            }
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

int Dungeon::startGameplay(int numNPCS){
    // initialize_monsters(d);
    // init_fog_grid(); // Initialize fog grid
    placeNPCsRandomly(numNPCS); // Place NPCs randomly
    numMonsterAlive = numNPCS; // Set the number of monsters alive
    int num_entities = getNPCs().size() + 1;

    // Create a priority queue for the entities
    // Only keys are needed, no data
    PriorityQueue *pq = pq_create(num_entities, num_entities, NULL, NULL);

    // Initialize the priority queue with the player and monsters
    // entity = (0) is the player, PLAYER_ID
    // entity = (i + 1), are the monsters, where i = index or monster_ID
    pq_insert(pq, 0, NULL, PLAYER_ID);
    for (size_t i = 0; i < getNPCs().size(); i++){
        pq_insert(pq, i + 1, NULL, 0); // all entities start at time 0
    }

    // render_grid(d); // Render the dungeon

    while (getPC().isAlive() && numMonsterAlive > 0) {

        int entity_id = pq_get_min_key(pq);
        int current_time = pq_get_priority(pq, entity_id);
        int next_time;


        if (entity_id == PLAYER_ID) { // Player's turn
            // ui::render_grid(*this); // Render the dungeon
            update_fog_grid(); // Update the fog of war
            // ui::render_grid(fog); // Render the fog of war
            if (getFogStatus()) {
                ui::render_grid(getFog());
            } else {
                ui::render_grid(getGrid());
            }
            if (ui::get_input(*this) == -2){
                pq_destroy(pq);
                return -2;
            }

        
            next_time = current_time + calculateTiming(pc.getSpeed());
        } else {
            // Check if the entity is alive, if not, skip
            if (!npcs[entity_id - 1].isAlive()) {
                pq_extract_min(pq);
                continue;
            }
            moveNPC(npcs[entity_id - 1]);
            next_time = current_time + calculateTiming(npcs[entity_id - 1].getSpeed());
        }
        
        // Reschedule entity's next turn
        pq_extract_min(pq);
        pq_insert(pq, entity_id, NULL, next_time);
    }

    ui::render_game_over(*this);
    pq_destroy(pq);

    return 1;
}

