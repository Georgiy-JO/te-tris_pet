#ifndef TETRIS_TETRINOS_SPEEDS_SCORE
#define TETRIS_TETRINOS_SPEEDS_SCORE

// TETRIONOS
#define INIT_LINE {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
#define INIT_T {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0};
#define INIT_LEFT_L {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0};
#define INIT_RIGHT_L {0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0};
#define INIT_SQUARE {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
#define INIT_LEFT_SNAKE {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0};
#define INIT_RIGHT_SNAKE {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};

typedef enum {
  tt_None = -1,
  tt_Line,
  tt_Square,
  tt_LeftL,
  tt_RightL,
  tt_LeftSnake,
  tt_RightSnake,
  tt_TheT
} TetrinoType_t;

// TETRINOS MOVING SPEEDS
#define SPEED_1 2
#define SPEED_2 1
#define SPEED_3 0.8
#define SPEED_4 0.7
#define SPEED_5 0.6
#define SPEED_6 0.5
#define SPEED_7 0.4
#define SPEED_8 0.25
#define SPEED_9 0.2
#define SPEED_10 0.1

// SCORE SETTINGS
#if (__INT_MAX__ < 99999999)
#define MAX_SCORE __INT_MAX__
#else
#define MAX_SCORE 99999999  // 99999900?
#endif

#define LEVELING_SCORE 600

enum PointsTier { pt_One = 100, pt_Two = 300, pt_Three = 700, pt_Four = 1500 };

#endif