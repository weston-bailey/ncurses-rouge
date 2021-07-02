#include <stdio.h>
#include <ncurses.h>

/* interfaces */
int screen_setup ();

int main (void) 
{
  screen_setup ();
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
