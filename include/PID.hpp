#ifndef _PID_HPP_
#define _PID_HPP_


#define DEFAULTKP 1
#define LEEWAY 10

double abscap (double val, double cap);
void control (void * ignore);
void moveBase (double p_targL, double p_targR,  double p_maxPow = 100, double p_kp = DEFAULTKP, double p_timeout, double autondelay = 0);


#endif