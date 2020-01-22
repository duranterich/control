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

    wiringPiSetup();
    pinMode(signalA, INPUT); // Input from button press
    pinMode(signalB, INPUT); // Output to LED Toggle
    
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
                angle = angle - 0.3;
                }
                cout<<"\nAngle: "<<angle<<endl;
            }
            aLastState = aState;
    }
    return 0;
}
