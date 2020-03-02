//Phin6v2 code for the Phin6 controller box
// Tools > USB Type > Serial + MIDI

#include "Phin6.h"

//Phin6 in1;
Phin6 in2;
//Phin6 in3;
//Phin6 in4;
//Phin6 in5;
//Phin6 in6;

//const int in1_pin = A0;
const int in2_pin = A1;
//const int in3_pin = A3;
//const int in4_pin = A4;
//const int in5_pin = A5;
//const int in6_pin = A6;

const int pedal_or_expression1 = 8;
const int pedal_or_expression2 = 9;
const int pedal_or_expression3 = 10;
const int pedal_or_expression4 = 11;
const int pedal_or_expression5 = 12;
const int pedal_or_expression6 = 14;

// pins that add resistor
const int contact1 = 2;
const int contact2 = 3;
const int contact3 = 4;
const int contact4 = 5;
const int contact5 = 6;
const int contact6 = 7;

// controler numbers for inputs
const int controllerA1 = 64;
const int controllerA2 = 65;
const int controllerA3 = 66;
const int controllerA4 = 67;
const int controllerA5 = 68;
const int controllerA6 = 69;

const int channel = 1;

void setup() {
  // maybe the pinMode stuff could go in the class
//  pinMode(pedal_or_expression1, INPUT_PULLUP);
//  pinMode(pedal_or_expression2, INPUT_PULLUP);
//  pinMode(pedal_or_expression3, INPUT_PULLUP);
//  pinMode(pedal_or_expression4, INPUT_PULLUP);
//  pinMode(pedal_or_expression5, INPUT_PULLUP);
//  pinMode(pedal_or_expression6, INPUT_PULLUP);
  pinMode(contact1, INPUT_PULLUP);
  pinMode(contact2, INPUT_PULLUP);
  pinMode(contact3, INPUT_PULLUP);
  pinMode(contact4, INPUT_PULLUP);
  pinMode(contact5, INPUT_PULLUP);
  pinMode(contact6, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  // maybe include refresh rates in class instead of with delay that way contact mics can be more responsive.
  // also maybe make a scaling option for the class. resistance numbers could change for knobs or mics.

  // x.readPin(pin to be read, pin that interprets pedal type (sustain or expression), pin that reads dip switch)

//  int n1 = in1.readPin(in1_pin, pedal_or_expression1, contact1);
//  Serial.print("Input 1 : ");
//  Serial.println(n1); // what the? if this is not here it's all messed up for a pedal. why?
//  in1.toMidi(controllerA1, channel); // must select USB type MIDI on Teensy

  int n2 = in2.readPin(in2_pin, pedal_or_expression2);
//  Serial.print("Input 2 : ");
//  Serial.println(n2);
  in2.toMidi(controllerA2, channel);

//  int n3 = in3.readPin(in3_pin, pedal_or_expression3, contact3);
//  Serial.print("Input 3 : ");
//  Serial.println(n3);
//  in3.toMidi(controllerA3, channel);

//  int n4 = in4.readPin(in4_pin, pedal_or_expression4, contact4);
//  Serial.print("Input 4 : ");
//  Serial.println(n4);
//  in4.toMidi(controllerA4, channel);

//  int n5 = in5.readPin(in5_pin, pedal_or_expression5, contact5);
//  Serial.print("Input 5 : ");
//  Serial.println(n5);
//  in5.toMidi(controllerA5, channel);

//  int n6 = in6.readPin(in6_pin, pedal_or_expression6, contact6);
//  Serial.print("Input 6 : ");
//  Serial.println(n6);
//  in6.toMidi(controllerA6, channel);

  while (usbMIDI.read()) {
    // ignore incoming messages
  }

  delay(2); // lowering this makes contact mic more responsive.

}
