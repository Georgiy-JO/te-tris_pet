#include "tetris.h"

// (ノ ◑‿◑)ノ (I calculate a movement in game stroke)
void gameStroke(GameMain_t* core) {
  moveDown(&(core->piece));
  if (ifCollide(core, &(core->piece))) {
    moveUp(&(core->piece));
    fixToField(core);
    core->score += lineEraser(core);
    whenScoreChanges();
    newTetrinoDrop(core);
    if (ifCollide(core, &(core->piece))) overGame(core);
  }
}

// (ノ ◑‿◑)ノ (I'm the one that kill the game)
void overGame(GameMain_t* core) {
  core->state = st_GameOver;
  highScoreKeeper(1);
  fieldFreeMaster(core, FULL_HIGHT);
  shapeFreeMaster(&(core->piece), PIECE_SIZE);
  shapeFreeMaster(&(core->next_piece), PIECE_SIZE);
}

// (ノ ◑‿◑)ノ (I copy terino from one to another)
void copyTetrino(Tetrino_t* from, Tetrino_t* to) {
  to->type = from->type;
  to->x = from->x;
  to->y = from->y;
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      to->shape[i][j] = from->shape[i][j];
    }
  }
}

// (ノ ◑‿◑)ノ (I make a tetrino move down)
void moveDown(Tetrino_t* piece) { piece->y++; }

// (ノ ◑‿◑)ノ (I make a tetrino move up)
void moveUp(Tetrino_t* piece) { piece->y--; }

// (ノ ◑‿◑)ノ (I make a tetrino move left)
void moveLeft(Tetrino_t* piece) { piece->x--; }

// (ノ ◑‿◑)ノ (I make a tetrino move right)
void moveRight(Tetrino_t* piece) { piece->x++; }

// (ノ ◑‿◑)ノ (I check if collision took place due to down/right/left movement)
GreatFlag_t ifCollide(const GameMain_t* core, const Tetrino_t* piece) {
  GreatFlag_t flag_collide = FAILURE;
  for (int i = piece->y; i < PIECE_SIZE + piece->y && !flag_collide; i++) {
    for (int j = piece->x; j < PIECE_SIZE + piece->x && !flag_collide; j++) {
      if (piece->shape[i - (piece->y)][j - (piece->x)] == TAKEN &&
          (j < 0 || j >= WIDTH || i >= FULL_HIGHT ||
           core->field[i][j] == TAKEN))
        flag_collide = SUCCESS;
    }
  }
  return flag_collide;
}

// (ノ ◑‿◑)ノ (I fix thetetrino to the field)
void fixToField(GameMain_t* core) {
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      if (core->piece.shape[i][j] == TAKEN)
        core->field[i + (core->piece.y)][j + (core->piece.x)] = TAKEN;
    }
  }
  cleanTetrino(&(core->piece));
}

// (ノ ◑‿◑)ノ (I clean the tetrino)
void cleanTetrino(Tetrino_t* piece) {
  piece->type = tt_None;
  piece->x = 0;
  piece->y = 0;
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      piece->shape[i][j] = EMPTY;
    }
  }
}

// (ノ ◑‿◑)ノ (I remove lines and count pionts for it )
int lineEraser(GameMain_t* core) {
  int points = 0;
  for (int i = FULL_HIGHT - 1; i >= FULL_HIGHT - HEIGHT; i--) {
    for (int j = 0; j < WIDTH && core->field[i][j]; j++) {
      if (j == WIDTH - 1 && core->field[i][j] == TAKEN) {
        points++;
        lineEater(core, i);
        i++;
      }
    }
  }
  switch (points) {
    case 1:
      points = pt_One;
      break;
    case 2:
      points = pt_Two;
      break;
    case 3:
      points = pt_Three;
      break;
    case 4:
      points = pt_Four;
      break;
    default:
      break;
  }
  return points;
}

// (ノ ◑‿◑)ノ (I just remove lines)
void lineEater(GameMain_t* core, int line_num) {
  for (int i = line_num; i > 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      core->field[i][j] = core->field[i - 1][j];
    }
  }
}

// (ノ ◑‿◑)ノ (I drop a new tetrino from core->next_piece and set new
// core->next_piece)
void newTetrinoDrop(GameMain_t* core) {
  copyTetrino(&(core->next_piece), &(core->piece));
  core->piece.x = WIDTH / 2 - 2;
  core->piece.y = 0;
  cleanTetrino(&(core->next_piece));
  setNextTetrino(core);
}

