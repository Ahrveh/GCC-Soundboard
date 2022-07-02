
#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"


// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX 5
#define SFX_RX 6

// Connect to the RST pin on the Sound Board
#define SFX_RST 4

// You can also monitor the ACT pin for when audio is playing!

// we'll be using software serial
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

// pass the software serial to Adafruit_soundboard, the second
// argument is the debug port (not used really) and the third 
// arg is the reset pin
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
// can also try hardware serial with
// Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, SFX_RST);
/*
  This code utilizes the Nicohood Library and was built off of the Multi-Singleplayer example
  Use this code at your own risk 
  Code Written by Simple Controllers, modified by Ahvreh Dah
*/

#include "Nintendo.h"

// Change this to what you like right now it is on pin 3 and 4
// I personally use 18 and 19 since it is near the bottom of the Arduino 
CGamecubeController GamecubeController1(7);

// Pin definitions
#define pinLed LED_BUILTIN

void setup()
{
  // Set up debug led
  pinMode(pinLed, OUTPUT);

  ss.begin(9600);

}


void loop()
{
    //Just stops the code if no controller is found
    if (!GamecubeController1.read()) {
      delay(100);
      return;
    }


    // Get the data of controller
    auto r1 = GamecubeController1.getReport();
    Gamecube_Data_t d = defaultGamecubeData;


    //NEW! Zeros the controller on startup
    d.origin = GamecubeController1.getOrigin();
    //Huge thanks to SeanMombo for debugging/figuring this out!

    //Reporting all buttons, sticks, sliders
    d.report.a = r1.a;
    d.report.b = r1.b;
    //Changes X to report Z button
    d.report.x = r1.z;
    d.report.y = r1.y;
    d.report.start = r1.start;
    
    d.report.dleft = r1.dleft;
    d.report.dright = r1.dright;
    d.report.ddown = r1.ddown;
    d.report.dup = r1.dup;

    //Changes Z to report X button
    d.report.z = r1.x;
    
    d.report.r = r1.r;
    d.report.l = r1.l;
    
    d.report.xAxis = r1.xAxis;
    d.report.yAxis = r1.yAxis;
    d.report.cxAxis = r1.cxAxis;
    d.report.cyAxis = r1.cyAxis;
    d.report.left = r1.left;
    d.report.right = r1.right;
    
    //plays the sound effect (uncomment to add a button)
//    if (r1.a == 1) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if (r1.b == 1) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if (r1.x == 1) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if (r1.y == 1) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if (r1.l == 1) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if (r1.r == 1) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if (r1.z == 1) {
//      sfx.playTrack ("YAYUZ   WAV");
//    }
//    else if (r1.cyAxis == 77) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if(r1.cyAxis == 177) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if (r1.cxAxis == 77) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if(r1.cxAxis == 177) {
//      sfx.playTrack ("VINE    WAV");
//    }
//    else if(r1.start == 1) {
//      sfx.playTrack ("MIKEHAZEWAV");
//    }
//      else if (r1.ddown == 1) {
//        sfx.playTrack ("MIKEHAZEWAV");
//      }

    

    // Enable rumble
    if (d.status.rumble) {
      GamecubeController1.setRumble(true);
    }
    else {
      GamecubeController1.setRumble(false);
    }
  }
