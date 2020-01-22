#include <wiringPi.h>
#include <iostream>

using namespace std;

int main(void)


{
    float angle = 0;
    int aState;
    int aLastState;

    int signalA = 0;
    int signalB = 2;
    int motorControl = 18;
    
    


    wiringPiSetup();
    pinMode(signalA, INPUT);       
    pinMode(signalB, INPUT);               
    
    pinMode(motorControl, PWM_OUTPUT); 
    
    aLastState = digitalRead(signalA);



    while(1)
    {
        aState = digitalRead(signalA);

        if(aState != aLastState) 
            {
                if(digitalRead(signalB) !=aState){
                angle = angle + 0.3;
                }
                else {
                counter = counter - 0.3;
                }
                cout<<"\nAngle: "<<angle<<endl;
            }
            aLastState = aState;
    }
    return 0;
}
