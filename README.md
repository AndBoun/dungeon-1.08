# How To Run The Project:

 Create a `.rlg327` folder in your home directory and move the `monster_desc.txt` and `object_desc.txt` file into it:
```bash
mkdir ~/.rlg327
```

> Files within the `.rlg327` folder are provided from Iowa State University's professor, Jeremy Scheaffer

Build the project:
```bash
make
```

Alternatively, use the `.devcontainer` folder to automatically build a development environment in VS Code or GitHub Codespaces. The container configuration
will automatically copy the `.rlg327` folder into the home directory and build the project. The environment uses a Docker image of the latest stable version of Fedora and installs gcc/g++ and gdb for developing. The environment is meant to emulate Iowa State University's Pyrite server environment.

## Running configurations
Run the project:
```bash
./dungeon --load --save --nummon <number>
```


# Main Files:
```plain
/
├── include/
├── character/
│   ├── NPC.hpp
│   └── NPCDescription.hpp
├── item/
│   ├── Item.hpp
│   └── ItemDescription.hpp
├── src/
├── character/
│   └── NPCFactory.cpp
├── dungeon/
│   ├── DungeonCharacterPlacement.cpp
│   └── DungeonItemPlacement.cpp
├── item/
│   ├── ItemFactory.cpp
│   └── ItemInteractions.cpp
└── main.cpp
```

# About the Project:

## Constraints:
- All files and inputs are assumed to be valid

## Additional Notes
- No optional features were added for 1.08
- Item pickup only works for the player. Move over items to pick them up.
- Item and monsters are deleted and regenerated after each level change / stair
	- Players don't keep their inventory after using stairs
- The destructor in the classes cleans up dynamically allocated objects
	- `reset_dungeon()` cleans up dynamically allocated objects explicitly, but doesn't reset everything to prepare to generate a new dungeon. It respects the current ineligible list of objects and monsters.

## How the Project Runs:
In `main.cpp`, it creates a dungeon instance, which will set up a description list and generate a random number for the amount of items in a dungeon. Next, it uses `start_gameplay()`. Within `start_gameplay()`, we set up and place NPCs and items around the dungeon with `placeNPCsRandomly()` and `placeItemsRandomly()`. These use the factories (`ItemFactory.cpp` and `NPCFactory.cpp`) to generate their respective objects, then randomly place them within the dungeon (with `DungeonCharacterPlacement.cpp` and `DungeonItemPlacement.cpp`). These keep track of which items can and can't be placed, and if an identical unique NPC or item artifact has already been placed.  When stairs are used, the `reset_dungeon()` method is called to free up allocated space, but it leaves the description lists alone to ensure generation specifications are kept. When the dungeon is destroyed, the allocated space is automatically freed in the deconstructor of `Dungeon.cpp`.


# Example Gameplay:
![Gameplay-1 08](https://github.com/user-attachments/assets/896063c8-cc16-4f01-b569-7ebb3150630e)
