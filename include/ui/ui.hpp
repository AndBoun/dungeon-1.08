//
// Created By Andrew Boun on 4/2/2025
//

#ifndef UI_HPP
#define UI_HPP

#include <dungeon/Dungeon.hpp>
#include <ncurses.h>

constexpr int COLOR_DEFAULT_ID = 1;
constexpr int COLOR_PLAYER_ID = 2;
constexpr int COLOR_STAIR_ID = 3;
constexpr int COLOR_SUCCESS_ID = 3;
constexpr int COLOR_MONSTER_ID = 4;
constexpr int COLOR_ERROR_ID = 5;
constexpr int COLOR_WARNING_ID = 6;

class ui {
    private:
        // Private member variables if needed
        static int handle_player_movement(Dungeon &d, int x, int y);
        static int print_monster_list(Dungeon &d, NPC alive[], int scroll);

    public:
        // Constructor and destructor
        ui() = delete;
        ~ui() = delete;
        
        // Initialize and destroy ncurses
        static void init_ncurses();
        static void destroy_ncurses();
        
        // Rendering methods
        static void render_top_bar(int color_id, const char *format, ...);
        static void render_grid(std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> grid);
        static void render_game_over(Dungeon &d);
        static bool teleport(Dungeon &d);
        
        // Input handling
        static int get_input(Dungeon &d);
        static int handle_monster_list(Dungeon &d);
};

#endif // NCURSES_UI_HPP