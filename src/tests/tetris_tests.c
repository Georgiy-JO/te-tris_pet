#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../brick_game/tetris/tetris.h"

// elevator    service ff
/* print the whole fieal with the curret piece
void printerfFull(GameMain_t core){
  printf("\n\n");
  for(int i=0;i<FULL_HIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      if(i>=core.piece.y && j>=core.piece.x && i<(core.piece.y+PIECE_SIZE) &&
j<(core.piece.x+PIECE_SIZE))
        printf("%d",(core.field[i][j]+core.piece.shape[i-core.piece.y][j-core.piece.x]));
      else
        printf("%d",core.field[i][j]);
    }
    printf("\n");
  }
  return;
}
*/
// elevator    begining of tests
START_TEST(test_copyTetrino) {
  Tetrino_t tetr_1, tetr_2;
  GreatFlag_t check = SUCCESS;
  ck_assert_int_eq(shapeAllocationMaster(&tetr_1), check);
  ck_assert_int_eq(shapeAllocationMaster(&tetr_2), check);
  tetr_1.type = tt_LeftL;
  tetr_1.x = WIDTH / 2;
  tetr_1.y = HEIGHT / 2 + 5;
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      tetr_1.shape[i][j] = (i + j) % 2;
    }
  }
  copyTetrino(&tetr_1, &tetr_2);
  ck_assert_int_eq(tetr_1.type, tetr_2.type);
  ck_assert_int_eq(tetr_1.x, tetr_2.x);
  ck_assert_int_eq(tetr_1.y, tetr_2.y);
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      ck_assert_int_eq(tetr_1.shape[i][j], tetr_2.shape[i][j]);
    }
  }
  shapeFreeMaster(&tetr_1, PIECE_SIZE);
  shapeFreeMaster(&tetr_2, PIECE_SIZE);
}
START_TEST(test_cleanTetrino) {
  GameMain_t core;
  GreatFlag_t check = SUCCESS;
  ck_assert_int_eq(shapeAllocationMaster(&(core.piece)), check);
  core.piece.type = tt_LeftSnake;
  core.piece.x = WIDTH - 4;
  core.piece.y = HEIGHT - 4;
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      core.piece.shape[i][j] = (i + j) % 2;
    }
  }
  ck_assert_int_eq(core.piece.type, tt_LeftSnake);
  ck_assert_int_eq(core.piece.x, WIDTH - 4);
  ck_assert_int_eq(core.piece.y, HEIGHT - 4);
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      ck_assert_int_eq(core.piece.shape[i][j], (i + j) % 2);
    }
  }
  cleanTetrino(&(core.piece));
  ck_assert_int_eq(core.piece.type, tt_None);
  ck_assert_int_eq(core.piece.x, 0);
  ck_assert_int_eq(core.piece.y, 0);
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      ck_assert_int_eq(core.piece.shape[i][j], 0);
    }
  }
  shapeFreeMaster(&(core.piece), PIECE_SIZE);
}
START_TEST(test_setShape) {
  GameMain_t core;
  const int arr[PIECE_SIZE * PIECE_SIZE] = INIT_LINE;
  GreatFlag_t check = SUCCESS;
  ck_assert_int_eq(shapeAllocationMaster(&(core.piece)), check);
  core.piece.type = tt_Line;
  core.piece.x = WIDTH / 2;
  core.piece.y = 5;
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      core.piece.shape[i][j] = TAKEN;
    }
  }
  setShape(arr, &(core.piece.shape));
  ck_assert_int_eq(core.piece.type, tt_Line);
  ck_assert_int_eq(core.piece.x, WIDTH / 2);
  ck_assert_int_eq(core.piece.y, 5);
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      if (i == 1)
        ck_assert_int_eq(core.piece.shape[i][j], TAKEN);
      else
        ck_assert_int_eq(core.piece.shape[i][j], EMPTY);
    }
  }
  shapeFreeMaster(&(core.piece), PIECE_SIZE);
}
START_TEST(test_setNextTetrino) {
  GameMain_t core;
  GreatFlag_t check = SUCCESS;
  ck_assert_int_eq(shapeAllocationMaster(&(core.next_piece)), check);
  for (int k = 0; k < 20; k++) {
    setNextTetrino(&core);
    for (int i = 0; i < PIECE_SIZE; i++) {
      for (int j = 0; j < PIECE_SIZE; j++) {
        // printf("%d",core.next_piece.shape[i][j]);
      }
      // printf("\n");
    }
    // printf("\n");
  }
  shapeFreeMaster(&(core.next_piece), PIECE_SIZE);
}
START_TEST(test_newTetrinoDrop) {
  GameMain_t core;
  GreatFlag_t check = SUCCESS;
  ck_assert_int_eq(shapeAllocationMaster(&(core.next_piece)), check);
  ck_assert_int_eq(shapeAllocationMaster(&(core.piece)), check);
  int arr[PIECE_SIZE * PIECE_SIZE] = INIT_LEFT_SNAKE;
  setShape(arr, &(core.next_piece.shape));
  core.next_piece.type = tt_LeftSnake;
  newTetrinoDrop(&core);
  ck_assert_int_eq(core.piece.type, tt_LeftSnake);
  ck_assert_int_eq(core.piece.x, WIDTH / 2 - 2);
  ck_assert_int_eq(core.piece.y, 0);
  for (int i = 0, k = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++, k++) {
      ck_assert_int_eq(core.piece.shape[i][j], arr[k]);
    }
  }
  // for(int i=0;i<PIECE_SIZE;i++){
  //   for(int j=0;j<PIECE_SIZE;j++){
  //     printf("%d",core.next_piece.shape[i][j]);
  //   }
  //   printf("\n");
  // }
  shapeFreeMaster(&(core.next_piece), PIECE_SIZE);
  shapeFreeMaster(&(core.piece), PIECE_SIZE);
}
START_TEST(test_initiateGame) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  for (int i = 0; i < FULL_HIGHT; i++) {
    // if(i==PIECE_SIZE-1) printf("\n");
    for (int j = 0; j < WIDTH; j++) {
      // if(i>=core.piece.y && j>=core.piece.x && i<(core.piece.y+PIECE_SIZE) &&
      // j<(core.piece.x+PIECE_SIZE))
      //   printf("%d",(core.field[i][j]+core.piece.shape[i-core.piece.y][j-core.piece.x]));
      // else
      //   printf("%d",core.field[i][j]);
    }
    // printf("\n");
  }
  // printf("\n\n");
  check = 0;
  ck_assert_int_eq(core.score, check);
  check = 2;
  ck_assert_int_eq(core.state, check);
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      // printf("%d",core.next_piece.shape[i][j]);
    }
    // printf("\n");
  }
  shapeFreeMaster(&(core.next_piece), PIECE_SIZE);
  shapeFreeMaster(&(core.piece), PIECE_SIZE);
  fieldFreeMaster(&core, FULL_HIGHT);
}
START_TEST(test_overGame) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  for (int i = 0; i < FULL_HIGHT; i++) {
    // if(i==PIECE_SIZE-1) printf("\n");
    for (int j = 0; j < WIDTH; j++) {
      // if(i>=core.piece.y && j>=core.piece.x && i<(core.piece.y+PIECE_SIZE) &&
      // j<(core.piece.x+PIECE_SIZE))
      //   printf("%d",(core.field[i][j]+core.piece.shape[i-core.piece.y][j-core.piece.x]));
      // else
      //   printf("%d",core.field[i][j]);
    }
    // printf("\n");
  }
  // printf("\n\n");
  check = 0;
  ck_assert_int_eq(core.score, check);
  check = 2;
  ck_assert_int_eq(core.state, check);
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      // printf("%d",core.next_piece.shape[i][j]);
    }
    // printf("\n");
  }
  overGame(&core);
  check = 0;
  ck_assert_int_eq(core.state, check);
}
START_TEST(test_movement) {
  GameMain_t core;
  int check = SUCCESS;
  int x = WIDTH / 2 - 2, y = 0;
  ck_assert_int_eq(initiateGame(&core), check);
  ck_assert_int_eq(core.piece.y, y);
  ck_assert_int_eq(core.piece.x, x);
  moveDown(&(core.piece));
  y++;
  ck_assert_int_eq(core.piece.y, y);
  ck_assert_int_eq(core.piece.x, x);
  moveLeft(&(core.piece));
  x--;
  ck_assert_int_eq(core.piece.y, y);
  ck_assert_int_eq(core.piece.x, x);
  moveRight(&(core.piece));
  x++;
  ck_assert_int_eq(core.piece.y, y);
  ck_assert_int_eq(core.piece.x, x);
  moveUp(&(core.piece));
  y--;
  ck_assert_int_eq(core.piece.y, y);
  ck_assert_int_eq(core.piece.x, x);
  overGame(&core);
}
START_TEST(test_fixToField_1) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  fixToField(&core);
  for (int i = 0; i < FULL_HIGHT; i++) {
    // if(i==PIECE_SIZE-1) printf("\n");
    for (int j = 0; j < WIDTH; j++) {
      // printf("%d",core.field[i][j]);
    }
    // printf("\n");
  }
  overGame(&core);
}
START_TEST(test_fixToField_2) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  core.piece.x = WIDTH - PIECE_SIZE;
  core.piece.y = FULL_HIGHT - PIECE_SIZE;
  fixToField(&core);
  for (int i = 0; i < FULL_HIGHT; i++) {
    // if(i==PIECE_SIZE-1) printf("\n");
    for (int j = 0; j < WIDTH; j++) {
      // printf("%d",core.field[i][j]);
    }
    // printf("\n");
  }
  overGame(&core);
}
START_TEST(test_lineEraser_1) {
  GameMain_t core;
  int check = SUCCESS, score = 0;
  ck_assert_int_eq(initiateGame(&core), check);
  for (int i = 0; i < WIDTH; i++) {
    core.field[FULL_HIGHT - 1][i] = TAKEN;
  }
  check = 100;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  check = 0;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  for (int i = 0; i < WIDTH; i++) {
    core.field[FULL_HIGHT - 1][i] = TAKEN;
    core.field[FULL_HIGHT - 4][i] = TAKEN;
  }
  check = 300;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  check = 0;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  for (int i = 0; i < WIDTH; i++) {
    core.field[FULL_HIGHT - 1][i] = TAKEN;
    core.field[FULL_HIGHT - 4][i] = TAKEN;
    core.field[FULL_HIGHT - 2][i] = TAKEN;
  }
  check = 700;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  check = 0;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  for (int i = 0; i < WIDTH; i++) {
    core.field[FULL_HIGHT - 1][i] = TAKEN;
    core.field[FULL_HIGHT - 4][i] = TAKEN;
    core.field[FULL_HIGHT - 2][i] = TAKEN;
    core.field[FULL_HIGHT - 10][i] = TAKEN;
  }
  check = 1500;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  check = 0;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  overGame(&core);
}
START_TEST(test_lineEraser_2) {
  GameMain_t core;
  int check = SUCCESS, score = 0;
  ck_assert_int_eq(initiateGame(&core), check);
  for (int i = 0; i < WIDTH; i++) {
    core.field[FULL_HIGHT - 1][i] = TAKEN;
    core.field[FULL_HIGHT - 4][i] = TAKEN;
    core.field[FULL_HIGHT - 2][i] = TAKEN;
    core.field[FULL_HIGHT - 6][i] = TAKEN;
  }
  core.field[FULL_HIGHT - 5][0] = TAKEN;
  core.field[FULL_HIGHT - 5][1] = TAKEN;
  core.field[FULL_HIGHT - 5][2] = TAKEN;
  core.field[FULL_HIGHT - 5][WIDTH - 1] = TAKEN;
  core.field[FULL_HIGHT - 5][WIDTH - 2] = TAKEN;
  core.field[FULL_HIGHT - 3][0] = TAKEN;
  core.field[FULL_HIGHT - 3][4] = TAKEN;
  core.field[FULL_HIGHT - 3][WIDTH - 5] = TAKEN;
  core.field[FULL_HIGHT - 7][1] = TAKEN;
  core.field[FULL_HIGHT - 7][2] = TAKEN;
  core.field[FULL_HIGHT - 7][3] = TAKEN;
  core.field[FULL_HIGHT - 7][4] = TAKEN;
  core.field[FULL_HIGHT - 7][5] = TAKEN;
  // for(int i=0;i<FULL_HIGHT;i++){
  //   if(i==PIECE_SIZE-1) printf("\n");
  //   for(int j=0;j<WIDTH;j++){
  //       printf("%d",core.field[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  check = 1500;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  // for(int i=0;i<FULL_HIGHT;i++){
  //   if(i==PIECE_SIZE-1) printf("\n");
  //   for(int j=0;j<WIDTH;j++){
  //       printf("%d",core.field[i][j]);
  //   }
  //   printf("\n");
  // }
  check = 0;
  score = lineEraser(&core);
  ck_assert_int_eq(score, check);
  check = TAKEN;
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][0], TAKEN);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][1], EMPTY);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][2], EMPTY);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][3], EMPTY);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][4], TAKEN);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][5], TAKEN);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][6], EMPTY);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][7], EMPTY);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][8], EMPTY);
  ck_assert_int_eq(core.field[FULL_HIGHT - 1][9], EMPTY);
  overGame(&core);
}
START_TEST(test_rotateTetrino) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  copyTetrino(&core.piece, &core.next_piece);
  // for(int i=0;i<PIECE_SIZE;i++){
  //   for(int j=0;j<PIECE_SIZE;j++){
  //     printf("%d",core.piece.shape[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  rotateTetrino(&(core.piece));
  // for(int i=0;i<PIECE_SIZE;i++){
  //   for(int j=0;j<PIECE_SIZE;j++){
  //     printf("%d",core.piece.shape[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  rotateTetrino(&(core.piece));
  // for(int i=0;i<PIECE_SIZE;i++){
  //   for(int j=0;j<PIECE_SIZE;j++){
  //     printf("%d",core.piece.shape[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  rotateTetrino(&(core.piece));
  // for(int i=0;i<PIECE_SIZE;i++){
  //   for(int j=0;j<PIECE_SIZE;j++){
  //     printf("%d",core.piece.shape[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  rotateTetrino(&(core.piece));
  // for(int i=0;i<PIECE_SIZE;i++){
  //   for(int j=0;j<PIECE_SIZE;j++){
  //     printf("%d",core.piece.shape[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      ck_assert_int_eq(core.piece.shape[i][j], core.next_piece.shape[i][j]);
    }
  }
  overGame(&core);
}
START_TEST(test_ifCollide_1) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  const int arr[PIECE_SIZE * PIECE_SIZE] = INIT_LEFT_L;
  setShape(arr, &(core.piece.shape));
  rotateTetrino(&(core.piece));
  check = FAILURE;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);

  core.piece.y = FULL_HIGHT - 1 - 4;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);

  core.piece.y = FULL_HIGHT - 4;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);

  core.piece.y = FULL_HIGHT - 3;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);

  check = SUCCESS;
  core.piece.y = FULL_HIGHT - 2;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);

  overGame(&core);
}
START_TEST(test_ifCollide_2) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  const int arr[PIECE_SIZE * PIECE_SIZE] = INIT_LEFT_L;
  setShape(arr, &(core.piece.shape));
  rotateTetrino(&(core.piece));
  check = FAILURE;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  core.piece.x = 0;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  core.piece.x = -1;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = -2;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  overGame(&core);
}
START_TEST(test_ifCollide_3) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  const int arr[PIECE_SIZE * PIECE_SIZE] = INIT_LEFT_L;
  setShape(arr, &(core.piece.shape));
  rotateTetrino(&(core.piece));
  check = FAILURE;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  core.piece.x = WIDTH - 5;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  core.piece.x = WIDTH - 4;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  core.piece.x = WIDTH - 3;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = WIDTH - 2;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  overGame(&core);
}
START_TEST(test_ifCollide_4) {
  GameMain_t core;
  int check = SUCCESS;
  ck_assert_int_eq(initiateGame(&core), check);
  const int arr[PIECE_SIZE * PIECE_SIZE] = INIT_LEFT_L;
  setShape(arr, &(core.piece.shape));
  rotateTetrino(&(core.piece));

  for (int i = 0; i < WIDTH; i++) {
    core.field[FULL_HIGHT - 1][i] = TAKEN;
    core.field[FULL_HIGHT - 2][i] = TAKEN;
  }
  core.field[FULL_HIGHT - 3][0] = TAKEN;
  core.field[FULL_HIGHT - 3][4] = TAKEN;
  core.field[FULL_HIGHT - 3][5] = TAKEN;
  core.field[FULL_HIGHT - 3][6] = TAKEN;
  core.field[FULL_HIGHT - 3][9] = TAKEN;
  core.field[FULL_HIGHT - 4][0] = TAKEN;
  core.field[FULL_HIGHT - 4][9] = TAKEN;
  core.field[FULL_HIGHT - 5][0] = TAKEN;
  core.field[FULL_HIGHT - 5][9] = TAKEN;
  core.field[FULL_HIGHT - 6][0] = TAKEN;
  core.field[FULL_HIGHT - 6][9] = TAKEN;
  core.field[FULL_HIGHT - 7][0] = TAKEN;

  check = FAILURE;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  core.piece.x = -1;
  core.piece.y = FULL_HIGHT - 11;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = -2;
  core.piece.y = FULL_HIGHT - 11;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = FAILURE;
  core.piece.x = -1;
  core.piece.y = FULL_HIGHT - 10;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = -1;
  core.piece.y = FULL_HIGHT - 9;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = FAILURE;
  core.piece.x = 0;
  core.piece.y = FULL_HIGHT - 9;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = FAILURE;
  core.piece.x = 0;
  core.piece.y = FULL_HIGHT - 6;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = FAILURE;
  core.piece.x = 0;
  core.piece.y = FULL_HIGHT - 5;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = 0;
  core.piece.y = FULL_HIGHT - 4;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = 2;
  core.piece.y = FULL_HIGHT - 4;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = FAILURE;
  core.piece.x = 2;
  core.piece.y = FULL_HIGHT - 5;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = 3;
  core.piece.y = FULL_HIGHT - 5;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = 8;
  core.piece.y = FULL_HIGHT - 5;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = 7;
  core.piece.y = FULL_HIGHT - 5;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = FAILURE;
  core.piece.x = 6;
  core.piece.y = FULL_HIGHT - 5;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = SUCCESS;
  core.piece.x = 7;
  core.piece.y = FULL_HIGHT - 6;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  check = FAILURE;
  core.piece.x = 7;
  core.piece.y = FULL_HIGHT - 7;
  // printerfFull(core);
  // printf("Collide = %d\n",check);
  ck_assert_int_eq(ifCollide(&core, &core.piece), check);
  overGame(&core);
}
START_TEST(test_playerAction_1) {
  GameMain_t core = {.state = st_Pause};
  int check = SUCCESS;
  playerAction(&core, 0);
  check = st_Pause;
  ck_assert_int_eq(core.state, check);
  core.state = st_GameOver;
  playerAction(&core, 0);
  check = st_GoingOn;
  ck_assert_int_eq(core.state, check);
  // printerfFull(core);
  playerAction(&core, 1);
  check = st_Pause;
  ck_assert_int_eq(core.state, check);
  playerAction(&core, 1);
  check = st_GoingOn;
  ck_assert_int_eq(core.state, check);
  core.state = st_GameOver;
  playerAction(&core, 1);
  check = st_GameOver;
  ck_assert_int_eq(core.state, check);
  core.state = st_GoingOn;
  playerAction(&core, 2);
  check = st_GameOver;
  ck_assert_int_eq(core.state, check);
  playerAction(&core, 2);
  check = st_Exit;
  ck_assert_int_eq(core.state, check);
}
START_TEST(test_playerAction_2) {
  GameMain_t core = {.state = st_GameOver};
  int check = SUCCESS;
  playerAction(&core, Start);
  check = st_GoingOn;
  ck_assert_int_eq(core.state, check);
  // printerfFull(core);
  playerAction(&core, 2);
  check = st_GameOver;
  ck_assert_int_eq(core.state, check);
}
START_TEST(test_playerAction_3) {
  GameMain_t core = {.state = st_GameOver};
  int check = SUCCESS;
  playerAction(&core, Start);
  check = st_GoingOn;
  ck_assert_int_eq(core.state, check);
  playerAction(&core, 3);
  playerAction(&core, 3);
  playerAction(&core, 3);
  playerAction(&core, 3);
  playerAction(&core, 3);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 4);
  playerAction(&core, 7);
  playerAction(&core, 7);
  playerAction(&core, 7);
  playerAction(&core, 7);
  playerAction(&core, 7);
  playerAction(&core, 7);
  playerAction(&core, 5);
  playerAction(&core, 5);
  playerAction(&core, 5);

  // printerfFull(core);
  playerAction(&core, 3);
  core.field[0][WIDTH - 1] = TAKEN;
  core.field[1][WIDTH - 1] = TAKEN;
  core.field[2][WIDTH - 1] = TAKEN;
  core.field[3][WIDTH - 1] = TAKEN;
  playerAction(&core, 7);
  playerAction(&core, 4);
  playerAction(&core, 7);
  playerAction(&core, 4);
  core.field[0][WIDTH - 1] = EMPTY;
  core.field[1][WIDTH - 1] = EMPTY;
  core.field[2][WIDTH - 1] = EMPTY;
  core.field[3][WIDTH - 1] = EMPTY;

  // printerfFull(core);
  playerAction(&core, 6);
  // printerfFull(core);
  playerAction(&core, 6);
  playerAction(&core, 6);
  playerAction(&core, 6);
  playerAction(&core, 6);
  playerAction(&core, 6);
  playerAction(&core, 6);
  playerAction(&core, 6);

  // printerfFull(core);
  playerAction(&core, 2);
}
START_TEST(test_gameStroke) {
  GameMain_t core = {.state = st_GameOver};
  int check = st_GoingOn;
  playerAction(&core, Start);
  ck_assert_int_eq(core.state, check);

  for (int i = 0; i < 100; i++) {
    // printerfFull(core);
    gameStroke(&core);
  }
  check = st_GameOver;
  for (int i = 0; i < 200 && core.state != st_GameOver; i++) {
    // printerfFull(core);
    gameStroke(&core);
  }
  ck_assert_int_eq(core.state, check);
}
/*
START_TEST(test_insidePrinter){
  GameMain_t core={.state=st_GameOver};
  int check=st_GoingOn;
  playerAction(&core,Start);
  ck_assert_int_eq(core.state,check);

  for(long int i=0;i<150000000000&&core.state!=st_GameOver;i++){
    if(i%100000000==0){
    insidePrinter(core);
    gameStroke(&core);
  }}
  check=st_GameOver;
  ck_assert_int_eq(core.state,check);
}
START_TEST(test_mainCycleV1){
  mainCycleV1();
}
*/
START_TEST(test_structureKeeper) {
  GameMain_t *core = NULL;
  int check = SUCCESS;
  core = structureKeeper();
  ck_assert_ptr_nonnull(core);
  ck_assert_ptr_null(core->field);
  ck_assert_ptr_null(core->next_piece.shape);
  ck_assert_ptr_null(core->piece.shape);
  ck_assert_int_eq(core->state, st_GameOver);
  ck_assert_int_eq(initiateGame(structureKeeper()), check);
  GameMain_t *core_2 = structureKeeper();
  ck_assert_ptr_nonnull(core_2->field);
  ck_assert_ptr_nonnull(core_2->next_piece.shape);
  ck_assert_ptr_nonnull(core_2->piece.shape);
  ck_assert_int_eq(core_2->state, st_GoingOn);
  ck_assert_int_eq(core_2->score, 0);
  ck_assert_int_eq(core_2->level, 1);
  // printerfFull(*core_2);
  playerAction(core_2, 2);
  check = st_GameOver;
  ck_assert_int_eq(core->state, check);
  ck_assert_int_eq(core_2->state, check);
}
START_TEST(test_outputFieldKeeper) {
  int **field = NULL;
  field = outputFieldKeeper(0);
  ck_assert_ptr_nonnull(field);
  field = NULL;
  ck_assert_ptr_null(field);
  field = outputFieldKeeper(1);
  ck_assert_ptr_nonnull(field);
  int check = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      ck_assert_int_eq(field[i][j], check);
    }
  }
  field = outputFieldKeeper(2);
  ck_assert_ptr_null(field);
}
START_TEST(test_userInput) {
  GameMain_t *core = NULL;
  bool hold = FAILURE;
  UserAction_t action_my = Start;
  userInput(action_my, hold);
  ck_assert_ptr_null(core);
  core = structureKeeper();
  ck_assert_ptr_nonnull(core);
  ck_assert_int_eq(core->state, st_GameOver);
  ck_assert_ptr_null(core->field);
  hold = SUCCESS;
  userInput(action_my, hold);
  core = structureKeeper();
  ck_assert_ptr_nonnull(core);
  ck_assert_int_eq(core->state, st_GoingOn);
  ck_assert_int_eq(core->score, 0);
  ck_assert_int_eq(core->level, 1);
  ck_assert_ptr_nonnull(core->field);
  ck_assert_ptr_nonnull(core->next_piece.shape);
  ck_assert_ptr_nonnull(core->piece.shape);
  // printerfFull(*core);
  action_my = Left;
  userInput(action_my, hold);
  // printerfFull(*core);
  action_my = Down;
  userInput(action_my, hold);
  // printerfFull(*core);
  action_my = Terminate;
  userInput(action_my, hold);
  ck_assert_int_eq(core->state, st_GameOver);
  hold = FAILURE;
  userInput(action_my, hold);
  ck_assert_int_eq(core->state, st_GameOver);
}
START_TEST(test_structureTranslator) {
  GameMain_t *core = structureKeeper();
  GameInfo_t info;
  outputFieldKeeper(0);
  ck_assert_ptr_null(core->field);
  ck_assert_int_eq(core->state, st_GameOver);
  ck_assert_int_eq(core->score, 0);
  ck_assert_int_eq(core->level, 1);
  ck_assert_ptr_null(core->next_piece.shape);
  ck_assert_ptr_null(core->piece.shape);
  userInput(Start, SUCCESS);
  ck_assert_ptr_nonnull(core->field);
  ck_assert_int_eq(core->state, st_GoingOn);
  ck_assert_int_eq(core->score, 0);
  ck_assert_int_eq(core->level, 1);
  ck_assert_ptr_nonnull(core->next_piece.shape);
  ck_assert_ptr_nonnull(core->piece.shape);
  userInput(Right, SUCCESS);
  userInput(Down, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Down, SUCCESS);
  userInput(Left, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Left, SUCCESS);
  userInput(Left, SUCCESS);
  userInput(Down, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Down, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Left, SUCCESS);
  userInput(Left, SUCCESS);
  userInput(Down, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Down, SUCCESS);
  structureTranslator(core, &info);
  ck_assert_int_eq(info.score, core->score);
  ck_assert_int_eq(info.level, core->level);
  ck_assert_int_eq(info.pause, 0);
  userInput(Pause, SUCCESS);
  structureTranslator(core, &info);
  ck_assert_int_eq(info.pause, 1);
  userInput(Pause, SUCCESS);
  structureTranslator(core, &info);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(info.speed, 1);
  int delta = FULL_HIGHT - HEIGHT;
  for (int i = delta; i < FULL_HIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (core->piece.y <= i && i < (core->piece.y + PIECE_SIZE) &&
          core->piece.x <= j && j < (core->piece.x + PIECE_SIZE))
        ck_assert_int_eq(
            info.field[i - delta][j],
            (core->field[i][j] +
             core->piece.shape[i - core->piece.y][j - core->piece.x]));
      else
        ck_assert_int_eq(info.field[i - delta][j], core->field[i][j]);
    }
  }
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      ck_assert_int_eq(info.next[i][j], core->next_piece.shape[i][j]);
    }
  }

  // printerfFull(*core);
  //   printf("\n\n");
  // for(int i=0;i<HEIGHT;i++){
  //   for(int j=0;j<WIDTH;j++){
  //     printf("%d",info.field[i][j]);
  //   }
  //   printf("\n");
  // }

  userInput(Action, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Left, SUCCESS);
  userInput(Left, SUCCESS);
  userInput(Down, SUCCESS);
  userInput(Right, SUCCESS);
  userInput(Action, SUCCESS);
  userInput(Down, SUCCESS);
  structureTranslator(core, &info);
  ck_assert_int_eq(info.score, core->score);
  ck_assert_int_eq(info.level, core->level);
  ck_assert_int_eq(info.pause, 0);
  userInput(Pause, SUCCESS);
  structureTranslator(core, &info);
  ck_assert_int_eq(info.pause, 1);
  userInput(Pause, SUCCESS);
  structureTranslator(core, &info);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(info.speed, 1);
  for (int i = delta; i < FULL_HIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (core->piece.y <= i && i < (core->piece.y + PIECE_SIZE) &&
          core->piece.x <= j && j < (core->piece.x + PIECE_SIZE))
        ck_assert_int_eq(
            info.field[i - delta][j],
            (core->field[i][j] +
             core->piece.shape[i - core->piece.y][j - core->piece.x]));
      else
        ck_assert_int_eq(info.field[i - delta][j], core->field[i][j]);
    }
  }
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      ck_assert_int_eq(info.next[i][j], core->next_piece.shape[i][j]);
    }
  }

  // printerfFull(*core);
  //   printf("\n\n");
  // for(int i=0;i<HEIGHT;i++){
  //   for(int j=0;j<WIDTH;j++){
  //     printf("%d",info.field[i][j]);
  //   }
  //   printf("\n");
  // }

  userInput(Terminate, SUCCESS);
  outputFieldKeeper(2);
}
START_TEST(test_timer) {
  int time_O;
  int sec, check = 1;
  startTimer();
  time_O = clock();
  while (1) {
    sec = (clock() - time_O) / CLOCKS_PER_SEC;
    if (sec == check) {
      check++;
      ck_assert_int_eq(getTimer(), sec);
    }
    if (check == 3) break;
  }
  startTimer();
  time_O = clock();
  check = 1;
  while (1) {
    sec = (clock() - time_O) / CLOCKS_PER_SEC;
    if (sec == check) {
      check++;
      ck_assert_int_eq(getTimer(), sec);
    }
    if (check == 2) break;
  }

  startTimer();
  time_O = clock();
  check = 5;
  int save = 2;
  int flag = 0;
  while (1) {
    sec = (clock() - time_O) / CLOCKS_PER_SEC;
    if (sec == save && flag == 0) {
      ck_assert_int_eq(getTimer(), sec);
      // printf("%ld\n", getTimer());
      pauseTimer();
      flag++;
    }

    if (sec == check && flag == 1) {
      ck_assert_int_eq(sec, check);
      ck_assert_int_eq(getTimer(), save);
      pauseTimer();
      flag++;
      time_O = clock() - CLOCKS_PER_SEC * check;
    }
    if (flag == 2 && sec == check + save) {
      ck_assert_int_eq(sec, check + save);
      ck_assert_int_eq(getTimer(), save * 2);
      break;
    }
  }
}
START_TEST(test_strokesToMake) {
  int time_O;
  int level = 1;
  int check = 2;
  startTimer();
  time_O = clock();
  int i = 0;
  while (1) {
    if ((clock() - time_O) / CLOCKS_PER_SEC == 4) {
      time_O = clock();
      ck_assert_int_eq(strokesToMake(level), check);
      level++;
      switch (level) {
        case 2:
          check = 4;
          break;
        case 3:
          check = 5;
          break;
        case 5:
          check = 6;
          break;
        case 6:
          check = 8;
          break;
        case 7:
          check = 10;
          break;
        case 8:
          check = 16;
          break;
        case 9:
          check = 20;
          break;
        case 10:
          check = 40;
          break;
        default:
          break;
      }
    }
    if (level == 5 && (i == 0 || i == 10)) {
      pauseTimer();
      i++;
      time_O = clock();
    }
    if (level == 5) {
      i++;
    }

    if (level == 11)  // 12 - for best full check
      break;
  }
}
START_TEST(test_catchUpStructure) {
  GameMain_t *core = structureKeeper();
  userInput(Start, 1);
  clock_t time_0 = clock();
  // printerfFull(*core);
  int move_for = 10;
  while (1) {
    if ((clock() - time_0) / (CLOCKS_PER_SEC * move_for) >= 1) {
      catchUpStructure();
      break;
    }
  }
  ck_assert_int_eq(core->piece.y, move_for / levelTable(1));
  userInput(Terminate, 1);

  // printerfFull(*core);
}
START_TEST(test_updateCurrentState) {
  GameInfo_t info = updateCurrentState();
  ck_assert_ptr_null(info.field);
  ck_assert_ptr_null(outputFieldKeeper(1));
  userInput(Start, 1);
  // info=updateCurrentState();
  // for(int i=0;i<HEIGHT;i++){
  //   for(int j=0;j<WIDTH;j++){
  //     printf("%d",info.field[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  clock_t time_0 = clock();
  while (1) {
    if ((clock() - time_0) / (CLOCKS_PER_SEC * 3) >= 1) {
      break;
    }
  }
  info = updateCurrentState();
  ck_assert_ptr_nonnull(info.field);
  ck_assert_ptr_nonnull(outputFieldKeeper(1));
  ck_assert_ptr_nonnull(info.next);
  GameMain_t *core = structureKeeper();
  ck_assert_int_eq(info.score, core->score);
  ck_assert_int_eq(info.level, core->level);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(info.speed, 1);
  // for(int i=0;i<HEIGHT;i++){
  //   for(int j=0;j<WIDTH;j++){
  //     printf("%d",info.field[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n\n");
  userInput(Terminate, 1);
  info = updateCurrentState();
  ck_assert_ptr_null(info.field);
  ck_assert_ptr_nonnull(outputFieldKeeper(1));
  ck_assert_ptr_null(info.next);
  ck_assert_int_eq(info.score, core->score);
  ck_assert_int_eq(info.level, core->level);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(info.speed, 1);
  userInput(Terminate, 1);
  info = updateCurrentState();
  ck_assert_ptr_null(info.field);
  ck_assert_ptr_null(outputFieldKeeper(1));
  ck_assert_ptr_null(info.next);
}
START_TEST(test_freaky_tests) {
  ck_assert_ptr_null(outputFieldKeeper(5));
  ck_assert_int_eq(highScoreKeeper(5), 0);
  ck_assert_double_eq(levelTable(11), SPEED_10);
  ck_assert_double_eq(levelTable(15), SPEED_10);
  ck_assert_double_eq(levelTable(20), SPEED_10);
  ck_assert_double_eq(levelTable(100), SPEED_10);
  timer(5);
  userInput(Start, 1);
  userInput(Down, 1);
  userInput(Down, 1);
  userInput(Down, 1);
  userInput(Down, 1);
  userInput(Down, 1);
  userInput(Down, 1);
  userInput(Down, 1);
  userInput(Down, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Action, 1);
  userInput(Terminate, 1);
  userInput(Terminate, 1);
}
START_TEST(test_whenScoreChanges) {
  userInput(Start, 1);
  GameMain_t *core = structureKeeper();
  whenScoreChanges();
  core->score = MAX_SCORE;
  whenScoreChanges();
  ck_assert_int_eq(core->score, MAX_SCORE);
  ck_assert_int_eq(core->high_score, MAX_SCORE);
  userInput(Terminate, 1);
  userInput(Terminate, 1);
}
START_TEST(test_highScoreKeeper) {
  int high_score = highScoreKeeper(0);
  ck_assert_int_eq(high_score, 0);
  userInput(Start, 1);
  GameMain_t *core = structureKeeper();
  core->score = MAX_SCORE;
  whenScoreChanges();
  highScoreKeeper(1);
  high_score = highScoreKeeper(0);
  ck_assert_int_eq(high_score, MAX_SCORE);
  userInput(Terminate, 1);
  userInput(Terminate, 1);
}
// elevator test blocks
void test_block_1(SRunner *sr) {
  Suite *s = suite_create("Test block #1");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_copyTetrino);
  tcase_add_test(tc_core, test_cleanTetrino);
  tcase_add_test(tc_core, test_setShape);
  tcase_add_test(tc_core, test_setNextTetrino);
  tcase_add_test(tc_core, test_newTetrinoDrop);
  tcase_add_test(tc_core, test_initiateGame);
  tcase_add_test(tc_core, test_overGame);
  tcase_add_test(tc_core, test_movement);
  tcase_add_test(tc_core, test_fixToField_1);
  tcase_add_test(tc_core, test_fixToField_2);
  tcase_add_test(tc_core, test_lineEraser_1);
  tcase_add_test(tc_core, test_lineEraser_2);
  tcase_add_test(tc_core, test_rotateTetrino);
  tcase_add_test(tc_core, test_ifCollide_1);
  tcase_add_test(tc_core, test_ifCollide_2);
  tcase_add_test(tc_core, test_ifCollide_3);
  tcase_add_test(tc_core, test_ifCollide_4);
  tcase_add_test(tc_core, test_playerAction_1);
  tcase_add_test(tc_core, test_playerAction_2);
  tcase_add_test(tc_core, test_playerAction_3);
  tcase_add_test(tc_core, test_gameStroke);
  // tcase_add_test(tc_core, test_insidePrinter);
  // tcase_add_test(tc_core, test_mainCycleV1);
  tcase_add_test(tc_core, test_structureKeeper);
  tcase_add_test(tc_core, test_outputFieldKeeper);
  tcase_add_test(tc_core, test_userInput);
  tcase_add_test(tc_core, test_structureTranslator);

  srunner_add_suite(sr, s);
}
void test_block_2(SRunner *sr) {
  Suite *s = suite_create(
      "Test block #2: timer related \n (testing may take a while...)");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_timer);
  tcase_add_test(tc_core, test_strokesToMake);
  tcase_add_test(tc_core, test_catchUpStructure);
  tcase_add_test(tc_core, test_updateCurrentState);

  srunner_add_suite(sr, s);
}
void test_block_3(SRunner *sr) {
  Suite *s = suite_create("Test block #3: extra tests");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_whenScoreChanges);
  tcase_add_test(tc_core, test_highScoreKeeper);
  tcase_add_test(tc_core, test_freaky_tests);

  srunner_add_suite(sr, s);
}
// elevator     end
int main(void) {
  int number_failed;
  Suite *s = suite_create("Tetris tests");
  SRunner *sr = srunner_create(s);

  test_block_1(sr);
  test_block_2(sr);
  test_block_3(sr);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
