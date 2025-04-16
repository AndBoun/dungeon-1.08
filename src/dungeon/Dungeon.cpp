//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <utils/priority_queue.h>
#include <iostream>
#include <unistd.h>
#include <ui/ui.hpp>

Dungeon::Dungeon() {
    npcDescList = NPCDescription::NPCParser();
    itemDescList = ItemDescription::itemParser();
    numItems = rand() % 11 + 10; // Random number of items between 10 and 20
}

Dungeon::~Dungeon() {
    // Free npcs
    for (size_t i = 0; i < npcs.size(); i++){
        if (npcs[i] != nullptr) delete npcs[i];
        npcs[i] = nullptr;
    }
    // Free items
    for (size_t i = 0; i < items.size(); i++){
        if (items[i] != nullptr) delete items[i];
        items[i] = nullptr;
    }
}

void Dungeon::resetDungeon()
{
    // Free npcs
    for (size_t i = 0; i < npcs.size(); i++){
        if (npcs[i] != nullptr) delete npcs[i];
        npcs[i] = nullptr;
    }
    // Free items
    for (size_t i = 0; i < items.size(); i++){
        if (items[i] != nullptr) delete items[i];
        items[i] = nullptr;
    }

    // Clear rooms, stairs, and NPCs
    reset_fog_grid(); // Reset the fog grid
    rooms.clear();
    up_stairs.clear();
    down_stairs.clear();
    npcs.clear();
    items.clear();
    pc.items.clear(); // Clear the player's items
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
        // fog[pc.getPosition().getY()][pc.getPosition().getX()].setType(pc.getSymbol());
        break;
    } while (true);
}

int Dungeon::startGameplay(int numNPCS){
    
    placeNPCsRandomly(numNPCS); // Place NPCs randomly
    placeItemsRandomly(numItems); // Place items randomly
    ui::init_NPC_colors(npcs); // Initialize NPC colors
    ui::init_item_colors(items); // Initialize item colors

    numMonsterAlive = numNPCS; // Set the number of monsters alive
    int num_entities = getNPCs().size() + 1;

    // Create a priority queue for the entities
    // Only keys are needed, no data
    PriorityQueue *pq = pq_create(num_entities, num_entities, NULL, NULL);

    // Initialize the priority queue with the player and monsters
    // entity = (0) is the player, PLAYER_ID
    // entity = (i + 1), are the monsters, where i = index or monster_ID
    pq_insert(pq, PLAYER_ID, NULL, 0);
    for (size_t i = 0; i < getNPCs().size(); i++){
        pq_insert(pq, i + 1, NULL, 0); // all entities start at time 0
    }

    // render_grid(d); // Render the dungeon

    while (getPC().isAlive() && numMonsterAlive > 0) {

        int entity_id = pq_get_min_key(pq);
        int current_time = pq_get_priority(pq, entity_id);
        int next_time;


        if (entity_id == PLAYER_ID) { // Player's turn

            update_fog_grid(); // Update the fog of war
        
            if (getFogStatus()) {
                ui::render_grid((*this), getFog(), true); // Render the fog grid
            } else {
                ui::render_grid((*this), getGrid());
            }
            if (ui::get_input(*this) == -2){
                pq_destroy(pq);
                return -2;
            }

        
            next_time = current_time + calculateTiming(pc.getSpeed());
        } else {
            // Check if the entity is alive, if not, skip
            if (!npcs[entity_id - 1]->isAlive()) {
                pq_extract_min(pq);
                continue;
            }
            moveNPC(npcs[entity_id - 1]);
            next_time = current_time + calculateTiming(npcs[entity_id - 1]->getSpeed());
        }
        
        // Reschedule entity's next turn
        pq_extract_min(pq);
        pq_insert(pq, entity_id, NULL, next_time);
    }

    ui::render_game_over(*this);
    pq_destroy(pq);

    return 1;
}