// (ノ ◑‿◑)ノ  (I set new next tetrino)
void setNextTetrino(GameMain_t* core) {
  core->next_piece.type = rand() % 7;
  core->next_piece.x = 0;
  core->next_piece.y = 0;

  switch (core->next_piece.type) {
    case 0:
      const int piece_0[PIECE_SIZE * PIECE_SIZE] = INIT_LINE;
      setShape(piece_0, &(core->next_piece.shape));
      break;
    case 1:
      const int piece_1[PIECE_SIZE * PIECE_SIZE] = INIT_SQUARE;
      setShape(piece_1, &(core->next_piece.shape));
      break;
    case 2:
      const int piece_2[PIECE_SIZE * PIECE_SIZE] = INIT_LEFT_L;
      setShape(piece_2, &(core->next_piece.shape));
      break;
    case 3:
      const int piece_3[PIECE_SIZE * PIECE_SIZE] = INIT_RIGHT_L;
      setShape(piece_3, &(core->next_piece.shape));
      break;
    case 4:
      const int piece_4[PIECE_SIZE * PIECE_SIZE] = INIT_LEFT_SNAKE;
      setShape(piece_4, &(core->next_piece.shape));
      break;
    case 5:
      const int piece_5[PIECE_SIZE * PIECE_SIZE] = INIT_RIGHT_SNAKE;
      setShape(piece_5, &(core->next_piece.shape));
      break;
    case 6:
      const int piece_6[PIECE_SIZE * PIECE_SIZE] = INIT_T;
      setShape(piece_6, &(core->next_piece.shape));
      break;
    default:
      break;
  }
}

// (ノ ◑‿◑)ノ (I set piece.sape from array. I'm a part of "setNextTetrino")
void setShape(const int* input, int*** shape) {
  for (int i = 0, k = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++, k++) {
      (*shape)[i][j] = input[k];
    }
  }
}

// (ノ ◑‿◑)ノ  (I work with palayer's actions)
void playerAction(GameMain_t* core, UserAction_t action) {
  switch (action) {
    case Start:
      if (core->state == st_GameOver) initiateGame(core);
      break;
    case Pause:
      pauseTimer();
      if (core->state == st_Pause)
        core->state = st_GoingOn;
      else if (core->state == st_GoingOn)
        core->state = st_Pause;
      break;
    case Terminate:
      if (core->state == st_GoingOn || core->state == st_Pause)
        overGame(core);
      else if (core->state == st_GameOver)
        core->state = st_Exit;
      break;
    case Left:
      if (core->state == st_GoingOn) pressLeft(core);
      break;
    case Right:
      if (core->state == st_GoingOn) pressRight(core);
      break;
    case Down:
      if (core->state == st_GoingOn) pressDown(core);
      break;
    case Action:
      if (core->state == st_GoingOn) pressAction(core);
      break;
    default:
      break;
  }
}

// (ノ ◑‿◑)ノ  (I'm part of thr "playerAction" function - for pres:left);
void pressLeft(GameMain_t* core) {
  moveLeft(&(core->piece));
  if (ifCollide(core, &(core->piece))) moveRight(&(core->piece));
}

// (ノ ◑‿◑)ノ  (I'm part of thr "playerAction" function - for pres:right);
void pressRight(GameMain_t* core) {
  moveRight(&(core->piece));
  if (ifCollide(core, &(core->piece))) moveLeft(&(core->piece));
}

// (ノ ◑‿◑)ノ  (I'm part of thr "playerAction" function - for pres:down);
void pressDown(GameMain_t* core) {
  while (!ifCollide(core, &(core->piece))) {
    moveDown(&(core->piece));
  }
  moveUp(&(core->piece));
  if (GAME_MODE_SWITCH) gameStroke(core);
}

// (ノ ◑‿◑)ノ  (I'm part of thr "playerAction" function - for pres:action);
void pressAction(GameMain_t* core) {
  rotateTetrino(&(core->piece));
  if (ifCollide(core, &(core->piece))) {
    for (int i = 0; i < 3; i++) {
      rotateTetrino(&(core->piece));
    }
  }
}

// (ノ ◑‿◑)ノ (I rotate a Tetrino)
void rotateTetrino(Tetrino_t* piece) {  // will it work?
  int tmp[PIECE_SIZE][PIECE_SIZE];
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      tmp[i][j] = piece->shape[i][j];
    }
  }
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      piece->shape[i][j] = tmp[PIECE_SIZE - 1 - j][i];
    }
  }
}

// (ノ ◑‿◑)ノ (I do the initial setup of the game core structure)
GreatFlag_t initiateGame(GameMain_t* core) {
  srand(time(NULL));
  GreatFlag_t error_flag = SUCCESS;
  error_flag = fieldAllocationMaster(core);
  error_flag =
      (error_flag && shapeAllocationMaster(&(core->piece))) ? SUCCESS : FAILURE;
  error_flag = (error_flag && shapeAllocationMaster(&(core->next_piece)))
                   ? SUCCESS
                   : FAILURE;
  if (error_flag) {
    core->score = 0;
    core->state = st_GoingOn;
    core->level = 1;
    core->high_score = highScoreKeeper(0);
    cleanTetrino(&(core->next_piece));
    setNextTetrino(core);
    newTetrinoDrop(core);
  }
  startTimer();
  return error_flag;
}

