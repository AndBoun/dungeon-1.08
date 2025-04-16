//
// Created By Andrew Boun on 4/15/2025
//

#include <dungeon/Dungeon.hpp>

int Dungeon::getItemID(Point p) const {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->pos == p) {
            return i;
        }
    }
    return -1;
}

Item* Dungeon::pickRandomItem(){
    do {
        int randomIndex = rand() % itemDescList.size();
        int rrty = rand() % 100;

        ItemDescription itemDesc = itemDescList[randomIndex];

        if (itemDesc.rrty > rrty && itemDesc.canBeGenerated) {

            bool artifactExists = false;
            for (const auto& item : items) {
                if (item->art && item->descID == randomIndex) {
                    artifactExists = true;
                    break;
                }
            }
            if (artifactExists) {
                continue; // Skip this item if an artifact of the same type already exists
            }

            Item *item = ItemDescription::createItem(itemDescList[randomIndex], 0, randomIndex);
            return item;
        }
    } while (true);
    return nullptr;
}

bool Dungeon::placeItemsRandomly(int numItems){
    for (int i = 0; i < numItems; i++) {
        Item *item = pickRandomItem();
        item->ID = i;

        if (placeItemRandomly(item)) {
            items.push_back(item);
        }
    }
    return true;
}

bool Dungeon::placeItemRandomly(Item *item) {
    do {
        int x = rand() % PLACABLE_WIDTH + 1;
        int y = rand() % PLACABLE_HEIGHT + 1;
        
        // Don't allow stacking items
        if (grid[y][x].getType() == FLOOR && x > 0 && y > 0 && getItemID(Point(x, y)) == -1) {
            item->pos = Point(x, y);
            return true;
        }
    } while (true);
    return false; // Should never reach here
}