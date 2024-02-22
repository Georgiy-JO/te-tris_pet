
#include "../tetris.h"

// (ノ ◑‿◑)ノ (I keep and work with the field that goes to GUI)
int** outputFieldKeeper(int command) {
  static int** field = NULL;
  int** output = NULL;
  switch (command) {
    case 0:
      if (outputFieldAllocationMaster(&field)) output = field;
      break;
    case 1:
      output = field;
      break;
    case 2:
      outputFieldFreeMaster(&field, HEIGHT);
      break;
    default:
      break;
  }
  return output;
}

// (ノ ◑‿◑)ノ (I allocate space for the field that goes to GUI)
GreatFlag_t outputFieldAllocationMaster(int*** field) {
  GreatFlag_t error_flag = SUCCESS;
  (*field) = (int**)calloc(HEIGHT, sizeof(int*));
  error_flag = ((*field) == NULL) ? FAILURE : SUCCESS;
  for (int i = 0; error_flag && i < HEIGHT; i++) {
    (*field)[i] = (int*)calloc(WIDTH, sizeof(int));
    if ((*field)[i] == NULL) {
      error_flag = FAILURE;
      outputFieldFreeMaster(field, i);
    }
  }
  return error_flag;
}

// (ノ ◑‿◑)ノ (I free space of the field that goes to GUI)
void outputFieldFreeMaster(int*** field, int hight) {
  if (field && (*field)) {
    for (int i = 0; i < hight; i++) {
      if ((*field)[i]) {
        free((*field)[i]);
        (*field)[i] = NULL;
      }
    }
    free((*field));
    (*field) = NULL;
  }
}

// (ノ ◑‿◑)ノ (I communicate user input between GUI in inside game functions)
void userInput(UserAction_t action, bool hold) {
  if (hold) {
    catchUpStructure();
    playerAction(structureKeeper(), action);
  }
}

// (ノ ◑‿◑)ノ (I translate inside structure of the game library to structure the
// GUI wants)
void structureTranslator(GameMain_t* core, GameInfo_t* info) {
  int** outputField = outputFieldKeeper(1);
  int hight_delta = FULL_HIGHT - HEIGHT;
  for (int i = hight_delta; i < FULL_HIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i >= core->piece.y && j >= core->piece.x &&
          i < (core->piece.y + PIECE_SIZE) && j < (core->piece.x + PIECE_SIZE))
        outputField[i - hight_delta][j] =
            core->field[i][j] +
            core->piece.shape[i - core->piece.y][j - core->piece.x];
      else
        outputField[i - hight_delta][j] = core->field[i][j];
    }
  }
  info->field = outputField;
  info->next = core->next_piece.shape;
  info->score = core->score;
  info->high_score = core->high_score;
  info->level = core->level;
  if (core->state == st_Pause)
    info->pause = 1;
  else
    info->pause = 0;
  info->speed = (double)(core->level) * 1.5;
}

// (ノ ◑‿◑)ノ (I organise  information in output structure for "Game over" case)
void gameOverScreen(GameInfo_t* info) {
  const GameMain_t* core = structureKeeper();
  info->next = NULL;
  info->score = core->score;
  info->high_score = core->high_score;
  info->level = core->level;
  info->pause = 0;
  info->speed = 1;
  info->field = NULL;
}

// (ノ ◑‿◑)ノ (I'm the main output function. I return the game state discribing
// structure)
GameInfo_t updateCurrentState() {
  static int first_start_flag = 0;
  GameMain_t* core = structureKeeper();
  GameInfo_t info = {.field = NULL};
  catchUpStructure();
  if (core->state == st_GameOver) {
    if (first_start_flag) gameOverScreen(&info);
  } else {
    if (!first_start_flag) {
      if (outputFieldKeeper(0)) first_start_flag++;
    }
    if (core->state == st_Exit)
      outputFieldKeeper(2);
    else if (first_start_flag >= 1)
      structureTranslator(core, &info);
  }

  return info;
}
