
#include "main.h"

void initializeIO() {
  pinMode(LIMIT_SWITCH, INPUT);
  pinMode(6, INPUT);
}

void initialize() {
  encoder1 = encoderInit(QUAD_TOP_PORT, QUAD_BOTTOM_PORT, false);
  encoder2 = encoderInit(QUAD_TOP_PORT2, QUAD_BOTTOM_PORT2, false);
  sensor = ultrasonicInit(7, 8);
}
