#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 2              //Here, we have defined the ports to which we will connect our LEDs 
#define greenpin 3
#define bluepin 4
#define led1 5
#define led2 6
#define led3 7
#define led4 8
#define led5 9
#define led6 10
#define led7 11
#define led8 12
#define mainled 13

// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //importing library 




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(mainled, HIGH); //this turns the blue LED on 

  //Serial.println("Color View Test!");

  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32) //Setting up of the RGB sensor
  ledcAttachPin(redpin, 1);
  ledcSetup(1, 12000, 8);
  ledcAttachPin(greenpin, 2);
  ledcSetup(2, 12000, 8);
  ledcAttachPin(bluepin, 3);
  ledcSetup(3, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    //Serial.println(gammatable[i]);
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  float red, green, blue; //
  
  tcs.setInterrupt(false);  // turn on LED

  delay(50);  // takes 50ms to read 

  tcs.getRGB(&red, &green, &blue); //gets RGB values 

  Serial.print("\tG%:\t"); Serial.print(int((green/255)*100)); // this prints the percentage of green light 

  Serial.print("\tR:\t"); Serial.print(int(red)); //prints red light from 0 to 255
  Serial.print("\tB:\t"); Serial.print(int(blue)); //prints blue light from 0 to 255
  Serial.print("\tG:\t"); Serial.println(int(green)); //prints green light from 0 to 255
  tcs.setInterrupt(true);  // turn off LED
  

  if(int(green) == 0){ //if green light = 0, 0 LEDs turn on
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    
  }
  else if(int(green) > 0 &&  int(green) <= 31.875){ //if green light in range (0, 31.875], 1 LED turns on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
  }
  else if(int(green) > 31.875 &&  int(green) <= 63.75){ //if green light in range (31.875,63.75], 2 LEDs turn on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
  }
  else if(int(green) > 63.75 &&  int(green) <= 95.625){ //if green light in range (63.75, 95.265], 3 LEDs turn on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
  }
  else if(int(green) > 95.625 &&  int(green) <= 127.5){ //if green light in range (95.265,127.5], 4 LEDs turn on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
  }
  else if(int(green) > 127.5 &&  int(green) <= 159.375){ //if green light in range (127.5, 159.375], 5 LEDs turn on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
  }
  else if(int(green) > 159.375 &&  int(green) <= 191.25){ //if green light in range (159.375, 191.25], 6 LEDs turn on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
  }
  else if(int(green) > 191.25 &&  int(green) <= 223.125){ //if green light in range (191.25, 223.125], 7 LEDs turn on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, LOW);
  }
  else if(int(green) > 223.125 &&  int(green) <= 255){ //if green light in range (223.125, 255], 8 LEDs turn on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, HIGH);
  }
  else{
    digitalWrite(led1, HIGH); //else, alternating LEDs will turn on to inform that there is some problem w the reading for green light 
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, LOW);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, LOW);
  }

  

}
