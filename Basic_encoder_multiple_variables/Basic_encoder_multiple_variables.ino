

/* Based on the original author's example
 * of the library (English):
 * 
 *  Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 * 
 * Some ideas with the code structure and functions 
 * for displaying and deboucing from (Portuguese):
 * 
 * WR Kits Channel: Menu Para Display LCD | Curso de Arduino #029
 * 
 * https://www.youtube.com/watch?v=Swr2Q1IFiBM&list=PLZ8dBTV2_5HSyOXhJ77d-iyt5Z_v_1DPM&index=29&ab_channel=WRKits * 
 * 
 * ---------------------------------------------------------------
 * 
 * You can find this example: 
 * https://github.com/andres-alippi/encoder-multiple-variables
 */

#include <Encoder.h>

#define encoderButton   7   //Encoder button on digital 7

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(5, 6);
//   avoid using pins with LEDs attached

//----------- Aux. Functions Prototypes --------------------------
void selectMenu();     
void updateVars();
void readEncoder(long);

//-------- Global variables --------------------------------------

boolean toggle_button;
int menu = 0;
long var1 = 0, var2 = 0;
String var_selected, displayInfo;

//--------- Setup ------------------------------------------------

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test with multiple variables:");

  pinMode(encoderButton, INPUT_PULLUP);
} // end setup

long oldPosition  = -999;

//--------- Main Loop --------------------------------------------

void loop() {
  selectMenu();
  updateVars();
  
} // end loop

//------- Aux. Functions -----------------------------------------

void selectMenu(){
  if(!digitalRead(encoderButton))
  {
  toggle_button = true;
  delay(1);
  }
  if(digitalRead(encoderButton) && toggle_button)
  {
    toggle_button = false;
    
    menu++;    
    
    if(menu > 1) menu = 0;    
  }
} // end selectMenu

void updateVars(){
  switch(menu){
    case 0:
      var_selected = "var1: ";
      readEncoder(&var1);      
      break;
    case 1:
      var_selected = "var2: ";
      readEncoder(&var2);
      break;
    }
} // end updateVars

void readEncoder(long *var)
{
  myEnc.write(*var);
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;    
    *var = newPosition;
    displayInfo = var_selected + String(*var);
    Serial.println(displayInfo);
  }
  
} // end readEncoder
