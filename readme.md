# Overview
This Documentation will give some rules for Codestyle

## Variables
+ All Variables allways lower case (myvar)
+ Global Variables starts with "g_" (g_gloabal)
+ Function Variables starts with "t_" (t_fktvar)
+ Enums starts with (e_myenum)
+ Typedefs starts with (td_typedef)
+ Constants allways Upper-Case (THATSCONSTANT)
    * Digital (In) Pins ends with "_PIN"
    * Digital (Out) Pins ends with "_POUT"
    * Analog (In) Pins ends with "_ADC"
    * Analog (Out) Pins ends with "_DAC"
    * Interface Pins ends with Interface-Shortcut (i.E. _I2C, _SPI, _UART, _OW ...) 

## Functions
+ Begin the functionname with lower case and end with "Fkt" 
+ Starts parameter with "t_"
+ If a function consumes an interface, overgive an reference to this.

Example: myFunctionFkt(Stream& t_stream);