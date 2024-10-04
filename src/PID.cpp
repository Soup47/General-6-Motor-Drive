#include "main.h"


double abscap (double val, double cap) {
    double ret = val;
    if (val > cap) {
        ret = cap;
    } else if (val < -cap) {
        ret = -cap;
    }
    return ret;
}


double targL = 0, targR = 0, errL = 0, errR = 0, powL = 0, powR = 0, kp = 0, maxPow = 0, timeout = 0, encdL = 0, encdR = 0;
bool activatePID = false;


void control (void * ignore) {
    Motor FL (FLPORT);
	Motor BL (BLPORT);
	Motor FR (FRPORT);
	Motor BR (BRPORT);
    
    Motor ML (MLPORT);
    Motor MR (MRPORT);

    while (true) {
        if (activatePID) {
            encdL = FL.get_position();
            encdR = FR.get_position();

            errL = targL - encdL;
            errR = targR - encdR;

            powL = kp * errL;
            powR = kp * errR;

            powL = abscap (powL, maxPow);
            powR = abscap (powR, maxPow);

            FL.move(powL);
            FR.move(powR);
            BL.move(powL);
            BR.move(powR);

            ML.move(powL);
            MR.move(powR);

        }
        
        delay(5);
    }
}

// auton function

void moveBase (double p_targL, double p_targR, double p_maxPow, double p_kp, double p_timeout) {

    targL = p_targL;
    targR = p_targR;
    maxPow = p_maxPow;
    kp = p_kp;

    Motor FL (FLPORT);
	Motor BL (BLPORT);
	Motor FR (FRPORT);
	Motor BR (BRPORT);

    Motor ML (MLPORT);
    Motor MR (MRPORT);

    FL.tare_position();
    BL.tare_position();
    FR.tare_position();
    BR.tare_position();
    ML.tare_position();
    MR.tare_position();

    timeout = p_timeout;
    double startMillis = millis();

    while ((fabs(targL - encdL) > LEEWAY || fabs(targR - encdR) > LEEWAY) && millis() - startMillis < timeout) {
        activatePID = true;
        delay(5);
    }

    activatePID = false;
    FL.move(0);
    BL.move(0);
    FR.move(0);
    BR.move(0);

    ML.move(0);
    MR.move(0);
}