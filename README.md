# uvtimer
Very simple timer for turning off UV lamp (or any device) after certain amount of time

Easy to use timer for contolling curation time of UV light.

BOM

| ID 	|  Name 	|  Size 	| Designator  	| Notes  	|
|---	|---	|---	|---	|---	|
|   1	|  Capacitor 	| 10uF  	| C2  	|   	|
|   2	|  ATMega328 	|   	|   U3 	|  	|
|   3	|  Resistor 	|   	10K|   R3	|   	|
|   4	|  SSD1306 	|128X32   	| U2  	|   	|
|   5	|  micro USB Female 	|  	| USB1 	|   	|


## Instructions

### Assembly
1.Asseblme the circuit as shown [here](https://easyeda.com/roey/uvtimer)
2. Connect relay to (not shown in the diagram)
3. Connect UV light to the relay (careful! make sure you know what you are doing!)
4. Compile and load the firmware to ATMega328 and place it in the board

### Usage
1. Turn the knob to determine number of minutes
2. Click the knob to start
3. System will stop after set minutes or upon another click
