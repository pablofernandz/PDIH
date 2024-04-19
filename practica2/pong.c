#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000


int main(int argc, char *argv[]) {
    
    int rows, cols;
    
    initscr();

    if (has_colors() == FALSE) {
        endwin();
        printf("El terminal no tiene soporte de color \n");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    clear();
    
    refresh();
    getmaxyx(stdscr, cols, rows);

    WINDOW *window = newwin(cols, rows, 0, 0);
    wbkgd(window, COLOR_PAIR(1));
    box(window, '|', '-');

    mvwprintw(window, 10, 10, "Juego realizado por Pablo Fernandez Tello");
    mvwprintw(window, 11, 10, "Jugador 1: teclas w y x");
    mvwprintw(window, 12, 10, "Jugador 2: teclas i y m");
    mvwprintw(window, 13, 10, "El juego terminara cuando alguno marque 5 goles o cuando se pulse la tecla 'F' ");
    wrefresh(window);

    getch();

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    
    int x = rows/2;
    int y = cols/2;
    int next_x = 0;
    int directionx = 1;
    int next_y = 0;
    int directiony = 1;
    int ch = 0;
    int goles_j1 = 0;
    int goles_j2 = 0;
    int xc = 0, yc = cols/2;
    int xd = rows - 1, yd = cols/2;
    bool game_over = false;
   

    while(!game_over) {
        clear();
        
        mvprintw(0, rows/3, "Goles J1: %d |  Goles J2: %d",goles_j1,goles_j2);
        mvprintw(y, x, "o");
        
        mvprintw(yc, xc,"|");
        mvprintw(yc + 1, xc,"|");
        mvprintw(yc + 2, xc,"|");
        mvprintw(yc + 3, xc,"|");
        mvprintw(yc + 4, xc,"|");
        mvprintw(yc + 5, xc,"|");
        
        mvprintw(yd, xd,"|");
        mvprintw(yd + 1, xd,"|");
        mvprintw(yd + 2, xd,"|");
        mvprintw(yd + 3, xd,"|");
        mvprintw(yd + 4, xd,"|");
        mvprintw(yd + 5, xd,"|");
        
        refresh();
        

        ch = getch();
        if (ch == 'w' && yc > 0)
            yc -= 1;
        else if (ch == 'x' && yc+6 < cols) 
            yc += 1;
        else if (ch == 'i' && yd > 0) 
            yd -= 1;
        else if (ch == 'm' && yd+6 < cols) 
            yd += 1;
        else if (ch == 'f')
            game_over = true;

        usleep(DELAY);

        next_x = x + directionx;
        next_y = y + directiony;

        if (next_x >= rows || next_x < 0) {
            directionx *= -1;
        } else {
            x += directionx;
        }

        if (next_y >= cols || next_y < 0) {
            directiony *= -1;
        } else {
            y += directiony;
        }
        
  
   	if (next_x == xc + 1 && next_y >= yc && next_y <= yc + 5) {
      	    directionx *= -1;
    	}
    
        if (next_x == xd - 1 && next_y >= yd && next_y <= yd + 5) {
            directionx *= -1;
        }
    
    
        if (next_x > xd){
            next_x = rows/2;
            next_y = cols/2;
            x = rows/2;
            y = cols/2;
            goles_j1++;
        } 
        else if (next_x < xc){
            next_x = rows/2;
            next_y = cols/2;
            x = rows/2;
            y = cols/2;
            goles_j2++;
        }
        
        if (goles_j1 >= 5 || goles_j2 >= 5)
            game_over = true;
            
        if (game_over) {
            clear();
	    refresh();
	    WINDOW *win_resultados = newwin(cols, rows, 0, 0);
	    wbkgd(win_resultados, COLOR_PAIR(2));
	    box(win_resultados, '|', '-');
	    mvwprintw(win_resultados, 1, 10, "RESULTADOS");
	    mvwprintw(win_resultados, 2, 5, "Jugador 1: %d goles", goles_j1);
	    mvwprintw(win_resultados, 3, 5, "Jugador 2: %d goles", goles_j2);
	    mvwprintw(win_resultados, 4, 5, "¿Quieres volver a jugar? (S/N)");
	    wrefresh(win_resultados);
	    
            int respuesta;
            do {
                respuesta = getch();
            } while (respuesta != 's' && respuesta != 'n');
            
            if (respuesta == 's') {
                goles_j1 = 0;
                goles_j2 = 0;
                game_over = false;
            } else {
                endwin();
                break;
            }
        }
    }
}
