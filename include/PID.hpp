#ifndef _PID_HPP_
#define _PID_HPP_

#define DEFAULTKP 1
#define LEEWAY 10

double abscap(double val, double cap);
void control(void *ignore);
void moveBase(double p_Left_Target, double p_Right_Target, double p_Max_Power = 100, double p_KP = DEFAULTKP, double p_timeout, double autondelay = 0);

#endif