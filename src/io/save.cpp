//
// Created By Andrew Boun on 4/1/2025
//

#include <io/SaveLoad.hpp>

int SaveLoad::calculateSize(Dungeon &d) {
    int size = 12 + 4 + 4 + 2 + 1680 
                + 2 + (d.getRooms().size() * 4) 
                + 2 + (d.getUpStairs().size() * 2) 
                + 2 + (d.getDownStairs().size() * 2);

    return size;
}

bool SaveLoad::save(Dungeon &d){

    f = fopen(dungeonFile.c_str(), "wb");

    // Write marker
    fwrite(EXPECTED_MARKER.c_str(), 1, 12, f);

    // Write version
    uint32_t version = 0;
    version = htobe32(version);
    fwrite(&version, sizeof(uint32_t), 1, f);

    // Write size
    uint32_t size = htobe32(calculateSize(d));
    fwrite(&size, 4, 1, f);

    // Write PC
    uint8_t pc_x = (uint8_t)d.getPC().getPosition().getX();
    uint8_t pc_y = (uint8_t)d.getPC().getPosition().getY();
    fwrite(&pc_x, 1, 1, f);
    fwrite(&pc_y, 1, 1, f);

    // Write hardness
    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            uint8_t hardness = (uint8_t)d.getGrid()[i][j].getHardness();
            fwrite(&hardness, 1, 1, f);
        }
    }

    // Write number of rooms
    uint16_t num_rooms = htobe16((uint16_t)d.getRooms().size());
    fwrite(&num_rooms, 2, 1, f);

    // Write rooms
    for (size_t i = 0; i < d.getRooms().size(); i++){
        uint8_t x = (uint8_t)d.getRooms()[i].getTopLeft().getX();
        uint8_t y = (uint8_t)d.getRooms()[i].getTopLeft().getY();
        uint8_t width = (uint8_t)d.getRooms()[i].getWidth();
        uint8_t height = (uint8_t)d.getRooms()[i].getHeight();
        fwrite(&x, sizeof(uint8_t), 1, f);
        fwrite(&y, sizeof(uint8_t), 1, f);
        fwrite(&width, sizeof(uint8_t), 1, f);
        fwrite(&height, sizeof(uint8_t), 1, f);
    }

    // Write number of up stairs
    uint16_t num_up = htobe16((uint16_t)d.getUpStairs().size());
    fwrite(&num_up, sizeof(uint16_t), 1, f);

    // Write up stairs
    for (size_t i = 0; i < d.getUpStairs().size(); i++){
        uint8_t x = (uint8_t)d.getUpStairs()[i].getX();
        uint8_t y = (uint8_t)d.getUpStairs()[i].getY();
        fwrite(&x, sizeof(uint8_t), 1, f);
        fwrite(&y, sizeof(uint8_t), 1, f);
    }

    // Write number of down stairs
    uint16_t num_down = htobe16((uint16_t)d.getDownStairs().size());
    fwrite(&num_down, sizeof(uint16_t), 1, f);

    // Write down stairs
    for (size_t i = 0; i < d.getDownStairs().size(); i++){
        uint8_t x = (uint8_t)d.getDownStairs()[i].getX();
        uint8_t y = (uint8_t)d.getDownStairs()[i].getY();
        fwrite(&x, sizeof(uint8_t), 1, f);
        fwrite(&y, sizeof(uint8_t), 1, f);
    }


    fclose(f);

    return true;
}