#include <wiringPi.h>
#include <iostream>

using namespace std;

float angle;
int stateA = 0;
int stateB = 0;

// MOTOR PINS
int signalA = 0;
int signalB = 2;

// ENCODER PINS
int motorControl = 1;
int motorForward = 24;
int motorReverse = 25;
// int motor1Switch = 23;

// PUSH BUTTON
int buttonForward = 4;
int buttonReverse = 5;

void cw()
{
	digitalWrite(motorReverse,FALSE);
	digitalWrite(motorForward,TRUE);
	pwmWrite(motorControl,512);
	return;
}
void ccw()
{
	digitalWrite(motorForward,FALSE);
	digitalWrite(motorReverse,FALSE);
	pwmWrite(motorControl,0);
	return;
}
void forwardRotate()
{
	if (stateA == stateB)
	{
		angle = angle + 0.3;
		cout<<"Angle: "<<angle<<endl;
		stateA = digitalRead(signalA);
	}
	return;
}
void reverseRotate()
{
	if (stateA == stateB)
	{
		angle = angle - 0.3;
		cout<<"Angle: "<<angle<<endl;
		stateB = digitalRead(signalB);
	}
	return;
}
	    
int main(void)

{
     
    // ENCODER SETUP
    wiringPiSetup();
    pinMode(signalA, INPUT);
    pinMode(signalB, INPUT);
    
    // BUTTON SETUP
    pinMode(buttonForward,INPUT);
    pinMode(buttonReverse,INPUT);
    pullUpDnControl(buttonForward,PUD_UP);
    
    // MOTOR SETUP
    wiringPiSetupGpio;
    pinMode(motorControl,PWM_OUTPUT);
    pinMode(motorForward,OUTPUT);
    pinMode(motorReverse,OUTPUT);
    
    // pinMode(motor1Switch,INPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
   
    
    // 160 = 60Hz, 192 = 50Hz, 256 = 37.5Hz
    
    // MOTOR INTERRUPTS
    wiringPiISR(4,INT_EDGE_RISING,&cw);
    wiringPiISR(5,INT_EDGE_RISING,&ccw);
    
    // ENCODER INTERRUPTS
    wiringPiISR(0,INT_EDGE_BOTH,&forwardRotate);
    wiringPiISR(2,INT_EDGE_BOTH,&reverseRotate);
    
    // MAIN LOOP
    while(1)
    {
		if(angle > 360) 			// checks for angle greater than 360
		{
			angle = 0;
		}
		if(angle < 0)				// checks for angle less than 0
		{
			angle = 360;
		}
		
	}
	
    return 0;
}
