#include <stdio.h>
#include <ncurses.h>

/* INTERFACES */
int screen_setup (void);
int map_setup (void);

int main (void) 
{

  screen_setup();
  map_setup();
  /* so you have to press a button to quit */
  getch();
  /* ends the ncurses session */
  endwin();
  return 0;
}

/* initialize the screen with ncurses */
int screen_setup (void)
{
  /* startup ncurses */
  initscr();
  /* ncurses uses printw() instead of printf() */
  printw("Hellow World");
  /* noecho prevents chars from kb input */
  noecho();
  /* you need to call refresh for some reason? -- TODO learn why */
  refresh();
  return 0;
}


int map_setup (void)
{    
  /* ncurses (x_position, y_postion, string to print) -- moves to x/y and prints string */
  mvprintw(13, 13, "--------");
  mvprintw(14, 13, "|......|");
  mvprintw(15, 13, "|......|");
  mvprintw(16, 13, "|......|");
  mvprintw(17, 13, "|......|");
  mvprintw(18, 13, "--------");
  return 0;
}
