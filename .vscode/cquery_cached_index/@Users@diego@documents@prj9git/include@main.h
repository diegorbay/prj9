
#ifndef MAIN_H_

#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

#define QUAD_TOP_PORT 1
#define QUAD_BOTTOM_PORT 2

Encoder encoder1;

#define QUAD_TOP_PORT2 4
#define QUAD_BOTTOM_PORT2 5
Encoder encoder2;
#define LIMIT_SWITCH 6

Ultrasonic sensor;

void autonomous();

void initializeIO();

void initialize();

void operatorControl();

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
