# Automated Door Opening System
#### C and Assembly Iteration
The main premise of the Automated Door Opening System is that it allows users to open
a door hands free using a motion sensor. This project was created for a second year Computer
Organization course and was programmed in C and utlizes a bit of Assembly to change register values.

### Context
This project was targeted towards small businesses that may not access to a Automated
door opening system to prevent customers spreading germs by touching a door handle.
In addtion to this, theres light indicators to tell you the state the device is in, and
a system to tell you how many people have entered the store. This system was implemented as there are certain bylaws being pushed by the current Ontario government restricting the amount of people that can enter a store/resteraunt. Having looked at the 
statistics for the amount of businesses being fined, I came up with the idea to help stores easily limit the amount of people in their establishment.


## How it works
The following is a video DEMO of the system: [![Demo](https://i.imgur.com/41d3LHi.png)](https://youtu.be/bLug87rL2Y8?t=101)

**The components used in this project are as follows:**
* `Arduino Groove Board (Has ATMEGA328 Processor)`
* `SNAP Programmer`
* `Servo Motor`
* `PIR Motion Sensor `
* `Colored LEDs`
* `Push Buttons`
* `Bread Board`

When the program is launched, the system is off by default. When the system is turned on,
a green light is turned on. This is done by pressing a button. The system then awaits a signal from the 
motion sensor. When the motion sensor detects motion, a servo motor is turned on along with a red LED to indicate that the door is opening.
After a couple of seconds the door then begins the close. 

Everytime the door is opened, a register value is increased by one which acts as the count of the amount of people
that have entered the store. When a lower amount of people are in the store, a green light is turned on, when this number reaches a certain limit, a yellow LED is turned on.
When this number of people goes up to a really high number, a red light is shown until the maximum amount of people allowed inside a store is reached. When at maximum, all LEDs would turn on
and the door would cease to open unless the count is reset or the amount of people in the store is lowered.

*These limits are intended to be set by an owner of the door*

## Implementation 
Here are a few 3D models of how this design would look if implemented in local stores today:

![img2](https://i.imgur.com/gc42ACa.png)

![img1](https://i.imgur.com/NXlsBug.png)


