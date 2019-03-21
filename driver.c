/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#pragma config(Sensor, dgtl1,  left,           sensorTouch)
#pragma config(Sensor, dgtl2,  right,          sensorTouch)
#pragma config(Motor,  port2,           leftmotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           elevator,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           conveyor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightmotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           guard,         tmotorVex393_MC29, openLoop)

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

void mtr(short btn, short sbtn, short port, int speed, int rspeed) //dont touch this part
{
	if(vexRT[btn] == 1)
	{
		motor[port] = speed;
	}
	else if(vexRT[sbtn] == 1)
	{
		motor[port] = rspeed;
	}
	else
	{
		motor[port] = 0;
	}
}
void drive(short left, short right)
{
	motor[left] = vexRT[Ch3];
	motor[right] = vexRT[Ch2];

}

//void onHittingTarget()

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;
	/*MotorPIDSpeedCtrl[port2] = mtrNoReg;
	nMotorPIDSpeedCtrl[port3] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[port4] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[port5] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[port8] = mtrSpeedReg;*/

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.
	//go forward
	//set port 2 motor(left motor) to speed 127(max)
	motor[port2] = 95;
	//set port 5 motor(right motor) to speed 127(max)
	motor[port5] = 127;
	//wait 3200 milliseconds(make motors move forward for 3200 milliseconds, or 3.2 seconds)
	wait1Msec(3200);
	//set motor speed to 0 (motor's stopped)
	motor[port2] = 0;
	motor[port5] = 0;
	//wait half a second
	wait1Msec(500);
	//set left motor to 127(max) (turn right)
	motor[port2] = 127;
	motor[port5] = -127;
	//wait 500 milliseconds (0.5 seconds) to run code for 0.5 seconds
	wait1Msec(425);
	//set port2 motor to 0. turns off motor.
	motor[port2] = 0;
	motor[port5] = 0;
	//wait makes it more professional
	wait1Msec(750);
	bool touchedTarget = false;
	while(!touchedTarget){
		if(SensorValue[dgtl1] == 1 && SensorValue[dgtl2] == 1)
		{
			motor[port2] = -55;
			motor[port5] = -55;
			wait1Msec(100);
			motor[port2] = 0;
			motor[port5] = 0;
			wait1Msec(750);
			//move the conveyor belt
			motor[port4] = -25;
			//run conveyor belt for 2 secondss
			wait1Msec(2000);
			//turn off conveyor belt
			motor[port4] = 0;
			touchedTarget = true;
		}
		else if (SensorValue[dgtl1] == 1)
		{
			if(time1[T1] > 35)
			{
				motor[port5] = 75;
				wait1Msec(15);
				motor[port2] = -75;
				clearTimer(T2);
			}
			else
			{
				//go backwards
				motor[port2] = -55;
				motor[port5] = -55;
				wait1Msec(125);
				motor[port2] = 0;
				motor[port5] = 0;
				wait1Msec(750);
				//move the conveyor belt
				motor[port4] = -20;
				//run conveyor belt for 2 secondss
				wait1Msec(2000);
				//turn off conveyor belt
				motor[port4] = 0;
				touchedTarget = true;
			}

		}
		else if (SensorValue[dgtl2] == 1)
		{
			if(time1[T2] > 35)
			{
				motor[port2] = 75;
				wait1Msec(15);
				motor[port5] = -75;
				clearTimer(T1);
			}
			else
			{
				motor[port2] = -55;
				motor[port5] = -55;
				wait1Msec(125);
				motor[port2] = 0;
				motor[port5] = 0;
				wait1Msec(750);
				//move the conveyor belt
				motor[port4] = -25;
				//run conveyor belt for 2 secondss
				wait1Msec(2000);
				//turn off conveyor belt
				motor[port4] = 0;
				touchedTarget = true;
			}
		}
		else if (SensorValue[dgtl2] == 0 && SensorValue[dgtl1] == 0)
		{
			motor[port2] = 57.5;
			motor[port5] = 63.5;
			wait1Msec(25);
			motor[port2] = 0;
			motor[port5] = 0;
		}
	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop
	while (true)
	{
		// This is the main execution loop for the user control program.
		// Each time through the loop your program should update motor + servo
		// values based on feedback from the joysticks.

		// ........................................................................
		// Insert user code here. This is where you use the joystick values to
		// update your motors, etc.
		// ........................................................................

		// Remove this function call once you have "real" code.
		drive(port2, port5);
		mtr(Btn5D, Btn5U, port3, 127, -127); //just put the controller buttons to move forward, backwards, then put the port for the motor to move.
		mtr(Btn6D, Btn6U, port4, 100, -100); //add as many of these functions as you want
		mtr(Btn8U, Btn8D, port8, 75, -75);
	}
}
