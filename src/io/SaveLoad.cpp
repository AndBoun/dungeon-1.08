//
// Created By Andrew Boun on 4/1/2025
//

#include <io/SaveLoad.hpp>
#include <iostream>

SaveLoad::SaveLoad() : f(nullptr)
{
    home = getenv("HOME");
    dungeonFile = home + "/.rlg327/dungeon";
    dungeonFileLength = dungeonFile.length();
}

SaveLoad::SaveLoad(std::string str) : f(nullptr)
{
    home = getenv("HOME");
    dungeonFile = home + "/.rlg327/" + str;
    dungeonFileLength = dungeonFile.length();
}

SaveLoad::~SaveLoad()
{
    if (f) {
        fclose(f);
    }
}