#include "main.h"
#include "PID.hpp"
#include "globals.hpp"
#include "mechLib.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.h"

void initialize()
{ // ---------------------------------------------------- INITIALIZATION

	// --- MOTORS:
	Motor FL(FLPORT, FLGEAR, FLREVERSE, E_MOTOR_ENCODER_DEGREES);
	Motor BL(BLPORT, BLGEAR, BLREVERSE, E_MOTOR_ENCODER_DEGREES);
	Motor FR(FRPORT, FRGEAR, FRREVERSE, E_MOTOR_ENCODER_DEGREES);
	Motor BR(BRPORT, BRGEAR, BRREVERSE, E_MOTOR_ENCODER_DEGREES);
	Motor ML(MLPORT, MLGEAR, MLREVERSE, E_MOTOR_ENCODER_DEGREES);
	Motor MR(MRPORT, MRGEAR, MRREVERSE, E_MOTOR_ENCODER_DEGREES);

	// --- PNEUMATICS:

	// ADIDigitalOut piston1 (name);
	// ADIDigitalOut piston2 (name);

	// --- PID INITIALIZATION:
	Controller master(E_CONTROLLER_MASTER);

	// pinMode(1, OUTPUT);
	// digitalWrite(1, LOW);
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{ // ---------------------------------------------------- AUTONOMOUS

	double autonDelay = 200;
	// [Add Autonomous code here]
}

void opcontrol()
{
	// CALLING HARDWARE:
	// --- Motors
	Motor FL(FLPORT);
	Motor BL(BLPORT);
	Motor FR(FRPORT);
	Motor BR(BRPORT);
	Motor ML(MLPORT);
	Motor MR(MRPORT);

	// --- Pneumatics
	// ADIDigitalOut piston1 (name);
	// ADIDigitalOut piston2 (name);

	// PID INITIALIZATION:
	Controller master(E_CONTROLLER_MASTER);

	// VARIABLES INITIALIZATION:
	double Left_Power = 0, Right_Power = 0;
	bool Side_Swap = false;
	bool Side_Swap_Toggle = false;

	// MAINLOOP:
	while (true)
	{
		// INPUTS:
		Left_Power = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		Right_Power = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		Side_Swap_Toggle = master.get_digital_new_press(E_CONTROLLER_DIGITAL_X);

		if (Side_Swap_Toggle)
		{
			Side_Swap = !Side_Swap;
		}

		if (Side_Swap = false)
		{
			// HARDWARE CONTROL:
			FL.move(Left_Power);
			BL.move(Left_Power);
			FR.move(Right_Power);
			BR.move(Right_Power);
			ML.move(Left_Power);
			MR.move(Right_Power);
		}
		else
		{
			// HARDWARE CONTROL:
			FL.move(Right_Power);
			BL.move(Right_Power);
			FR.move(Left_Power);
			BR.move(Left_Power);
			ML.move(Right_Power);
			MR.move(Left_Power);
		}

		// MAINLOOP DELAY:
		delay(5); // [Adjust to increase reaction speed]
	}
}
