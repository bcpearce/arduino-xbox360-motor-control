# Arudino Motor Control Through Xbox Controller
This project includes a simple windows program which generates Serial Commands based on input to an attached Xbox 360 controller.

## Setup
Load the included `*.ino` onto an Arudino microcontroller with an attached Motor shield.  The one that has been tested with this is the SainSmart L293D motor shield.  Motors should be connected to 1 and 4.  

Connect an Xbox 360 Controller to your Windows computer.  Connect the Arudino to the computer and set it to Serial Port `COM4`. Connect an LED+ to pin 7 and the LED- to a ground to enable the signal lamp.  The signal lamp will indicate if the stream is being sent to the Arduino.  

## Operation
Activate the Arudino running the `*.ino` file.  The indicator lamp should be 'off'.  Start the Code included in `main.cpp` on the host computer.  If the connection is successful, the indicator lamp will illuminate.  

Use the right stick to control the right motor, and the left stick to control the left motor.  
Press 'A' to exit the program on Windows.  

## Misc.
I reccommend using an external power supply for the Arudino.  The USB port doesn't supply much power, but this will depend on which motors you are using.  

