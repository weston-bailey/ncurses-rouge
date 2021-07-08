#include <stdlib.h>
#include <ncurses.h>

/* Game constants */
#define CHAR_PLAYER "@"
#define CHAR_WALL_Y "-"
#define CHAR_WALL_X "|"
#define CHAR_FLOOR "."

#define KEY_QUIT 'q'

/* GAME OBEJECT TYPE DEFINITIONS */

typedef struct room Room;
typedef struct player Player;
typedef struct position Position;

struct position {
  int x;
  int y;
  // TILE_TYPE tile;
};

struct room {
  Position position;
  int height;
  int width;
  // Monster **monsters;
  // Item **items;
};

struct player {
  Position position;
  int health;
  Room *room;
};

/* INTERFACES */

int screen_setup (void);
Room **map_setup (void);
Player *player_setup (void);
int handle_input (int input, Player *user);
int player_move (int y, int x, Player *user);
int check_position(int newY, int newX, Player *user);

/* ROOM FUNCTIONS */
Room *create_room(int x, int y, int height, int width);
int draw_room(Room *room);

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
  while ((ch = getch()) != KEY_QUIT) {
    handle_input(ch, user); 
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
  /* printw("Hellow World"); */
  /* noecho prevents chars from kb input */
  noecho();
  /* you need to call refresh for some reason? -- TODO learn why */
  refresh();
  return 1;
}

/* returns an array of rooms to setup map */
Room **map_setup (void)
{    
  /* ncurses (x_position, y_postion, string to print) -- moves to x/y and prints string */
  /* array of rooms */
  Room **rooms;
  rooms = malloc(sizeof(Room*)*6);
  // mvprintw(13, 13, "--------");
  // mvprintw(14, 13, "|......|");
  // mvprintw(15, 13, "|......|");
  // mvprintw(16, 13, "|......|");
  // mvprintw(17, 13, "|......|");
  // mvprintw(18, 13, "--------");

  rooms[0] = create_room(13, 13, 6, 8);
  draw_room(rooms[0]);

  // mvprintw(2, 40, "--------");
  // mvprintw(3, 40, "|......|");
  // mvprintw(4, 40, "|......|");
  // mvprintw(5, 40, "|......|");
  // mvprintw(6, 40, "|......|");
  // mvprintw(7, 40, "--------");

  rooms[1] = create_room(40, 2, 6, 8);
  draw_room(rooms[1]);

  // mvprintw(10, 40, "------------");
  // mvprintw(11, 40, "|..........|");
  // mvprintw(12, 40, "|..........|");
  // mvprintw(13, 40, "|..........|");
  // mvprintw(14, 40, "|..........|");
  // mvprintw(15, 40, "------------");

  rooms[2] = create_room(40, 10, 6, 12);
  draw_room(rooms[2]);

  return rooms;
}


Room *create_room(int x, int y, int height, int width)
{
  /* declare a new room */
  Room *newRoom;
  newRoom = malloc(sizeof(Room));

  newRoom->position.x = x;
  newRoom->position.y = y;
  newRoom->height = height;
  newRoom->width = width;

  return newRoom;
}

int draw_room(Room *room)
{
  /* first draw top and bottom */
  int i;
  for (i = room->position.x; i < room->position.x + room->width; i++) {
    /* top of the room */
    mvprintw(room->position.y, i, CHAR_WALL_Y);
    /*bottom of the room */
    mvprintw(room->position.y + room->height - 1, i, CHAR_WALL_Y);
  }

  /* draw floors and side walls */
  int j; 
  int k;
  for (j = room->position.y + 1; j < room->position.y + room->height - 1; j++) { 
    /* draw side walls */
    mvprintw(j, room->position.x, CHAR_WALL_X);
    mvprintw(j, room->position.x + room->width - 1, CHAR_WALL_X);
    /* draw floors */
    for (k = room->position.x + 1; k < room->position.x + room->width - 1; k++) {
      mvprintw(j, k, CHAR_FLOOR);
    }
  }

  return 1;
}

/* creates a new player object */
Player *player_setup (void)
{
  Player *newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->position.x = 14;
  newPlayer->position.y = 14;
  newPlayer->health = 20;

  mvprintw(newPlayer->position.y, newPlayer->position.x, CHAR_PLAYER);

  /* move the cursor without printing */
  move(14, 14);

  return newPlayer;
}

int handle_input (int input, Player *user) 
{
  int newY;
  int newX;
  switch (input)
  {
    /* move up */
    case 'w':
    case 'W':
      newY = user->position.y - 1;
      newX = user->position.x;
      break;
    
    /* move down */
    case 's':
    case 'S':
      newY = user->position.y + 1;
      newX = user->position.x;
      break;

    /* move right */
    case 'a':
    case 'A':
      newY = user->position.y;
      newX = user->position.x - 1;
      break;

    /* move left */
    case 'd':
    case 'D':
      newY = user->position.y;
      newX = user->position.x + 1;
      break;

    default:
      break;
  }

  check_position(newY, newX, user);

  return 1;
}

/* check what is at the next position  where the user is trying to move */
int check_position (int newY, int newX, Player *user)
{
  /* the space the user is trying to move to */
  int space = mvinch(newY, newX);
  /* mvinch(y, x) returns the character at a specifc y x position */
  switch (mvinch(newY, newX))
  {
    case '.':
      player_move (newY, newX, user);
      break;
    default:
      move(user->position.y, user->position.x);
      break;
  }

  return 0;
}

int player_move (int y, int x, Player *user)
{
  mvprintw(user->position.y, user->position.x, CHAR_FLOOR);

  user->position.y = y;
  user->position.x = x;

  mvprintw(user->position.y, user->position.x, CHAR_PLAYER);
  return 1;
}

























