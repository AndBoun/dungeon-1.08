//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <pathfinding/Dijkstras.hpp>
#include <math.h>

int Dungeon:: getNPCID(int x, int y) const{
    for (size_t i = 0; i < npcs.size(); i++){
        if (npcs[i].getPosition().getX() == x && npcs[i].getPosition().getY() == y){
            return i;
        }
    }
    return -1;
}

bool Dungeon:: killNPC(int x, int y){
    int ID = getNPCID(x, y);
    if (ID == -1) return 0;

    modifyGrid()[y][x].setType(getNPCs()[ID].getCurrentCell().getType());
    npcs[ID].setPosition(Point(-1, -1));
    npcs[ID].setAlive(false);
    numMonsterAlive--;
    return 0;
}

bool Dungeon:: hasLineOfSight(int x, int y) {
    int pc_x = getPC().getPosition().getX();
    int pc_y = getPC().getPosition().getY();

    // Check if PC is within sight radius
    int sight_radius = 25;
    int dx = x - pc_x;
    int dy = y - pc_y;
    if (dx * dx + dy * dy > sight_radius * sight_radius)
    {
        return 0; // Target is out of sight radius
    }

    // Bresenham's Line Algorithm to check for walls and obstacles
    int abs_dx = abs(dx);
    int abs_dy = abs(dy);

    int sx = (dx > 0) ? 1 : -1;
    int sy = (dy > 0) ? 1 : -1;

    int err = abs_dx - abs_dy;
    int curr_x = pc_x;
    int curr_y = pc_y;

    // Trace the line from player to target
    while (curr_x != x || curr_y != y)
    {
        int e2 = 2 * err;

        if (e2 > -abs_dy)
        {
            err -= abs_dy;
            curr_x += sx;
        }

        if (e2 < abs_dx)
        {
            err += abs_dx;
            curr_y += sy;
        }

        // Check if we hit a wall before reaching the target
        // Skip the starting position (player's position)
        if ((curr_x != pc_x || curr_y != pc_y) && (curr_x != x || curr_y != y))
        {
            if (getGrid()[curr_y][curr_x].getHardness() != 0)
            {
                return 0; // Line of sight blocked by a wall
            }
        }
    }

    return 1; // Line of sight is clear
}

int Dungeon:: is_valid_move_non_tunnel(int x, int y){
    if (x < 1 || x >= DUNGEON_WIDTH - 1 || y < 1 || y >= DUNGEON_HEIGHT - 1) return 0;
    return getGrid()[y][x].getHardness() == 0;
}

int Dungeon:: is_valid_move_tunnel(int x, int y){
    if (x < 1 || x >= DUNGEON_WIDTH - 1 || y < 1 || y >= DUNGEON_HEIGHT - 1) return 0;
    return getGrid()[y][x].getHardness() != MAX_HARDNESS;
}

Point Dungeon:: get_next_random_move(int x, int y, int tunneling){
    Point p;
    Point valid_moves[8]; // Store valid adjacent coordinates
    int valid_count = 0;
    auto isValidMove = tunneling ? 
        &Dungeon::is_valid_move_tunnel : 
        &Dungeon::is_valid_move_non_tunnel;

    // Check all 8 adjacent cells
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            // Skip the cell itself (0,0)
            if (dx == 0 && dy == 0)
                continue;

            int new_x = x + dx;
            int new_y = y + dy;

            // If valid, add to our list of valid moves
            if ((this->*isValidMove)(new_x, new_y))
            {
                valid_moves[valid_count].setX(new_x);
                valid_moves[valid_count].setY(new_y);
                valid_count++;
            }
        }
    }

    // If we have valid moves, randomly select one
    if (valid_count > 0)
    {
        int choice = rand() % valid_count;
        p = valid_moves[choice];
    }
    else
    {
        // No valid moves, stay in place
        p.setPoint(x, y);
    }

    return p;
}

