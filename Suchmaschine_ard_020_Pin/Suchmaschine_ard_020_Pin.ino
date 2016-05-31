// Sketch for Nils-Florian-Bene Suchmaschine
// Includes Sketches from Adafruit Neopixel 
//
// Version
// 0.01 Basic Test Neopixel & Arcade-Button
// 0.02 TIP120 added, Arcade-Butto Switched/Pulse fixed
// 0.03 NeoPixel Number fixed
// 0.04 Stages Introduced, Interrupt 
// 0.05 Simplified. Removing LED-Scheme – Renamed Suchmaschine_ard
//      Prob: D5 Produces short_circuit
// 0.06 Test module
// 0.07 Adjusting Pins for board
// 0.08 Working with final board – restoring button. 25 LED. added modes for test
// 0.09 improving LED; writing chars
// 0.10 Passing chars to function
// 0.11 Extending Char for LED-Pad. Runs pretty stable.
// 0.12 Preparing for Board
// 0.20 Github_Master
//
// --------------------------------------------------------------------------
//
// Stages
// 01 Idle Mode 
//    LED Blinking slowly
// 02 Calculating ->
//    Going nuts
// 03 Calling for help
//    Bell ringing
// 04 Freibier
//
// --------------------------------------------------------------------------
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
// 
// Debug and run modes
// Set by "mode" integer
// 0 = run (Serial sends rpi-commands), 
// 1 = run (serial serial sends debug),
// 2 = led-Test

int mode = 0;

// --------------------------------------------------------------------------
 

#include <Adafruit_NeoPixel.h>


// Neopixel Declaration
const int neoPin = 13;
const int neoNumber = 25; // Number of neoPixels included on the board

Adafruit_NeoPixel strip = Adafruit_NeoPixel(neoNumber, neoPin, NEO_GRB + NEO_KHZ800);
 
// Arcade Button switch
const int buttonPin = 02;
boolean buttonPressed = false;

//Arcade Button LED
const int pulsePin = 10;
int brightness = 10;
int steps = 3;

// Bell-Transistor
const int bellPin = 4;
const int bellPulse = 10; //millis for ringing

// Rotate-Transistor (Drehteller)
const int rotPin = 5;

// Secret-Transistor
const int secrPin = 3;

     


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // switch declare
  attachInterrupt(digitalPinToInterrupt(buttonPin), ArcadeChange, RISING);

  // open serial for feedback
  Serial.begin(9600); 

  //Button LED Pin
  pinMode(pulsePin, OUTPUT);

  //Secret Pin
  pinMode(secrPin, OUTPUT);

  // Bell-Transistor
  pinMode(bellPin, OUTPUT);

  // Bell-Transistor
  pinMode(rotPin, OUTPUT);

}

void loop() {

  buttonPressed = false; //Reset

// =================================================== 
//                      STAGE 1
// ===================================================

  if (mode == 0) Serial.println("stage 1");
  if (mode == 1) Serial.println("Stage 1. Pulsing LED until Button pressed"); 

  do {
  
    // Arcade Button LED
    
    if (brightness < 3 || brightness > 252) {
      steps = -steps ;
    }
    
    brightness = brightness + steps;
    analogWrite(pulsePin, brightness); 
    delay(50); // Gegens Verschlucken
  
  } while (!buttonPressed && mode < 2); //Wend until button pressed, mode must be "run"
  
  //Button LED Off
  if (mode == 1) Serial.println("Pulse LED Off"); 
  analogWrite(pulsePin, 0);


// =================================================== 
//                      STAGE 2
// ===================================================

  if (mode == 0) Serial.println("stage 2");

  LED_dots(50);

  // start secret pin only in rund mode '0'. Headstart to warm up
  if (mode == 0) { 
    digitalWrite(secrPin, HIGH); 
    if (mode == 1) Serial.println("Secret Pin HIGH"); 
  }


  // bring random nrs. to display
  for (int i = 0; i < 25; i++) {  
    LED_char(random(10), 255, 255, 255, 300); //Expects Nr, r, g, b, delay in ms)
  }

  // Going nuts from here
  
  LED_stripes(15);
  LED_whiteNoise(50); //expects cycles
  LED_colour_noise(50); //expects cycles
  
  LED_pong(5000); //Expects delay after last frame

  
  do {
    void();
  } while (!buttonPressed); //Wend until button pressed, include LED-test-mode 2
  

// =================================================== 
//                      STAGE 3
// ===================================================


    if (mode == 1) Serial.println("Button pressed. Entering 3. Secret pin off. Ring bell"); 
    if (mode == 0) {
      Serial.println("stage 3");
      digitalWrite(secrPin, LOW); //chimney off
    }


    if (mode == 1) Serial.println("Bell pin HIGH"); 

    //Ring bell, but only in run mode

    if (mode == 0) {
      digitalWrite(bellPin, HIGH); 
      delay(500);
      digitalWrite(bellPin, LOW); 
    }

    //Waiting for button to be pressed

    do {
      void();
    } while (!buttonPressed && mode < 2); //Wend until button pressed, mode must be "run"

  
// =================================================== 
//                      STAGE 4
// ===================================================
    
  
    if (mode == 1) Serial.println("Stage 4. Rotate Pin high until button"); 
    if (mode == 0) digitalWrite(rotPin, HIGH); 

        //Waiting for button to be pressed

    do {
      void();
    } while (!buttonPressed && mode < 2); //Wend until button pressed, mode must be "run"
     
    if (mode == 1) Serial.println("Button pressed. Rotate off Re-looping. Stage 1"); 
    if (mode == 0) digitalWrite(rotPin, LOW); 
    
} // ----------- END LOOP ---------------------



