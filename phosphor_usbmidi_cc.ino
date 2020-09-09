/*
 * PHOSPHOR_USBMIDI_CC
 *
 * Created: September 2020
 * Author: Jokubas Verbickas (instagram.com/jokubas.ver)
 * Based on work by: Joris Wegner (joriswegner.de)
 * Libraries used: MIDI Library, USB-MIDI, Sparkfun TLC5904
 * 
 * 
 * Allows control of Phosphor's vactrols using MIDI CC (in this case Akai LPD8 knobs)
 * 
 * Use this together with MIDIberry or other software to connect your MIDI CC controller to Phosphor
 * (Input: your MIDI controller with CC, Output: Phosphor)
 * 
 * Change channels and numbers (ie controller/knob) for your specific MIDI controller (MIDIberry displays this info clearly)
 *
 * 
 * USE THIS DEVICE AT YOUR OWN RISK. Using the original software to create and use patches as well as the recommended
 * parts, the unit should use much less current then a usb port can deliver. The video circuitry should be isolated 
 * well enough from the controller circuit that is connected to the computer. However, I am not responsible for any damage
 * that could occur while using this device.
 *
 */ 

// Init USB-MIDI
#include <USB-MIDI.h>
USBMIDI_CREATE_DEFAULT_INSTANCE();

#include "SparkFun_Tlc5940.h"

int value = 0;

int a = 0; int b = 0; int c = 0; int d = 0; int e = 0; int f = 0;
int g = 0; int h = 0; int i = 0; int j = 0; int k = 0;

int led = 14;


// Receive MIDI CC changes, map them to TLC5940 range and send them over
//
// TLC5940 channels go from 'a' to 'k', but Akai LPD8 only has 8 CC knobs, so we do from 'a' to 'h'
// If needed, add the remaining i, j, k channels.
//
// You can change the map to remove the dead zone for each channel (if, for example, there's no visual change after some point of the knob) or to increase dynamic range
//
// There's probably a cleaner way to do this (only basic programming knowledge here), but it works
void handleControlChange(byte channel, byte number, byte value)
{
    if(channel == 1 && number == 9)
    {
        a = map(value, 0, 127, 0, 4095);
    }

    if(channel == 1 && number == 10)
    {
        b = map(value, 0, 127, 0, 4095);
    }

    if(channel == 1 && number == 11)
    {
        c = map(value, 0, 127, 0, 4095);
    }

    if(channel == 1 && number == 12)
    {
        d = map(value, 0, 127, 0, 4095);
    }

    if(channel == 1 && number == 13)
    {
        e = map(value, 0, 127, 0, 4095);
    }

    if(channel == 1 && number == 14)
    {
        f = map(value, 0, 127, 0, 4095);
    }

    if(channel == 1 && number == 15)
    {
        g = map(value, 0, 127, 0, 4095);
    }

    if(channel == 1 && number == 16)
    {
        h = map(value, 0, 127, 0, 4095);
    }
}

void setup() {
  Tlc.init();
  digitalWrite(led, LOW);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

// Recieve a string of values
void loop() {
    MIDI.read();
    setTlc();
}

// Set the TLC to the transmitted value
void setTlc() {
  digitalWrite(led, HIGH);

  Tlc.set(4,  a);
  Tlc.set(1,  b);
  Tlc.set(5,  c);
  Tlc.set(2,  d);
  Tlc.set(9,  e);
  Tlc.set(11, f);
  Tlc.set(14, g);
  Tlc.set(3,  h);
  Tlc.set(13, i);
  Tlc.set(12, j);
  Tlc.set(10, k);

  Tlc.update();
  digitalWrite(led, LOW);
}
