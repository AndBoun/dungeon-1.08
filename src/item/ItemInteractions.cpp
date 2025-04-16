//
// Created By Andrew Boun on 4/16/2025
//

#include <dungeon/Dungeon.hpp>
#include <ui/ui.hpp>

bool Dungeon::pickUpItem(Character &character){

    int itemID = getItemID(character.getPosition());

    if (itemID == -1) {
        return false; // No item at the character's position
    }

    character.items.push_back(items[itemID]);
    items[itemID]->pos = Point(-1, -1); // Remove item from the dungeon

    if (items[itemID]->art) {
        itemDescList[items[itemID]->descID].canBeGenerated = false;
    }

    ui::render_top_bar(
        COLOR_SUCCESS_ID,
        "Picked up a %s: %c",
        items[itemID]->type.c_str(),
        items[itemID]->symbol
    );

    return true;
}