//----------------------------------------------------------------------------
//                      Functions for LED handling
//----------------------------------------------------------------------------


void ArcadeChange() {
  buttonPressed = true;
}

// calculate Ord.-Number from x,y

int LED_nr(int lx, int ly) {         
  int number;
  if (((lx + 2) % 2) != 0) ly = 4-ly; // in odd rows, reverse order of y
  number = ( (lx) * 5 + (ly));
  return number;
}

// Clears Screan

void eraseLED() {
  for(int i = 0; i <= neoNumber; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show(); // Write to pixel
  delay(100);
}


//----------------------------------------------------------------------------
//                      Functions for LED handling
//----------------------------------------------------------------------------


void LED_test(){

  for(int x = 0; x <= (neoNumber/5)-1; x++) { 
    for(int y = 0; y <= (neoNumber/5)-1; y ++) {

      strip.setPixelColor(LED_nr(x, y), 0, 255, 0); //LED On        
      strip.show(); // Write to pixel
      Serial.print("Neopixel x: "); 
      Serial.print(x);
      Serial.print(" y: "); 
      Serial.print(y);
      Serial.print(", Nr.:");
      Serial.println(LED_nr(x, y));
      delay(100);
        
      }
    }
}


void LED_pong(int d) {  
  
  int ballDeltaX = 1; // initial direction of ball
  int ballDeltaY = 1; // 
  int ballX[4] = {2, 0, 0, 0}; // ball's cordinates. Array[0] actual, [1-2] older
  int ballY[4] = {0, 0, 0, 0}; //

  eraseLED(); //Call LED erase
  
  for(int f = 0; f <= 22; f++) { //number of frames       

    if (ballX[0] + ballDeltaX > 3 || ballX[0] + ballDeltaX < 1) ballDeltaX = -ballDeltaX;
    if (ballY[0] + ballDeltaY > 4 || ballY[0] + ballDeltaY < 0) ballDeltaY = -ballDeltaY;

    if(f > 18) {
      ballDeltaX = -1; // tweak to let the last ball go off
      ballDeltaY = 1;
    }


    for(int p1 = 2 - int(f / 8); p1 < (5 - int(f / 8)) ; p1++) { //printing paddle 1
        strip.setPixelColor(LED_nr(0, p1), 60, 50 , 20);
        strip.setPixelColor(LED_nr(0, p1+1), 0, 0 , 0); //clean after paddle move
    }

    for(int p2 = 1; p2 < 4; p2++) { //printing paddle 2
        strip.setPixelColor(LED_nr(4, p2), 60, 50 , 20);
    }

    for(int i = 3; i>0; i--) {

      ballX[i] = ballX[i-1]; //Write old positions one register up
      ballY[i] = ballY[i-1]; 

      strip.setPixelColor(LED_nr(ballX[i], ballY[i]), 0, 99 - (i * 33) , 0); //the older, the darker the trace
    
    }

    ballX[0] += ballDeltaX; //Current pos
    ballY[0] += ballDeltaY;

    strip.setPixelColor(LED_nr(ballX[0], ballY[0]), 0, 255 , 0); //the older, the darker the trace
    
    delay(150);
    strip.show(); // Write to pixel  
    
  }

  delay(500);
  eraseLED(); //Call LED erase

  //Game Over
 
  for(int i = 1; i <= 3; i++) { 
    strip.setPixelColor(LED_nr(i,i), 0, 255 , 0);
    strip.setPixelColor(LED_nr(4-i,i), 0, 255 , 0);
  }

  strip.show(); // Write to pixel  
  delay(d);

}



int LED_colour_noise(int cycles) {

  for(int i = 0; i <= cycles; i++) {
    for(int x = 0; x <= neoNumber/5; x++) { 
      for(int y = 0; y <= neoNumber/5; y ++) {
      
          strip.setPixelColor(LED_nr(x, y),random(255), random(255), random(255)); //LED On
          strip.show(); // Write to pixel
        }
      }
      delay(10);
    }
}


int LED_dots(int cycles) {  

   eraseLED(); //Call LED erase

   for(int i = 0; i <= cycles; i++) {
    for(int x = 0; x <= neoNumber/5; x++) { 
      for(int y = 0; y <= neoNumber/5; y ++) {

          if ( (x + y + i) % 2 == 1) {
            strip.setPixelColor(LED_nr(x, y) + 1, 0, 0, 0); //LED off 
          } else {
            strip.setPixelColor(LED_nr(x, y) + 1, 0, 255, 0); //LED On        
          }
  
          
        }
      }
      strip.show(); // Write to pixel
      delay(100);
    
   }
}



int LED_stripes(int cycles) {
   //Writing stripes of random lenght 

   eraseLED(); //Call LED erase
   
   for(int i = 0; i <= cycles; i++) {
    
    int stripe = random(3, 5);
    int pos = 0;
    int rVal = 255;
    
    for(int z = 0; z <= neoNumber; z++) { 

        if (z < stripe + pos) {
           strip.setPixelColor(z, 0, rVal, 0); //LED red
        } else {
          stripe = random(3, 9); //generate new stripe
          pos = z;
          if (rVal == 255) {      // switch red and blck
            rVal = 0;
          } else {
            rVal = 255;
          }
        }

       
        strip.show(); // Write to pixel
      }
      delay(200);
    }
}

int LED_whiteNoise(int cycles) {
   //Writing random grey to each px

   eraseLED(); //Call LED erase
   
   for(int i = 0; i <= cycles; i++) {
    for(int x = 0; x <= neoNumber/5; x++) { 
      for(int y = 0; y <= neoNumber/5; y ++) {

          int val = random(255);
          strip.setPixelColor(LED_nr(x, y), val, val, val); //LED On
        

  
          strip.show(); // Write to pixel
        }
      }
      delay(10);
    }
}

int LED_char(int n,int r,int g,int b, int d) {

  eraseLED();
  byte ch[5];

  switch (n) {
    case 0:
      ch[0] = B00100;
      ch[1] = B01010;
      ch[2] = B01010;
      ch[3] = B01010;
      ch[4] = B00100;
      break;
    case 1:
      ch[0] = B00100;
      ch[1] = B01100;
      ch[2] = B00100;
      ch[3] = B00100;
      ch[4] = B01110;
      break;
    case 2: 
      ch[0] = B01100;
      ch[1] = B00010;
      ch[2] = B00110;
      ch[3] = B01000;
      ch[4] = B01110;
    break;
    case 3:
      ch[0] = B01100;
      ch[1] = B00010;
      ch[2] = B00110;
      ch[3] = B00010;
      ch[4] = B01100;
      break;
    case 4:
      ch[0] = B01010;
      ch[1] = B01010;
      ch[2] = B01110;
      ch[3] = B00010;
      ch[4] = B00010;
      break;
    case 5:
      ch[0] = B01110;
      ch[1] = B01000;
      ch[2] = B01100;
      ch[3] = B00010;
      ch[4] = B01100;
      break;
    case 6:
      ch[0] = B00110;
      ch[1] = B01000;
      ch[2] = B01100;
      ch[3] = B01010;
      ch[4] = B00100;
      break;
    case 7:
      ch[0] = B01110;
      ch[1] = B00010;
      ch[2] = B00100;
      ch[3] = B00100;
      ch[4] = B00100;
      break;
    case 8:
      ch[0] = B00100;
      ch[1] = B01010;
      ch[2] = B00100;
      ch[3] = B01010;
      ch[4] = B00100;
      break;
    case 9:
      ch[0] = B01100;
      ch[1] = B01010;
      ch[2] = B01110;
      ch[3] = B00010;
      ch[4] = B01100;
      break;
  }


  for(int i = 0; i < 5; i++) {          //y-rows
    int converted = (ch[i]);            //convert to integer
        
    for(int j = 0; j <=5 ; j++) {       //x-rows
      int decrement = (5-j);            //backwards
      int pow_pos = pow(2, decrement);  //calc power of 2
      if (decrement > 1) {              // Komisch, aber hoch 2 ergibt sonst Gruetze
        pow_pos = pow_pos + 1;
      }

      if (converted >= pow_pos) {
        converted -= pow_pos;
        strip.setPixelColor(LED_nr(j-1, i), r, g, b); //LED On
      }
    }
  }
  strip.show(); // Write to pixel
  delay(d);    
}

   