Point Dungeon:: get_next_intelligent_move(NPC &npc, int tunneling){
    const int INF = 99999999;

    int m_x = npc.getPosition().getX();
    int m_y = npc.getPosition().getY();
    int m_pc_x = npc.getPCPostion().getX();
    int m_pc_y = npc.getPCPostion().getY();

    int pc_x = getPC().getPosition().getX();
    int pc_y = getPC().getPosition().getY();

    // If the monster is already at the PC's position, return that position
    // If the monster doesn't know the PC's position, return its own position
    if ((m_pc_x == m_x && m_pc_y == m_y) ||
        (m_pc_x == -1 || m_pc_y == -1))
        return Point(m_x, m_y);

    // Recalculate the distance maps if using PC's remembered position
    if (m_pc_x != pc_x || m_pc_y != pc_y){
        Dijkstras::createDistanceMap(
            *this, 
            modifyNonTunnelingDistanceMap(),
            m_pc_x,
            m_pc_y, 
            false
        );
    
        Dijkstras::createDistanceMap(
            *this, 
            modifyTunnelingDistanceMap(),
            m_pc_x,
            m_pc_y,
            true
        );
    }


    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    Point p;
    p.setPoint(m_x, m_y);
    int min_dist = INF;
    for (int i = 0; i < 8; i++){

        int new_x = m_x + dx[i];
        int new_y = m_y + dy[i];

        // Check if the new position is within bounds
        if (new_x < 0 || new_x >= DUNGEON_WIDTH || new_y < 0 || new_y >= DUNGEON_HEIGHT)
            continue;

        if (tunneling){
            // Account for -1 being an invalid weight
            if (getTunnelingDistanceMap()[new_y][new_x] <= min_dist &&
                getTunnelingDistanceMap()[new_y][new_x] != -1){

                // Prevent tunneling through walls if there's an equivalent non-tunneling path
                // Select the first minimum distance
                if (grid[new_y][new_x].getHardness() == 0 &&
                    grid[p.getY()][p.getX()].getHardness() != 0
                ){
                    min_dist = getTunnelingDistanceMap()[new_y][new_x];
                    p.setPoint(new_x, new_y);
                }
                else if (getTunnelingDistanceMap()[new_y][new_x] < min_dist){
                    min_dist = getTunnelingDistanceMap()[new_y][new_x];
                    p.setPoint(new_x, new_y);
                }
            }
        }
        else
        {
            if (getNonTunnelingDistanceMap()[new_y][new_x] < min_dist){
                min_dist = getNonTunnelingDistanceMap()[new_y][new_x];
                p.setPoint(new_x, new_y);
            }
        }
    }

    // Recalculate the distance maps using PC's correct position
    // if it differes from the monster's remembered position
    if (m_pc_x != pc_x || m_pc_x != pc_y){
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
    }

    return p;
}

Point Dungeon:: get_next_unintelligent_move(NPC &npc, int tunneling){
    int m_x = npc.getPosition().getX();
    int m_y = npc.getPosition().getY();
    int m_pc_x = npc.getPCPostion().getX();
    int m_pc_y = npc.getPCPostion().getY();

    int pc_x = getPC().getPosition().getX();
    int pc_y = getPC().getPosition().getY();

    Point p;
    p.setPoint(m_x, m_y);



    // If the monster doesn't know the PC's position, move randomly
    if (m_pc_x == -1 || m_pc_y == -1)
        return get_next_random_move(m_x, m_y, tunneling);

    // Calculate the direction towards the PC
    int dx = (m_x < pc_x) ? 1 : (m_x > pc_x) ? -1
                                                     : 0;
    int dy = (m_y < pc_y) ? 1 : (m_y > pc_y) ? -1
                                                     : 0;

    // Choose movement validation function based on monster type
    auto isValidMove = tunneling ? 
        &Dungeon::is_valid_move_tunnel : 
        &Dungeon::is_valid_move_non_tunnel;

    // Try to move one step horizontaly or vertically of the PC
    // Never move diagonally
    if (dx != 0 && (this->*isValidMove)(m_x + dx, m_y)){
        p.setX(m_x + dx);
    }
    else if (dy != 0 && (this->*isValidMove)(m_x, m_y + dy)){
        p.setY(m_y + dy);
    }

    return p;
}

