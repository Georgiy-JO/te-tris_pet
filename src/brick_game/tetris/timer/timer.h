#ifndef TIMER
#define TIMER

#include <time.h>

#include "../tetris.h"

int strokesToMake(int level);
long int getTimer();
void startTimer();
void pauseTimer();
long int timer(char restart);  // has no independent tests
double levelTable(int level);  // has no independent tests

#endif