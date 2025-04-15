//
// Created by Andrew Boun on 3/24/25.
//

#include <ncurses.h>
#include <ui/ui.hpp>
#include <cstdlib>


int ui::handle_monster_list(Dungeon &d){

    // Create array with only alive monsters for easier scrolling
    int idx = 0;
    NPC alive [d.getNumMonsters()];
    for (size_t i = 0; i < d.getNPCs().size(); i++){
        if (d.getNPCs()[i].isAlive()) {
            alive[idx++] = d.getNPCs()[i];
        }
    }

    int input;
    int scroll = 0;
    do {
        print_monster_list(d, alive, scroll);

        timeout(-1);
        input = getch();

        switch (input) {
            case 'Q':
                destroy_ncurses();
                printf("Game terminated by user\n");
                exit(0);
                break;
                
            case KEY_DOWN: // Scroll down
                scroll = print_monster_list(d, alive, ++scroll);
                break;

            case KEY_UP: // Scroll up
                scroll = print_monster_list(d, alive, --scroll);
                break;

            default:
                break;
        }
    } while (input != 27 && input != 'm' && input != 'q'); // 27 is the ASCII value for ESC key

    clear();
    d.getFogStatus() ? render_grid(d, d.getFog(), true) : render_grid(d, d.getGrid());
    return 1;
}

// Prints monst list, symbol, and position relative to player
// return position of scroll
int ui::print_monster_list(Dungeon &d, NPC alive[], int scroll){
    clear();
    int j = 2; // current line to be printed at

    // Check if the scroll is out of bounds
    if (d.getNumMonsters() - scroll < 10) { scroll = d.getNumMonsters() - 10; }
    if (scroll < 0) { scroll = 0; }
    
    // Print the header
    mvprintw(1, 0, "Monster");
    mvprintw(1, 35, "X Distance");
    mvprintw(1, 70, "Y Distance");
    
    int c = 0; // counter number of lines, max of 10 lines

    for (int i = scroll; i < d.getNumMonsters() && c < 10; i++){

        mvprintw(j, 0, "%c", alive[i].getSymbol());

        int relative_x = alive[i].getPosition().getX() - d.getPC().getPosition().getX();
        int relative_y = alive[i].getPosition().getY() - d.getPC().getPosition().getY();

        
        if (relative_x < 0) {
            mvprintw(j, 35, "%d West", -relative_x);
        } else if (relative_x == 0) {
            mvprintw(j, 35, "Here");
        }
        else {
            mvprintw(j, 35, "%d East", relative_x);
        }

        if (relative_y < 0) {
            mvprintw(j, 70, "%d North", -relative_y);
        } else if (relative_y == 0) {
            mvprintw(j, 70, "Here");
        }
        else {
            mvprintw(j, 70, "%d South", relative_y);
        }
        
        c++; // increment line counter
        j++; // increment current line
    }

    refresh();
    return scroll;
}