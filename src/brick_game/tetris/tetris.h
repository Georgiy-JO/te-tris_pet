#ifndef TETRIS_MAIN
#define TETRIS_MAIN

#include <stdio.h>
#include <stdlib.h>

#include "database/tetris_TSS.h"
#include "timer/timer.h"

#ifndef bool
#define bool _Bool
#endif

#define INPUT_ERROR -1

#define MAXTIME __LONG_MAX__

#define WIDTH 10
#define HEIGHT 20
#define FULL_HIGHT 23

#define PIECE_SIZE 4

// set this to 0 (zero) if you want to be able to rotate a piece just after
// force drop, before fixint it to the field.
#define GAME_MODE_SWITCH 1

enum PixelSt { EMPTY, TAKEN };
typedef enum { FAILURE, SUCCESS } GreatFlag_t;
typedef enum { st_Exit = -1, st_GameOver, st_Pause, st_GoingOn } GameState_t;

typedef struct __Tetrino_t {
  TetrinoType_t type;
  // TetrinoColor_t color;
  int x;
  int y;
  int** shape;
} Tetrino_t;

typedef struct __GameMain {
  int** field;
  Tetrino_t piece;
  Tetrino_t next_piece;
  long int score;
  GameState_t state;
  int level;
  long int high_score;
} GameMain_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct __GameInfo_t {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// mains
void gameStroke(GameMain_t* core);
GameMain_t* structureKeeper();

// tetrino
void copyTetrino(Tetrino_t* from, Tetrino_t* to);
void cleanTetrino(Tetrino_t* piece);
void setNextTetrino(GameMain_t* core);
void rotateTetrino(Tetrino_t* piece);

// Big service
GreatFlag_t ifCollide(const GameMain_t* core, const Tetrino_t* piece);
void fixToField(GameMain_t* core);
int lineEraser(GameMain_t* core);
void catchUpStructure();

// Little service
void lineEater(GameMain_t* core, int line_num);
void newTetrinoDrop(GameMain_t* core);
void setShape(const int* input, int*** shape);
void whenScoreChanges();
int highScoreKeeper(char choice);

// movements
void moveDown(Tetrino_t* piece);
void moveUp(Tetrino_t* piece);
void moveLeft(Tetrino_t* piece);
void moveRight(Tetrino_t* piece);

// Player
void playerAction(GameMain_t* core, UserAction_t action);
void pressLeft(GameMain_t* core);
void pressRight(GameMain_t* core);
void pressDown(GameMain_t* core);
void pressAction(GameMain_t* core);

// init-exit
GreatFlag_t initiateGame(GameMain_t* core);
void overGame(GameMain_t* core);

// allocate/free
GreatFlag_t fieldAllocationMaster(GameMain_t* core);
void fieldFreeMaster(GameMain_t* core, int lines);
GreatFlag_t shapeAllocationMaster(Tetrino_t* piece);
void shapeFreeMaster(Tetrino_t* piece, int lines);

// OUTPUT BLOCK--------------------------------------------

// output structure functions
void structureTranslator(GameMain_t* core, GameInfo_t* info);
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

// output structure service functions
int** outputFieldKeeper(int command);
GreatFlag_t outputFieldAllocationMaster(int*** field);
void outputFieldFreeMaster(int*** field, int hight);
void gameOverScreen(GameInfo_t* info);
//---------------------------------------------------------

#endif