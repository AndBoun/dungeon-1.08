//
// Created By Andrew Boun on 4/2/2025
//


#include <ui/ui.hpp>
#include <cstdlib>


bool ui::teleport(Dungeon &d){
    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> grid_copy = d.getGrid();
    int result = 0;

    int x = d.getPC().getPosition().getX();
    int y = d.getPC().getPosition().getY();
    char prev = d.getGrid()[y][x].getType();

    render_top_bar(COLOR_PLAYER_ID, "In teleport mode, press 'g' to teleport, 'r' to randomize, or 'q' to quit");

    while (1) {
        prev = grid_copy[y][x].getType();
        grid_copy[y][x].setType('*');

        render_grid(d, grid_copy);

        grid_copy[y][x].setType(prev);

        timeout(-1);
        int input = getch();

        switch (input){
            case 'g':
                if (d.movePC(x, y, true) == 0){
                    result = 0;
                    render_top_bar(COLOR_ERROR_ID, "Invalid teleport location");
                } else {
                    result = 1;
                    render_top_bar(COLOR_SUCCESS_ID, "Teleported to (%d, %d)", x, y);
                }
                break;
                
            case 'r':
                do {
                    x = rand() % DUNGEON_WIDTH;
                    y = rand() % DUNGEON_HEIGHT;
                } while (d.getGrid()[y][x].getHardness() == MAX_HARDNESS);

                d.movePC(x, y, true);
                result = 1;
                render_top_bar(COLOR_SUCCESS_ID, "Teleported to (%d, %d)", x, y);
                result = 1;
                break;
            
            case 'h':
            case '4':
                x--;
                break;

            case 'j':
            case '2':
                y++;
                break;

            case 'k':
            case '8':
                y--;
                break;
                
            case 'l':
            case '6':
                x++;
                break;

            case 'y':
            case '7':
                x--;
                y--;
                break;

            case 'u':
            case '9':
                x++;
                y--;
                break;

            case 'b':  
            case '1':
                x--;
                y++;
                break;

            case 'n':
            case '3':
                x++;
                y++;
                break;
            
            case 'q':
                if (d.getFogStatus()) {
                    render_grid(d, d.getFog(), true /* fog is on */);
                } else {
                    render_grid(d, d.getGrid());
                }
                render_top_bar(COLOR_SUCCESS_ID, "Teleport cancelled");
                return false;
                break;

            case 'Q':
                destroy_ncurses();
                printf("Game terminated by user\n");
                exit(0);
                break;
        };
        if (x < 1) x = 1;
        if (x >= DUNGEON_WIDTH - 1) x = DUNGEON_WIDTH - 2;
        if (y < 1) y = 1;
        if (y >= DUNGEON_HEIGHT - 1) y = DUNGEON_HEIGHT - 2;

        if (result) break;
    }
    
    return true;
}