//
// Created By Andrew Boun on 4/15/2025
//


#include <item/ItemDescription.hpp>
#include <item/Item.hpp>
#include <character/NPCDescription.hpp>

Item *ItemDescription::createItem(ItemDescription &itemDesc, int ID, int descID){
    Item *item = new Item();

    item->pos = Point(0, 0); // Initialize position to (0, 0)

    auto it = validColorsMap.find(itemDesc.color);
    item->color = it->second;
    
    item->hit = itemDesc.dice_hit.getRandNum();
    item->dice_dam = itemDesc.dice_dam;
    item->dodge = itemDesc.dice_dodge.getRandNum();
    item->def = itemDesc.dice_def.getRandNum();
    item->weight = itemDesc.dice_weight.getRandNum();
    item->speed = itemDesc.dice_speed.getRandNum();
    item->attr = itemDesc.dice_attr.getRandNum();
    item->val = itemDesc.dice_val.getRandNum();
    item->art = itemDesc.art == "TRUE" ? true : false;
    item->rrty = itemDesc.rrty;

    item->ID = ID;
    item->descID = descID;

    if (itemDesc.type == "WEAPON") {
        item->symbol = '|';
    } else if (itemDesc.type == "OFFHAND") {
        item->symbol = ')';
    } else if (itemDesc.type == "RANGED") {
        item->symbol = '}';
    } else if (itemDesc.type == "ARMOR") {
        item->symbol = '[';
    } else if (itemDesc.type == "HELMET") {
        item->symbol = ']';
    } else if (itemDesc.type == "CLOAK") {
        item->symbol = '(';
    } else if (itemDesc.type == "GLOVES") {
        item->symbol = '{';
    } else if (itemDesc.type == "BOOTS") {
        item->symbol = '\\';  // note the escape character
    } else if (itemDesc.type == "RING") {
        item->symbol = '=';
    } else if (itemDesc.type == "AMULET") {
        item->symbol = '"';
    } else if (itemDesc.type == "LIGHT") {
        item->symbol = '_';
    } else if (itemDesc.type == "SCROLL") {
        item->symbol = '~';
    } else if (itemDesc.type == "BOOK") {
        item->symbol = '?';
    } else if (itemDesc.type == "FLASK") {
        item->symbol = '!';
    } else if (itemDesc.type == "GOLD") {
        item->symbol = '$';
    } else if (itemDesc.type == "AMMUNITION") {
        item->symbol = '/';
    } else if (itemDesc.type == "FOOD") {
        item->symbol = ',';
    } else if (itemDesc.type == "WAND") {
        item->symbol = '-';
    } else if (itemDesc.type == "CONTAINER") {
        item->symbol = '%';
    } else if (itemDesc.type == "STACK") {
        item->symbol = '&';
    } else {
        item->symbol = '*';  // Not a valid type (for debugging)
    }


    return item;
}