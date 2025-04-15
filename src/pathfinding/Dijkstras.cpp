//
// Created By Andrew Boun on 4/2/2025
//

#include <pathfinding/Dijkstras.hpp>
#include <cstdlib>
#include <cstring>

int Dijkstras:: coordToKey(int x, int y)
{
    return (y * DUNGEON_WIDTH) + x;
}

// Used for legacy priority queue
void* Dijkstras::copy_node_data(const void* data){
    NodeData* new_data = (NodeData*)malloc(sizeof(NodeData));
    memcpy(new_data, data, sizeof(NodeData));
    return new_data;
}

//Used for legacy priority queue
void Dijkstras::destroy_node_data(void* data){
    free(data);
}

void Dijkstras::initDistanceMap(std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &distanceMap)
{
    for (int y = 0; y < DUNGEON_HEIGHT; ++y)
    {
        for (int x = 0; x < DUNGEON_WIDTH; ++x)
        {
            distanceMap[y][x] = INF;
        }
    }
}

void Dijkstras::createDistanceMap(
    Dungeon &d,
    std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &distanceMap,
    int startX,
    int startY,
    bool tunneling
)
{
    initDistanceMap(distanceMap);

    int dx[] = {-1, -1, -1,  0, 0, 1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1,-1, 0, 1};
    int rows = DUNGEON_HEIGHT, cols = DUNGEON_WIDTH;
    PriorityQueue* pq = pq_create(rows * cols, rows * cols, copy_node_data, destroy_node_data);



    // Initialize start node
    NodeData start_data = {startX, startY};
    pq_insert(pq, coordToKey(startX, startY), &start_data, 0);
    distanceMap[startY][startX] = 0;

    
    while (!pq_is_empty(pq)) {
        NodeData* current = (NodeData*)pq_extract_min(pq);
        int curr_x = current->x, curr_y = current->y;
        
        for (int i = 0; i < 8; i++) {
            int next_x = curr_x + dx[i];
            int next_y = curr_y + dy[i];
            
            if (next_x >= 0 && next_x < cols &&
                next_y >= 0 && next_y < rows) {
                
                int curr_hardness = d.getGrid()[curr_y][curr_x].getHardness();
                int edge_cost = 0;
                
                // Check if movement is valid based on tunneling
                int neighbor_hardness = d.getGrid()[next_y][next_x].getHardness();
                
                if (!tunneling) {
                    if (neighbor_hardness != 0)
                        continue;
                    edge_cost = 1;
                } else {
                    if (neighbor_hardness == MAX_HARDNESS)
                        continue;
                    edge_cost = 1 + (curr_hardness / 85);
                }
                
                int new_dist = distanceMap[curr_y][curr_x] + edge_cost;
                if (new_dist < distanceMap[next_y][next_x]) {
                    distanceMap[next_y][next_x] = new_dist;
                    NodeData next_data = {next_x, next_y};
                    pq_insert(pq, coordToKey(next_x, next_y), &next_data, new_dist);
                }
            }
        }
        
        free(current);
    }

    
    pq_destroy(pq);
}