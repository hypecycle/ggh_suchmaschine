# ggh_suchmaschine

These are the Arduino and RPI files for a Project for my agency. The Arduino board drives several functions of a "machine" we have been constructing to address talents.
Basically, we are putting the bosses in a box to talk to future employees. 

The board waits for input of a button to drive a steam generator, a bell and an LED-lighted presentation platform. 
Furthermore, it drives an LED-Neopixel pad of individual Neopixels.

/ --------------------------------------------------------------------------
//
// LED
// 00  09  10  19  20
// 01  08  11  18  21
// 02  07  12  17  22
// 03  06  13  16  23
// 04  05  14  15  24
//
// --------------------------------------------------------------------------
//
// Arduino Pins
//
//      D2          D3        D5       D4        D10           D13
// Arcade Button   Secret    Rotate   Bell   Arcade Button   Neopixel
//    switch                                    LED
// -------------------------------------------------------------------------

Stages
// 01 Idle Mode 
//    LED Blinking slowly
// 02 Calculating ->
//    Going nuts
// 03 Calling for help
//    Bell ringing
// 04 Freibier

The fritzing sketch (1.0) depicts the latest version of the board: Board_10.fzz
The openscad sketch depicts the dimensions. Uncomment parts to make them visible: Suchmaschine_10.scad



