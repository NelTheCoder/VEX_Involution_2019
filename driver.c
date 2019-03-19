#pragma config(Sensor, dgtl1,  left,           sensorTouch)
#pragma config(Sensor, dgtl2,  right,          sensorTouch)
#pragma config(Motor,  port2,           leftmotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           elevator,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           conveyor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightmotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           guard,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//click motor and sensor setup to configure motors
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




task main()
{

	while(true)
	{
		drive(port2, port5);
		mtr(Btn5D, Btn5U, port3, 127, -127); //just put the controller buttons to move forward, backwards, then put the port for the motor to move.
		mtr(Btn6D, Btn6U, port4, 100, -100); //add as many of these functions as you want
		mtr(Btn8U, Btn8D, port8, 75, -75);
		//autonomous most left tile
		if(vexRT[Btn7L] == 1)
		{
			//go forward
			//set port 2 motor(left motor) to speed 127(max)
			motor[port2] = 95;
			//set port 5 motor(right motor) to speed 127(max)
			motor[port5] = 127;
			//wait 3200 milliseconds(make motors move forward for 3200 milliseconds, or 3.2 seconds)
			wait1Msec(3300);
			//set motor speed to 0 (motor's stopped)
			motor[port2] = 0;
			motor[port5] = 0;
			//wait half a second
			wait1Msec(500);
			//set left motor to 127(max) (turn right)
			motor[port2] = 127;
			motor[port5] = -127;
			//wait 400 milliseconds (0.4 seconds) to run code for 0.9 seconds
			wait1Msec(400);
			//set port2 motor to 0. turns off motor.
			motor[port2] = 0;
			motor[port5] = 0;
			//wait makes it more professional
			wait1Msec(750);
			bool touchedTarget = false;
			while(!touchedTarget){
				if(SensorValue[dgtl1] == 1 && SensorValue[dgtl2] == 1)
				{
					motor[leftmotor] = -55;
					motor[rightmotor] = -55;
					wait1Msec(75);
					motor[leftmotor] = 0;
					motor[rightmotor] = 0;
					wait1Msec(750);
					//move the conveyor belt
					motor[port4] = -35;
					//run conveyor belt for 2 secondss
					wait1Msec(1500);
					//turn off conveyor belt
					motor[port4] = 0;
					touchedTarget = true;
				}
				else if (SensorValue[left] == 1)
				{
					if(time1[T1] > 25)
					{
						motor[rightmotor] = 75;
						wait1Msec(50);
						motor[leftmotor] = -75;
						clearTimer(T2);
					}
					else
					{
						//go backwards
						motor[leftmotor] = -55;
						motor[rightmotor] = -55;
						wait1Msec(75);
						motor[leftmotor] = 0;
						motor[rightmotor] = 0;
						wait1Msec(750);
						//move the conveyor belt
						motor[port4] = -35;
						//run conveyor belt for 2 secondss
						wait1Msec(1500);
						//turn off conveyor belt
						motor[port4] = 0;
						touchedTarget = true;
					}

				}
				else if (SensorValue[right] == 1)
				{
					if(time1[T2] > 25)
					{
						motor[leftmotor] = 75;
						wait1Msec(50);
						motor[rightmotor] = -75;
						clearTimer(T1);
					}
					else
					{
						motor[leftmotor] = -55;
						motor[rightmotor] = -55;
						wait1Msec(75);
						motor[leftmotor] = 0;
						motor[rightmotor] = 0;
						wait1Msec(750);
						//move the conveyor belt
						motor[port4] = -35;
						//run conveyor belt for 2 secondss
						wait1Msec(1500);
						//turn off conveyor belt
						motor[port4] = 0;
						touchedTarget = true;
					}
				}
				else if (SensorValue[right] == 0 && SensorValue[left] == 0)
				{
					motor[leftmotor] = 47.5;
					motor[rightmotor] = 63.5;
					wait1Msec(25);
					motor[leftmotor] = 0;
					motor[rightmotor] = 0;
				}
			}
		}
	}
}
