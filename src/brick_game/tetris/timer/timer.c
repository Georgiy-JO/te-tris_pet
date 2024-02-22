#include "timer.h"

// (ノ ◑‿◑)ノ (I'm a timer, I can be started/restarted/paused and I return the
// number of seconds passed from the restarte)
long int timer(char restart) {
  static clock_t time_0 = 0;

  static long int seconds = 0;
  static GreatFlag_t pause_switch = FAILURE;
  switch (restart) {
    case 0:
      time_0 = clock();
      seconds = 0;
      pause_switch = FAILURE;
      break;
    case 1:
      if (!pause_switch)
        seconds = (long int)(clock() - time_0) / CLOCKS_PER_SEC;
      break;
    case 2:
      if (pause_switch) {
        pause_switch = FAILURE;
        time_0 = clock() - seconds * CLOCKS_PER_SEC;
      } else {
        seconds = (long int)(clock() - time_0) / CLOCKS_PER_SEC;
        pause_switch = SUCCESS;
      }
      break;
    default:
      break;
  }
  if (seconds == MAXTIME || seconds < 0) {
    startTimer();
    if (restart == 2) pause_switch = SUCCESS;
  }
  return seconds;

  /*
    long int seconds=0;
    if(!restart)
      time_0=clock();
    else{
      seconds=(long int)(clock()-time_0)/CLOCKS_PER_SEC;
        if(seconds==MAXTIME||seconds<0)
          startTimer();
    }
    return seconds;
    */
}

// (ノ ◑‿◑)ノ (I start/restart timer)
void startTimer() { timer(0); }

// (ノ ◑‿◑)ノ (I get the timer info)
long int getTimer() { return timer(1); }

// (ノ ◑‿◑)ノ (I pause timer)
void pauseTimer() { timer(2); }

// (ノ ◑‿◑)ノ (I return the ammount of strokes to make depending on level based
// on timer output)
int strokesToMake(int level) {
  static int seconds_0 = 0;
  double output = 0;
  double speed = levelTable(level);
  if (seconds_0 > getTimer()) seconds_0 = 0;
  if ((double)(getTimer() - seconds_0) / speed >= 1) {
    // printf("%f-%ld-%d-%f\n",speed,
    // getTimer(),seconds_0,(double)(getTimer()-seconds_0)/speed);
    output = (double)(getTimer() - seconds_0) / speed;
    seconds_0 = getTimer();
  }
  return (int)output;
}

// (ノ ◑‿◑)ノ (I controle speed of stroking depending on level)
double levelTable(int level) {
  double output = SPEED_10;
  switch (level) {
    case 1:
      output = SPEED_1;
      break;
    case 2:
      output = SPEED_2;
      break;
    case 3:
      output = SPEED_3;
      break;
    case 4:
      output = SPEED_4;
      break;
    case 5:
      output = SPEED_5;
      break;
    case 6:
      output = SPEED_6;
      break;
    case 7:
      output = SPEED_7;
      break;
    case 8:
      output = SPEED_8;
      break;
    case 9:
      output = SPEED_9;
      break;
    case 10:
      output = SPEED_10;
      break;
    default:
      break;
  }
  return output;
}
