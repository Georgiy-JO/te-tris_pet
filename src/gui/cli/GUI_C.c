#include "GUI_C.h"

int main() {
  ncursesINIT();
  WINDOW* win_main = newwin(wm_Hight, wm_Width, wm_y, wm_x);
  WINDOW* win_game = newwin(gm_Hight, gm_Width, gm_y, gm_x);
  WINDOW* win_next = newwin(nm_Hight, nm_Width, nm_y, nm_x);
  WINDOW* win_score = newwin(sm_Hight, sm_Width, sm_y, sm_x);
  WINDOW* win_high_score = newwin(hm_Hight, hm_Width, hm_y, hm_x);
  WINDOW* win_level = newwin(lm_Hight, lm_Width, lm_y, lm_x);
  refresh();

  welcomeTetrisScreen(win_main);
  untilEnter();

  srand(time(NULL));

  mainBorder(win_main);
  gameBorder(win_game);
  nextBorder(win_next);
  scoreBorder(win_score);
  highScoreBorder(win_high_score);
  levelBorder(win_level);

  userInput(Start, SUCCESS);

  clock_t time_fix = clock();
  GameInfo_t game_info = updateCurrentState();

  int input;
  int switch_on = 1;
  while (switch_on) {
    input = getGamerInput();
    if (input != INPUT_ERROR) {
      if (input == Terminate && game_info.field == NULL) {
        updateCurrentState();
        switch_on = 0;
      }
      theBigTetrisPrinter(&game_info, win_main, win_game, win_next, win_score,
                          win_high_score, win_level);
    }

    if (((clock() - time_fix) * game_info.speed) / CLOCKS_PER_SEC >= 1) {
      theBigTetrisPrinter(&game_info, win_main, win_game, win_next, win_score,
                          win_high_score, win_level);
      time_fix = clock();
    }
  }
  endwin();
  return 0;
}

// (ノ ◑‿◑)ノ (I'm the main during game printing function)
void theBigTetrisPrinter(GameInfo_t* game_info, WINDOW* win_main,
                         WINDOW* win_game, WINDOW* win_next, WINDOW* win_score,
                         WINDOW* win_high_score, WINDOW* win_level) {
  *game_info = updateCurrentState();
  if (game_info->field != NULL) {
    mainBorder(win_main);
    fullFieldPrinter(win_game, *game_info);
    fullNextPrinter(win_next, *game_info);
    fulllevelPrinter(win_level, *game_info);
    fullHighScorePrinter(win_high_score, *game_info);
    fullScorePrinter(win_score, *game_info);
  } else
    gameOverPrinter(win_main, *game_info);
}

// (ノ ◑‿◑)ノ (I print the "NoInfo" mesage)
void noINFOprinter(WINDOW* window) {
  int x, y = 0;
  getmaxyx(window, y, x);
  mvwprintw(window, y / 2, x / 2 - 3, "NoInfo");
}

// (ノ ◑‿◑)ノ (I print the main window borders)
void mainBorder(WINDOW* win_main) {
  wclear(win_main);
  box(win_main, 0, 0);
  wattron(win_main, A_BOLD);
  mvwprintw(win_main, 0, wm_Width / 2 - 2, "TETRIS");
  wattroff(win_main, A_BOLD);
  wrefresh(win_main);
}

// (ノ ◑‿◑)ノ (I print the game field window borders)
void gameBorder(WINDOW* win_game) {
  wclear(win_game);
  box(win_game, 0, 0);
  wrefresh(win_game);
}

// (ノ ◑‿◑)ノ (I print the next piece window borders)
void nextBorder(WINDOW* win_next) {
  wclear(win_next);
  box(win_next, 0, 0);
  mvwprintw(win_next, 0, nm_Width / 2 - 2, "Next");
  wrefresh(win_next);
}

// (ノ ◑‿◑)ノ (I print the score window borders)
void scoreBorder(WINDOW* win_score) {
  wclear(win_score);
  box(win_score, 0, 0);
  mvwprintw(win_score, 0, sm_Width / 2 - 3, "Score");
  wrefresh(win_score);
}

