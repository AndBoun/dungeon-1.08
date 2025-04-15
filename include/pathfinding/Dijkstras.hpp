//
// Created By Andrew Boun on 4/2/2025
//

#ifndef DIJKSTRAS_HPP
#define DIJKSTRAS_HPP

#include <dungeon/Dungeon.hpp>
#include <utils/priority_queue.h>

const int INF = 99999999;

// Helper struct to store node data, used for legacy priority queue
typedef struct {
    int x;
    int y;
} NodeData;

class Dijkstras
{
public:
    Dijkstras() = delete;
    ~Dijkstras() = delete;

    static void createDistanceMap(
        Dungeon &d,
        std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &distanceMap,
        int startX,
        int startY,
        bool tunneling
    );

private:
    static void* copy_node_data(const void* data);
    static void destroy_node_data(void* data);
    static int coordToKey(int x, int y);
    static void initDistanceMap(std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &distanceMap);
    
};

#endif