#ifndef GUI
#define GUI

#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../brick_game/tetris/tetris.h"
#include "database/big_inscriptions.h"

#define KEY_ESC 27
#define ENTER_KEY 10

enum MainWinMesures { wm_Hight = 24, wm_Width = 35, wm_y = 0, wm_x = 0 };
enum GameFieldMesures { gm_Hight = 22, gm_Width = 22, gm_y = 1, gm_x = 1 };
enum NextFieldMesure { nm_Hight = 6, nm_Width = 10, nm_y = 1, nm_x = 24 };
enum ScoreFieldMesure { sm_Hight = 3, sm_Width = 10, sm_y = 7, sm_x = 24 };
enum HighScoreFieldMesure { hm_Hight = 3, hm_Width = 10, hm_y = 10, hm_x = 24 };
enum LevelFieldMesure { lm_Hight = 3, lm_Width = 10, lm_y = 13, lm_x = 24 };

#define INPUT_ERROR -1

// main
int getGamerInput();
void ncursesINIT();
void theBigTetrisPrinter(GameInfo_t* game_info, WINDOW* win_main,
                         WINDOW* win_game, WINDOW* win_next, WINDOW* win_score,
                         WINDOW* win_high_score, WINDOW* win_level);

// big windows printing
void bigSymbolInscription(WINDOW* win_main, char which, char color);
void welcomeTetrisScreen(WINDOW* win_main);
void gameOverPrinter(WINDOW* win_main, GameInfo_t game_info);

// borders printing
void mainBorder(WINDOW* win_main);
void gameBorder(WINDOW* win_game);
void nextBorder(WINDOW* win_next);
void scoreBorder(WINDOW* win_score);
void highScoreBorder(WINDOW* win_high_score);
void levelBorder(WINDOW* win_level);

// game windows printing
void fullFieldPrinter(WINDOW* win_game, GameInfo_t game_info);
void fullNextPrinter(WINDOW* win_next, GameInfo_t game_info);
void fullScorePrinter(WINDOW* win_score, GameInfo_t game_info);
void fullHighScorePrinter(WINDOW* win_high_score, GameInfo_t game_info);
void fulllevelPrinter(WINDOW* win_level, GameInfo_t game_info);

// service functions
void untilEnter();
void noINFOprinter(WINDOW* window);

#endif