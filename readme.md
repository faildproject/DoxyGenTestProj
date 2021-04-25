# Overview
This Documentation will give some rules for Codestyle

## Variables
+ All Variables allways lower case and delimited by "_" (my_var)
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
+ Objects are lowercase but ends with "Obj" (instance_from_classObj)

## Functions
+ Begin the functionname with lower case and end with "Fkt" 
+ Starts parameter with "t_"
+ If a function consumes an interface, overgive an reference to this.

Example: myFunctionFkt(Stream& t_stream);

## Classes
+ Classes always Camlecase and ends with "Class"
+ Objects as are lower Case and ends with "Obj"
Example: MyOwnClass();