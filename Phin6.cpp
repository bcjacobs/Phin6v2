#include "Phin6.h"

/* Phin6 is a three-way (midi foot pedal, midi expression pedal, contact microphone) input interpreter
    that automatically detects the these devices and outputs their values scaled for midi.
*/

/*
 * currently the pedal must be set to the second position (normally closed) 
 * before inserting it into the Phin.
 */

Phin6::Phin6(bool displayMsg) { // of the TestLib class ... here's the TestLib constructor ... the parameter that you're expecting
  // Anything you need when instantiating your object goes here
  _msg = displayMsg;
}

// this is our 'begin' function
void Phin6::begin(int baudRate) { // Serial.begin needs to be in its own method
  Serial.begin(baudRate);
  if (_msg) {
    Serial.println("TestLib constructor instantiated (created) successfully.");
  }
}

// Pretend this is one or more complex and involved functions you have written
int Phin6::readPin(int pin, int pedalType, int buttonStateContact) { // TestLib:: says this function is part of the TestLib class

  _typeValueHold = digitalRead(pedalType);
  _contactState = digitalRead(buttonStateContact);
  _n0 = analogRead(pin);
  _counter = ++_counter;

//    _typeValue = _typeValueHold;

  if (_counter < switch_wait_time) {
    _n0 = 0;
  }

  if (_counter == switch_wait_time) {
    _typeValue = _typeValueHold;
  }

  if (_typeValueHold == 1) {
    _typeValue = _typeValueHold;
  }

  if (_typeValueHold == 0 && _n0 >= 200) { // this is try and detect a pedal that is normally open (floating).
    _typeValue = _typeValueHold;
  }

//  Serial.print(_n0);
//  Serial.print("   -   ");
//  Serial.print(_counter);
//  Serial.print("   -   ");
//  Serial.println(_typeValue);

  if (_counter >= switch_wait_time) {
//_typeValue = _typeValueHold; // do I really want this here?

  
    // Expression

    if (_typeValue == 1 && _contactState == 1) {
      _type = "Expression";
      if ((_previous_n0 - 5) < _n0 || (_previous_n0 + 5) > _n0) { // filters out some jitter
      _scaled_n0 = map(_n0, 0, 1012, 0, 127); //Feb 18, 2019 changed high number from 1014 to 1012
      _previous_n0 = _n0;
      }
    }

    // Pedal

    if (_typeValue == 0 && _contactState == 1) {
      _type = "Pedal";
      if (_n0 < 120) {
        _scaled_n0 = 127;     
      }
      else {
        _scaled_n0 = 0;
      }
    }
//    Serial.print(" - ");
//    Serial.println(_n0);

    // Contact

    if ((_typeValue == 0 || _typeValue == 1 ) && _contactState == 0) {
      _type = "Contact";
      _scaled_n0 = map(_n0, 0, 1014, 0, 127);
    }



  }

//    Serial.print(pin, DEC);
//    Serial.print(" (_counter): ");
//    Serial.print(_counter);
//    Serial.print(" (typeValueHold): ");
//    Serial.print(_typeValueHold);
//    Serial.print(" (typeValue): ");
//    Serial.print(_typeValue);
//    Serial.print(" (contactState): ");
//    Serial.print(_contactState);
//    Serial.print(" - ");
//    Serial.print(_type);
//    Serial.print(" - ");
//    Serial.print(_n0);
  return _n0;

//  Serial.print("_previous_n0");
//  Serial.print(_previous_n0);
//  Serial.print("_n0");
//  Serial.print(_n0);
  

}

String Phin6::type() {
  return _type;
}

void Phin6::toMidi(int controllerNumber, int channel) {
  if (_counter < switch_wait_time) {
    // do nothing
  }

  else {
    if (_scaled_n0 != _previous_scaled_n0) {
//      Serial.print("unscaled: ");
//      Serial.print(_n0);
//      Serial.print(" - ");
//      Serial.print("(");
//      Serial.print(_typeValueHold);
//      Serial.print(") ");
//      Serial.print(_type);
//      Serial.print("  ");
//      Serial.println(_scaled_n0);
      usbMIDI.sendControlChange(controllerNumber, _scaled_n0, channel);
      _previous_scaled_n0 = _scaled_n0;
    }
  }
}


// Example: Private method for this class
//float Phin6::varCounter() {
//  static int var;
//  ++ var;
//  return var;
//}