int Dungeon:: move_non_tunnel(NPC &npc, int new_x, int new_y){
    int m_x = npc.getPosition().getX();
    int m_y = npc.getPosition().getY();
    // int m_pc_x = npc.getPCPostion().getX();
    // int m_pc_y = npc.getPCPostion().getY();

    // int pc_x = getPC().getPosition().getX();
    // int pc_y = getPC().getPosition().getY();

    if (!is_valid_move_non_tunnel(new_x, new_y)) return 0;

    // Check if the new cell is occupied, and kill the occupant
    if (getGrid()[new_y][new_x].getType() != FLOOR &&
        getGrid()[new_y][new_x].getType() != CORRIDOR &&
        getGrid()[new_y][new_x].getType() != UP_STAIR &&
        getGrid()[new_y][new_x].getType() != DOWN_STAIR
    ){
        if (getGrid()[new_y][new_x].getType() == PLAYER){
            // kill player and return cell to original type
            // printf("Monster %c killed the player\n", m->symbol);
            getPC().setAlive(false);
            modifyGrid()[new_y][new_x].setType(getPC().getCurrentCell().getType());
        }
        else{
            // printf("Monster %c killed a monster %c\n", m->symbol, d->grid[new_y][new_x].type);
            killNPC(new_x, new_y);
        }
    }

    // printf("Monster %c moved from (%d, %d) to (%d, %d)\n", m->symbol, m->x, m->y, new_x, new_y);

    // d->grid[m->y][m->x].type = m->curr_cell;   // return the cell to its original type
    // m->curr_cell = d->grid[new_y][new_x].type; // update the current cell type to the new cell type
    // d->grid[new_y][new_x].type = m->symbol;    // update the new cell to the monster's symbol
    // m->x = new_x, m->y = new_y;                // update the monster's position

    modifyGrid()[m_y][m_x].setType(npc.getCurrentCell().getType()); // return the cell to its original type
    npc.setCurrentCell(getGrid()[new_y][new_x]); // update the current cell
    modifyGrid()[new_y][new_x].setType(npc.getSymbol()); // update the grid with the monster type
    npc.setPosition(Point(new_x, new_y)); // update the monster position

    return 0;
}

int Dungeon:: move_tunnel(NPC &npc, int new_x, int new_y){
    if (!is_valid_move_tunnel(new_x, new_y))
        return 0;

    // Burrow through the wall
    if (getGrid()[new_y][new_x].getHardness() <= 85 && getGrid()[new_y][new_x].getHardness() > 0)
    {
        // kill player, should only occur if player teleports into rock
        if (grid[new_y][new_x].getType() == PLAYER){
            getPC().setAlive(false);
        }

        modifyGrid()[new_y][new_x].setHardness(0);
        modifyGrid()[new_y][new_x].setType(CORRIDOR);

        // recalculate the distance maps
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
    }
    else if (getGrid()[new_y][new_x].getHardness() > 85)
    {
        int prev_hardness = getGrid()[new_y][new_x].getHardness();
        modifyGrid()[new_y][new_x].setHardness(prev_hardness - 85);
        // printf("Monster %c is attempting to break through a rock\n", m->symbol);
        return 0;
    }

    move_non_tunnel(npc, new_x, new_y);

    return 0;
}

bool Dungeon:: moveNPC(NPC &npc){
    int new_x, new_y;

    int intelligent = npc.getIntelligent(), telepathy = npc.getTelepathy();
    int tunneling = npc.getTunneling(), erratic = npc.getErratic();

    // Update monster's knowledge of PC position
    if (telepathy || hasLineOfSight(npc.getPosition().getX(), npc.getPosition().getY()))
    {
        // Monster can see the PC through telepathy or direct line of sight
        npc.setPCPosition(Point(getPC().getPosition().getX(), getPC().getPosition().getY()));
    }
    else if (!intelligent)
    {
        // Non-intelligent monsters forget PC position when out of sight
        npc.setPCPosition(Point(-1, -1));
    }


    if (erratic && rand() % 2 == 1)
    { // erratic random movement, 50% chance
        Point p = get_next_random_move(npc.getPosition().getX(), npc.getPosition().getY(), tunneling);
        new_x = p.getX();
        new_y = p.getY();
    }
    else
    {
        if (intelligent)
        { // intelligent movement towards PC if position is known, otherwise stay in place
            Point p = get_next_intelligent_move(npc, tunneling);
            new_x = p.getX();
            new_y = p.getY();
        }
        else
        { // unintelligent, linearly move towards PC, or randomly towards a valid cell if PC position is unknown
            Point p = get_next_unintelligent_move(npc, tunneling);
            new_x = p.getX();
            new_y = p.getY();
        }
    }

    // Check if the monster is trying to move to the same cell, if so, do nothing
    if (new_x == npc.getPosition().getX() && new_y == npc.getPosition().getY()){
        // printf("Monster %c is trying to move to the same cell (%d, %d)\n", m->symbol, new_x, new_y);
        return 0; // No movement
    }

    // printf("Monster %c moved from (%d, %d) to (%d, %d)\n", m->symbol, m->x, m->y, new_x, new_y);

    tunneling ? move_tunnel(npc, new_x, new_y) : move_non_tunnel(npc, new_x, new_y);

    return 0;
}