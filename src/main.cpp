#include "main.h"
#include "PID.hpp"
#include "globals.hpp"
#include "mechLib.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.h"

void initialize() {
	Motor FL (FLPORT, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor BL (BLPORT, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor FR (FRPORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor BR (BRPORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor ML (MLPORT, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor MR (MRPORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	//below is for pneumatics
//hello
    //ADIDigitalOut piston1 (name);
	//ADIDigitalOut piston2 (name);

	Controller master (E_CONTROLLER_MASTER);

	Task controlControl (control, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My Task");

	//pinMode(1, OUTPUT);
	//digitalWrite(1, LOW); 

}




void disabled() {}

void competition_initialize() {}

void autonomous() {

	double autonDelay = 200;

    // Paste Code Here
}

void opcontrol() {
	//motors
	Motor FL (FLPORT);
	Motor BL (BLPORT);
	Motor FR (FRPORT);
	Motor BR (BRPORT);
	Motor ML (MLPORT);
	Motor MR (MRPORT);

	//pneumatics
    //ADIDigitalOut piston1 (name);
	//ADIDigitalOut piston2 (name);

	Controller master (E_CONTROLLER_MASTER);

	//variables needed
	double leftPow = 0, rightPow = 0;
	while (true) {
		//inputs
		leftPow = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		rightPow = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

		//drive control
		FL.move(leftPow);
		BL.move(leftPow);
		FR.move(rightPow);
		BR.move(rightPow);
		ML.move(leftPow);
		MR.move(rightPow);

		delay(5);
	}
}
