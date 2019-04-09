#pragma config(Sensor, dgtl1,  left,           sensorTouch)
#pragma config(Sensor, dgtl2,  right,          sensorTouch)
#pragma config(Motor,  port2,           leftmotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           elevator,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           conveyor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightmotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           guard,         tmotorVex393_MC29, openLoop)
void onHittingTarget()
{
	motor[port2] = -55;
	motor[port5] = -55;
	wait1Msec(150/(nImmediateBatteryLevel * 0.01/76.83));
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

task main()
{
	motor[port2] = 127;
	motor[port5] = 82.5;
	wait1Msec(2700/(nImmediateBatteryLevel * 0.01/76.83));
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
	wait1Msec(1100/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(250);
	motor[port2] = 127;
	motor[port5] = -127;
	wait1Msec(440/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(250);
	motor[port2] = 127;
	motor[port5] = 82.5;
	wait1Msec(687.5/(nImmediateBatteryLevel * 0.01/76.83));
	motor[port2] = 0;
	motor[port5] = 0;
	wait1Msec(250);
	motor[port2] = 127;
	motor[port5] = -127;
	wait1Msec(44(nImmediateBatteryLevel * 0.01/76.83));
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
