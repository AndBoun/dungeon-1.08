//
// Created by Andrew Boun on 3/24/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <ui/ui.hpp>

// #define COLOR_DEFAULT_ID 1
// #define COLOR_PLAYER_ID 2
// #define COLOR_STAIR_ID 3
// #define COLOR_SUCCESS_ID 3
// #define COLOR_MONSTER_ID 4
// #define COLOR_ERROR_ID 5
// #define COLOR_WARNING_ID 6


void ui::init_ncurses() {
    initscr();
    raw();                 // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special keys
    noecho();              // Don't echo input characters
    curs_set(0);           // Hide cursor
    start_color();         // Enable colors
    use_default_colors();  // Use default colors
    timeout(0);            // Non-blocking input

    init_pair(COLOR_DEFAULT_ID, COLOR_WHITE, -1);           // Default
    init_pair(COLOR_PLAYER_ID, COLOR_WHITE, COLOR_YELLOW);  // Player
    init_pair(COLOR_STAIR_ID, COLOR_GREEN, -1);             // Stairs and Success
    init_pair(COLOR_MONSTER_ID, COLOR_CYAN, COLOR_RED);     // Monster
    init_pair(COLOR_ERROR_ID, COLOR_RED, -1);               // ERROR
    init_pair(COLOR_WARNING_ID, COLOR_YELLOW, -1);          // Warning
}

void ui::destroy_ncurses() {
    endwin();
}

void ui::render_top_bar(int color_id, const char *format, ...) {
    char message[100];
    va_list args;
    
    // Format the string with the variable arguments
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // Clear the top bar
    move(0, 0);
    clrtoeol();
    
    // Set color and print message
    attron(COLOR_PAIR(color_id));
    mvprintw(0, (DUNGEON_WIDTH - strlen(message)) / 2, "%s", message);
    attroff(COLOR_PAIR(color_id));
    
    refresh();
}

void ui::render_grid(const Dungeon &d, const std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &grid, bool is_fog_on) {

    // Get player position and radius
    int pc_x = d.pc.getPosition().getX();
    int pc_y = d.pc.getPosition().getY();

    int start_x = std::max(0, pc_x - 2);
    int end_x = std::min(DUNGEON_WIDTH - 1, pc_x + 2);

    int start_y = std::max(0, pc_y - 2);
    int end_y = std::min(DUNGEON_HEIGHT - 1, pc_y + 2);

    // Draw the dungeon grid with colors based on cell type
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            char cell_type = grid[y][x].getType();
            Point current_point = Point(x, y);
            attron(COLOR_PAIR(COLOR_DEFAULT_ID)); 
            

            if (d.isUpStair(current_point) || d.isDownStair(current_point)) {
                attron(COLOR_PAIR(COLOR_STAIR_ID));
            }

            if ( // only render player and monsters in radius if fog is on
                !is_fog_on || (
                    (x >= start_x && x <= end_x) &&
                    (y >= start_y && y <= end_y)
                )
            ){
                if (current_point == d.pc.getPosition()){
                    attron(COLOR_PAIR(COLOR_PLAYER_ID));
                    cell_type = (cell_type == '*') ? '*' : d.pc.getSymbol();
                }
                else if (d.getNPCID(current_point) != -1) {
                    attron(COLOR_PAIR(COLOR_MONSTER_ID));
                    cell_type = (cell_type == '*') ? '*' : d.npcs[d.getNPCID(current_point)].getSymbol();
                }
            }
            
            mvaddch(y + 1, x, cell_type);
        }
    }

    refresh();
}

// Render game over message
void ui::render_game_over(Dungeon &d) {
    clear();
    
    render_grid(d, d.getGrid()); // Render the grid without fog
    
    if (!d.getPC().isAlive()) {
        render_top_bar(COLOR_ERROR_ID, "Player Died, press 'q' to quit");
    } else if (d.getNumMonsters() == 0) {
        render_top_bar(COLOR_SUCCESS_ID, "All Monsters are Dead, press 'q' to quit");
    }
    
    
    // Render top bar handles rerendering, so we don't need to call it again

    int input;
    do {
        timeout(-1);
        input = getch();
    } while (input != 'q' && input != 'Q');
}