// (ノ ◑‿◑)ノ (I print the high score window borders)
void highScoreBorder(WINDOW* win_high_score) {
  wclear(win_high_score);
  box(win_high_score, 0, 0);
  mvwprintw(win_high_score, 0, hm_Width / 2 - 3, "Record");
  wrefresh(win_high_score);
}

// (ノ ◑‿◑)ノ (I print the level window borders)
void levelBorder(WINDOW* win_level) {
  wclear(win_level);
  box(win_level, 0, 0);
  mvwprintw(win_level, 0, lm_Width / 2 - 3, "Level");
  wrefresh(win_level);
}

// (ノ ◑‿◑)ノ (I print the whole  game field window)
void fullFieldPrinter(WINDOW* win_game, GameInfo_t game_info) {
  gameBorder(win_game);
  if (has_colors()) wattron(win_game, COLOR_PAIR(3));

  for (int i = 1; i < gm_Hight - 1; i++) {
    for (int j = 1; j < gm_Width - 1; j++) {
      if (game_info.field[i - 1][j - 1] == TAKEN) {
        mvwprintw(win_game, i, j * 2, " ");
        mvwprintw(win_game, i, j * 2 - 1, " ");
      }
    }
  }

  if (has_colors()) wattroff(win_game, COLOR_PAIR(3));

  wrefresh(win_game);
}

// (ノ ◑‿◑)ノ (I print the whole score window)
void fullScorePrinter(WINDOW* win_score, GameInfo_t game_info) {
  scoreBorder(win_score);
  if (game_info.score < 0)
    noINFOprinter(win_score);
  else
    mvwprintw(win_score, 1, 1, "%8d", game_info.score);
  wrefresh(win_score);
}

// (ノ ◑‿◑)ノ (I print the whole high score window)
void fullHighScorePrinter(WINDOW* win_high_score, GameInfo_t game_info) {
  highScoreBorder(win_high_score);
  if (game_info.high_score < 0)
    noINFOprinter(win_high_score);
  else
    mvwprintw(win_high_score, 1, 1, "%8d", game_info.high_score);
  wrefresh(win_high_score);
}

// (ノ ◑‿◑)ノ (I print the whole level window)
void fulllevelPrinter(WINDOW* win_level, GameInfo_t game_info) {
  levelBorder(win_level);
  if (game_info.level < 0)
    noINFOprinter(win_level);
  else
    mvwprintw(win_level, 1, lm_Width / 2, "%d", game_info.level);
  wrefresh(win_level);
}

// (ノ ◑‿◑)ノ (I print the whole next window)
void fullNextPrinter(WINDOW* win_next, GameInfo_t game_info) {
  nextBorder(win_next);
  if (game_info.next) {
    wattron(win_next, A_BOLD);
    if (has_colors()) {
      int color = rand() % 7 + 1;
      init_pair(4, color, color);
      wattron(win_next, COLOR_PAIR(4));
    }
    for (int i = 1; i < nm_Hight - 1; i++) {
      for (int j = 1; j < nm_Width - 1; j++) {
        if (game_info.next[i - 1][j - 1] == TAKEN) {
          mvwprintw(win_next, i, j * 2, " ");
          mvwprintw(win_next, i, j * 2 - 1, " ");
        }
      }
    }

    if (has_colors()) wattroff(win_next, COLOR_PAIR(4));
    wattroff(win_next, A_BOLD);
  } else {
    noINFOprinter(win_next);
  }
  wrefresh(win_next);
}

// (ノ ◑‿◑)ノ (I print the "GAME OVER" screen)
void gameOverPrinter(WINDOW* win_main, GameInfo_t game_info) {
  mainBorder(win_main);
  bigSymbolInscription(win_main, 2, 1);
  if (game_info.score >= 0 && game_info.level >= 0)
    mvwprintw(win_main, 15, wm_Width / 2 - 8, "Score: %d (level %d)",
              game_info.score, game_info.level);
  if (game_info.high_score >= 0)
    mvwprintw(win_main, 16, wm_Width / 2 - 8, "High Score: %d",
              game_info.high_score);
  wrefresh(win_main);
}

