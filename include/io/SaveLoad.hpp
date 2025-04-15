//
// Created By Andrew Boun on 4/1/2025
//

#ifndef LOAD_SAVE_HPP
#define LOAD_SAVE_HPP

#include <string>
#include <dungeon/Dungeon.hpp>

#ifdef __linux__
#include <endian.h>
#endif

#ifdef __APPLE__
#include <machine/endian.h>
#include <libkern/OSByteOrder.h>
#define be16toh(x) OSSwapBigToHostInt16(x)
#define htobe16(x) OSSwapHostToBigInt16(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define htobe32(x) OSSwapHostToBigInt32(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define htobe64(x) OSSwapHostToBigInt64(x)
#define be8toh(x) (x)
#define htobe8(x) (x)
#endif

const std::string EXPECTED_MARKER = "RLG327-S2025";

class SaveLoad
{
protected:
    FILE *f;
    std::string home;
    std::string dungeonFile;
    int dungeonFileLength;

public:
    SaveLoad();
    SaveLoad(std::string str);
    ~SaveLoad();

    bool save(Dungeon &dungeon);
    bool load(Dungeon &dungeon);

private:
    int calculateSize(Dungeon &d);
    std::string loadMarker();
    uint32_t loadVersion();
    uint32_t loadSize();
    bool loadPC(Dungeon &d);
    bool loadHardness(Dungeon &d);
    int loadNumRooms(Dungeon &d);
    bool loadRooms(Dungeon& d, int numRooms);
    int loadNumUpStairs(Dungeon& d);
    bool loadUpStairs(Dungeon& d, int numUpStairs);
    int loadNumDownStairs(Dungeon& d);
    bool loadDownStairs(Dungeon& d, int numDownStairs);
    bool fillInCorridors(Dungeon& d);
};
#endif