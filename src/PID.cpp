#include "main.h"

double abscap(double val, double cap)
{
    double ret = val;
    if (val > cap)
    {
        ret = cap;
    }
    else if (val < -cap)
    {
        ret = -cap;
    }
    return ret;
}

// VARIABLES INITIALIZATION:
double Left_Target = 0, Right_Target = 0, Left_Error = 0, Right_Error = 0, Left_Power = 0, Right_Power = 0, KP = 0, Max_Power = 0, timeout = 0, Left_Encoding = 0, Right_Encoding = 0;
bool activatePID = false;

void control(void *ignore)
{
    // CALLING HARDWARE:
    // --- Motors
    Motor FL(FLPORT);
    Motor BL(BLPORT);
    Motor FR(FRPORT);
    Motor BR(BRPORT);
    Motor ML(MLPORT);
    Motor MR(MRPORT);

    while (true)
    {
        if (activatePID)
        {
            Left_Encoding = FL.get_position();
            Right_Encoding = FR.get_position();

            Left_Error = Left_Target - Left_Encoding;
            Right_Error = Right_Target - Right_Encoding;

            Left_Power = KP * Left_Error;
            Right_Power = KP * Right_Error;

            Left_Power = abscap(Left_Power, Max_Power);
            Right_Power = abscap(Right_Power, Max_Power);

            FL.move(Left_Power);
            FR.move(Right_Power);
            BL.move(Left_Power);
            BR.move(Right_Power);

            ML.move(Left_Power);
            MR.move(Right_Power);
        }

        delay(5);
    }
}

// ---------------------------------------------------- AUTONOMOUS FUNCTION
void moveBase(double p_Left_Target, double p_Right_Target, double p_Max_Power, double p_KP, double p_timeout, double autondelay)
{

    Left_Target = p_Left_Target;
    Right_Target = p_Right_Target;
    Max_Power = p_Max_Power;
    KP = p_KP;

    Motor FL(FLPORT);
    Motor BL(BLPORT);
    Motor FR(FRPORT);
    Motor BR(BRPORT);

    Motor ML(MLPORT);
    Motor MR(MRPORT);

    FL.tare_position();
    BL.tare_position();
    FR.tare_position();
    BR.tare_position();
    ML.tare_position();
    MR.tare_position();

    timeout = p_timeout;
    double startMillis = millis();

    while ((fabs(Left_Target - Left_Encoding) > LEEWAY || fabs(Right_Target - Right_Encoding) > LEEWAY) && millis() - startMillis < timeout)
    {
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

    delay(autondelay);
}