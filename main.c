#include <stdlib.h>
#include <ncurses.h>

/* Game constants */
#define PLAYER_CHAR "@"
#define WALL_CHAR "|"
#define FLOOR_CHAR "."

#define QUIT_CHAR "q"

typedef struct Player {
  int xPosition;
  int yPosition;
  int health;
} Player;

/* INTERFACES */

int screen_setup (void);
int map_setup (void);
Player *player_setup(void); 

int main (void) 
{
  /* game variables */ 
  Player *user;
  int ch;

  /* game setup */
  screen_setup();
  map_setup();
  user = player_setup();

  /* main game loop */
  while ((ch = getch()) != 'q') {
  
  }
  
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

/* initializes map */
int map_setup (void)
{    
  /* ncurses (x_position, y_postion, string to print) -- moves to x/y and prints string */
  mvprintw(13, 13, "--------");
  mvprintw(14, 13, "|......|");
  mvprintw(15, 13, "|......|");
  mvprintw(16, 13, "|......|");
  mvprintw(17, 13, "|......|");
  mvprintw(18, 13, "--------");

  mvprintw(2, 40, "--------");
  mvprintw(3, 40, "|......|");
  mvprintw(4, 40, "|......|");
  mvprintw(5, 40, "|......|");
  mvprintw(6, 40, "|......|");
  mvprintw(7, 40, "--------");

  mvprintw(10, 40, "------------");
  mvprintw(11, 40, "|..........|");
  mvprintw(12, 40, "|..........|");
  mvprintw(13, 40, "|..........|");
  mvprintw(14, 40, "|..........|");
  mvprintw(15, 40, "------------");

  return 0;
}

/* creates a new player object */
Player *player_setup (void)
{
  Player *newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
  newPlayer->health = 20;

  mvprintw(newPlayer->yPosition, newPlayer->xPosition, PLAYER_CHAR);

  /* move the cursor without printing */
  move(14, 14);

  return newPlayer;
}





