int ui::get_input(Dungeon &d) {
    while (1) {
        timeout(-1);
        int input = getch();
        int result = 0;
        
        
        // Process directional keys
        switch (input) {
            case '7': // move up-left
            case 'y':
                result = handle_player_movement(d, d.getPC().getPosition().getX() - 1, d.getPC().getPosition().getY() - 1);
                break;
                
            case '8': // move up
            case 'k':
                result = handle_player_movement(d,d.getPC().getPosition().getX(), d.getPC().getPosition().getY() - 1);
                break;
                
            case '9': // move up-right
            case 'u':
                result = handle_player_movement(d,d.getPC().getPosition().getX() + 1, d.getPC().getPosition().getY() - 1);
                break;
                
            case '6': // move right
            case 'l':
                result = handle_player_movement(d,d.getPC().getPosition().getX() + 1, d.getPC().getPosition().getY());
                break;
                
            case '3': // move down-right
            case 'n':
                result = handle_player_movement(d,d.getPC().getPosition().getX() + 1, d.getPC().getPosition().getY() + 1);
                break;
                
            case '2': // move down
            case 'j':
                result = handle_player_movement(d,d.getPC().getPosition().getX(), d.getPC().getPosition().getY() + 1);
                break;
                
            case '1': // move down-left
            case 'b':
                result = handle_player_movement(d,d.getPC().getPosition().getX() - 1, d.getPC().getPosition().getY() + 1);
                break;
                
            case '4': // move left
            case 'h':
                result = handle_player_movement(d,d.getPC().getPosition().getX() - 1, d.getPC().getPosition().getY());
                break;
            
            case '5':
            case '.':
            case ' ': 
                render_top_bar(COLOR_WARNING_ID, "Player Skipped Their Turn");
                return 1; // Skip turn
                
            case '<': // Up stairs
                result = handle_player_movement(d, -2, -2); // -2 for up stairs
                break;
                
            case '>': // Down stairs
                result = handle_player_movement(d, -3, -3); // -3 for down stairs
                break;
            
            case 'f':
                d.setFogStatus(!d.getFogStatus());
                if (d.getFogStatus()) {
                    render_top_bar(COLOR_SUCCESS_ID, "Fog of War Enabled");
                    render_grid(d, d.getFog(), true); // fog is on
                } else {
                    render_top_bar(COLOR_SUCCESS_ID, "Fog of War Disabled");
                    render_grid(d, d.getGrid()); // fog is off
                }
                continue;
            
            case 'g':
                // if (teleport(d)) result = 1;
                teleport(d);
                if (d.getNumMonsters() == 0) result = 1; // all monsters dead, stop game by returning
                if (d.getFogStatus()) {
                    render_grid(d, d.getFog(), true); // fog is on
                } else {
                    render_grid(d, d.getGrid()); // fog is off
                }
                break;


            case 'q':
                render_top_bar(COLOR_ERROR_ID, "Press 'shift + q' to quit");
                break;
                
            case 'Q':
                destroy_ncurses();
                printf("Game terminated by user\n");
                exit(0);
                break;
            
            case 'm': // Monster list
                result = 0; // no movement, run loop again
                handle_monster_list(d);
                break;
                
            default:
                render_top_bar(COLOR_ERROR_ID, "Invalid Input");
                continue; // Get input again
        }
        
        // Process the result from movement
        if (result == MOVEMENT_STAIRS) return MOVEMENT_STAIRS;
        if (result == 1) return 1;
    }
}

int ui::handle_player_movement(Dungeon &d, int x, int y) {

    // Avoid \t to keep centering of top bar message
    render_top_bar(
        COLOR_DEFAULT_ID,
        "Player Previously at: (%d, %d)          Player Currently At: (%d, %d)",
        d.getPC().getPosition().getX(), d.getPC().getPosition().getY(), x, y
    );

    int move_result = d.movePC(x, y);
    
    if (move_result == 0) { // invalid move
        render_top_bar(COLOR_ERROR_ID, "Invalid Player Movement, Try Again");
        return 0;  // Return invalid movement code
    } else if (move_result == MOVEMENT_STAIRS) {
        render_top_bar(COLOR_STAIR_ID, "Player uses stairs");
        return MOVEMENT_STAIRS; // Return stairs code
    }

    return 1; // Return successful movement
}