// (ノ ◑‿◑)ノ (I print the welcome screen)
void welcomeTetrisScreen(WINDOW* win_main) {
  mainBorder(win_main);
  bigSymbolInscription(win_main, 1, 1);

  mvwprintw(win_main, 10, wm_Width / 2 - 8, "Active buttons:");
  wattron(win_main, A_ITALIC);
  mvwprintw(win_main, 11, wm_Width / 2 - 10, "Arrow down - DROP");
  mvwprintw(win_main, 12, wm_Width / 2 - 10, "Arrow left - MOVE LEFT");
  mvwprintw(win_main, 13, wm_Width / 2 - 10, "Arrow right - MOVE RIGH");
  mvwprintw(win_main, 15, wm_Width / 2 - 10, "Enter - START");
  mvwprintw(win_main, 14, wm_Width / 2 - 10, "z - ACTION");
  mvwprintw(win_main, 16, wm_Width / 2 - 10, "q - TERMINATE/EXIT");
  mvwprintw(win_main, 14, wm_Width / 2 - 10, "p - PAUSE/UNPAUSE");
  wattroff(win_main, A_ITALIC);

  if (has_colors()) wattron(win_main, COLOR_PAIR(2));
  mvwprintw(win_main, wm_Hight - 3, wm_Width / 2 - 6, "PRESS ENTER");
  if (has_colors()) wattroff(win_main, COLOR_PAIR(2));

  wrefresh(win_main);
}

// (ノ ◑‿◑)ノ (I'm printing big symbol made notes (ex."TETRIS"))
void bigSymbolInscription(WINDOW* win_main, char which, char color) {
  int arr[wm_Hight][wm_Width];
  for (int i = 0; i < wm_Hight; i++) {
    for (int j = 0; j < wm_Width; j++) {
      arr[i][j] = 0;
    }
  }
  switch (which) {
    case 1:
      TETRIS_COORDINATES
      break;
    case 2:
      GAMEOVER_COORDINATES
      break;
    default:
      break;
  }

  wattron(win_main, A_BLINK);
  if (has_colors()) wattron(win_main, COLOR_PAIR(color));
  for (int i = 0; i < wm_Hight; i++) {
    for (int j = 0; j < wm_Width; j++) {
      if (arr[i][j] == 1) mvwprintw(win_main, i, j, "*");
    }
  }
  if (has_colors()) wattroff(win_main, COLOR_PAIR(color));
  wattroff(win_main, A_BLINK);
}

// (ノ ◑‿◑)ノ (I initiate ncurses settings for terminal)
void ncursesINIT() {
  initscr();

  nodelay(stdscr, TRUE);
  noecho();
  cbreak();
  raw();
  keypad(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  curs_set(0);

  if (has_colors()) {
    start_color();
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_CYAN);
  }
}

// (ノ ◑‿◑)ノ (I'm a simple function that wait for user to press "ENTER")
void untilEnter() {
  int input;
  while (1) {
    input = getch();
    if (input == ENTER_KEY || input == KEY_ENTER) break;
  }
}

// (ノ ◑‿◑)ノ (I get user input from keyboard and translate it into
// UserAction_t)
int getGamerInput() {
  int c = getch();
  UserAction_t output = 0;
  bool activness = SUCCESS;
  switch (c) {
    case KEY_UP:
      output = Up;
      break;
    case KEY_DOWN:
      output = Down;
      break;
    case KEY_LEFT:
      output = Left;
      break;
    case KEY_RIGHT:
      output = Right;
      break;
    case '/':
      output = Action;
      break;
    case 'z':
      output = Action;
      break;
    case KEY_ENTER:
      output = Start;
      break;
    case ENTER_KEY:
      output = Start;
      break;
    case 'q':
      output = Terminate;
      break;
    case KEY_ESC:
      output = Terminate;
      break;
    case 'p':
      output = Pause;
      break;
    default:
      activness = FAILURE;
      output = INPUT_ERROR;
      break;
  }
  userInput(output, activness);
  return output;
}
