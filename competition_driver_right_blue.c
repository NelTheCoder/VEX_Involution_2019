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

void onHittingTarget()
{
	motor[port2] = -55;
	motor[port5] = -55;
	wait1Msec(155/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(1100);
	//move the conveyor belt
	motor[port4] = -32;
	//run conveyor belt for 5 seconds
	wait1Msec(3000/(nImmediateBatteryLevel * 0.01/76.83));
	//turn off conveyor belt
	motor[port4] = 0;
}

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
task autonomous()
{
	motor[port2] = 127;
	motor[port5] = 82.5;
	wait1Msec(2660 /(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(250);
	motor[port2] = -127;
	motor[port5] = 127;
	wait1Msec(425/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(250);
	motor[port2] = 127;
	motor[port5] = 82.5;
	wait1Msec(1175/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(250);
	motor[port2] = 127;
	motor[port5] = -127;
	wait1Msec(425/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(250);
	motor[port2] = 127;
	motor[port5] = 82.5;
	wait1Msec(738/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(253);
	motor[port2] = 127;
	motor[port5] = -127;
	wait1Msec(397/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(400);
	bool touchedTarget = false;
	while(!touchedTarget){
		if(SensorValue[dgtl1] == 1 && SensorValue[dgtl2] == 1)
		{
			onHittingTarget();
			touchedTarget = true;
		}
		else if (SensorValue[dgtl1] == 1)
		{
			if(time1[T1] > 50)
			{
				motor[port5] = 75;
				wait1Msec(15/(nImmediateBatteryLevel * 0.01/76.83));
				motor[port2] = -75;
				clearTimer(T2);
			}
			else
			{
				onHittingTarget();
				touchedTarget = true;
			}

		}
		else if (SensorValue[dgtl2] == 1)
		{
			if(time1[T2] > 50)
			{
				motor[port2] = 75;
				wait1Msec(15/(nImmediateBatteryLevel * 0.01/76.83));
				motor[port5] = -75;
				clearTimer(T1);
			}
			else
			{
				onHittingTarget();
				touchedTarget = true;
			}
		}
		else if (SensorValue[dgtl2] == 0 && SensorValue[dgtl1] == 0)
		{
			motor[port2] = 57.5;
			motor[port5] = 63.5;
			wait1Msec(25/(nImmediateBatteryLevel * 0.01/76.83));
			motor[port2] = 0;
			motor[port5] = 0;
		}
	}
}
task usercontrol()
{
	while (true)
	{
		drive(port2, port5);
		mtr(Btn5D, Btn5U, port3, 127, -127); //just put the controller buttons to move forward, backwards, then put the port for the motor to move.
		mtr(Btn6D, Btn6U, port4, 100, -100); //add as many of these functions as you want
		mtr(Btn8U, Btn8D, port8, 75, -75);
		if(vexRT[Btn7U] == 1)
		{
			motor[port8] = 75;
			wait1Msec(175/(nImmediateBatteryLevel * 0.01/76.83));
			motor[port8] = 0;
		}
		else if(vexRT[Btn7D] == 1)
		{
			motor[port8] = -75;
			wait1Msec(150/(nImmediateBatteryLevel * 0.01/76.83));
			motor[port8] = 0;
		}
	}
}