// (ノ ◑‿◑)ノ (I allocate "field" part of GameMain_t)
GreatFlag_t fieldAllocationMaster(GameMain_t* core) {
  GreatFlag_t allocation_flag = SUCCESS;
  core->field = calloc(FULL_HIGHT, sizeof(int*));
  allocation_flag = (core->field == NULL)
                        ? FAILURE
                        : SUCCESS;  // check if allocation was successful
  for (int i = 0; allocation_flag && i < FULL_HIGHT; i++) {
    core->field[i] = (int*)calloc(WIDTH, sizeof(int));
    if (core->field[i] == NULL) {
      allocation_flag = FAILURE;
      fieldFreeMaster(core, i);
      continue;
    }
    for (int j = 0; j < WIDTH; j++) {
      core->field[i][j] = 0;
    }
  }
  return allocation_flag;
}

// (ノ ◑‿◑)ノ (I free "field" part of GameMain_t)
void fieldFreeMaster(GameMain_t* core, int lines) {
  if (core != NULL && core->field != NULL) {
    for (int i = 0; i < lines; i++) {
      if (core->field[i] != NULL) free(core->field[i]);
    }
    free(core->field);
    core->field = NULL;
  }
}

// (ノ ◑‿◑)ノ (I allocate "shape" part of Tetrino_t of GameMain_t)
GreatFlag_t shapeAllocationMaster(Tetrino_t* piece) {
  GreatFlag_t allocation_flag = SUCCESS;
  piece->shape = calloc(PIECE_SIZE, sizeof(int*));
  allocation_flag = (piece->shape == NULL)
                        ? FAILURE
                        : SUCCESS;  // check if allocation was successful
  for (int i = 0; allocation_flag && i < PIECE_SIZE; i++) {
    piece->shape[i] = (int*)calloc(PIECE_SIZE, sizeof(int));
    if (piece->shape[i] == NULL) {
      allocation_flag = FAILURE;
      shapeFreeMaster(piece, i);
      continue;
    }
    for (int j = 0; j < PIECE_SIZE; j++) {
      piece->shape[i][j] = 0;
    }
  }
  return allocation_flag;
}

// (ノ ◑‿◑)ノ (I free "shape" part of Tetrino_t of GameMain_t)
void shapeFreeMaster(Tetrino_t* piece, int lines) {
  if (piece != NULL && piece->shape != NULL) {
    for (int i = 0; i < lines; i++) {
      if (piece->shape[i] != NULL) free(piece->shape[i]);
    }
    free(piece->shape);
    piece->shape = NULL;
  }
}

// (ノ ◑‿◑)ノ (I keep the main game structure safe)
GameMain_t* structureKeeper() {
  static GameMain_t core = {.state = st_GameOver,
                            .field = NULL,
                            .next_piece.shape = NULL,
                            .piece.shape = NULL,
                            .level = 1};
  return &core;
}

// (ノ ◑‿◑)ノ (I make stroke movement depend on how many of these are needed
// based on time passed)
void catchUpStructure() {
  GameMain_t* core = structureKeeper();
  if (core->state == st_GoingOn) {
    int strokes = strokesToMake(core->level);
    for (int i = 0; i < strokes; i++) {
      gameStroke(core);
    }
  }
}

// (ノ ◑‿◑)ノ (I upgreat level and high score if it's needed)
void whenScoreChanges() {
  GameMain_t* core = structureKeeper();
  if (core->score >= MAX_SCORE || core->score < 0) core->score = MAX_SCORE;
  if (core->score > core->high_score) core->high_score = core->score;
  if (core->score / LEVELING_SCORE >= 1) core->level = (core->score / LEVELING_SCORE) + 1;
}

// (ノ ◑‿◑)ノ (I read ad score high score aka. work with files)
int highScoreKeeper(char choice) {
  FILE* scoretable = NULL;
  const GameMain_t* core = structureKeeper();
  int output = 0;
  switch (choice) {
    case 0:
      scoretable = fopen("high_score.txt", "r");
      if (scoretable == NULL)
        output = INPUT_ERROR;
      else {
        fscanf(scoretable, "%d", &output);
        fclose(scoretable);
      }
      break;
    case 1:
      if (core->high_score <= core->score) {
        scoretable = fopen("high_score.txt", "w");
        if (scoretable == NULL)
          output = INPUT_ERROR;
        else {
          fprintf(scoretable, "%d", (int)core->score);
          fclose(scoretable);
        }
      }
      break;
    default:
      break;
  }
  return output;
}