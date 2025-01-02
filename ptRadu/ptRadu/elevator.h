#ifndef ELEVATOR_H
#define	ELEVATOR_H

#include <xc.h>

void init(void);
void reset(void);
void start(void);
void updateLedIndicatior(void);
void moveMotor();
void logic();

void __interrupt() interr(void);

#endif	

