


#ifndef MOTORSTEUERUNG_H_
#define MOTORSTEUERUNG_H_

#include <hw_types.h>
#include"EGR_Cape.h"
#include"Conf_mod.h"
#include"EGR_DCMotor.h"
#include"delay_ms.h"



void MotorInit_and_Mux();
void MotorSpeedSet(int speed);
void MotorLinks(int curren_speed);
void MotorRechts(int curren_speed);
void LinkRad_RehctsRad(int speedlinks, int speedrechts);

#endif
