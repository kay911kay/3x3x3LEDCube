/*
Author: Daniel Wang
Objective: Attempt to multiplex and create colorful LED functions
Chip: ATMEGA2560;
LEDCUBE: 3x3x3
*/
int ledLayers[] = {24,26,28};
int ledPins[] = {13,12,11,10,9,8,7,6,5}; //left to right array
int ledPinsRotate[] = {13,12,11,10,7,6,5,8,9}; //spiral array specifically made for rotating wall #4, pins will change
int routine = 6; // the number of the routine to be played from 1 to 7
int randLayer; //the random layer pin number generated from 1-3
int randPin; //the random pin number generated from 1-9
void setup(){
  for (int i = 0; i<3; i++){ //declares the entire layer as an output
    pinMode(ledLayers[i], OUTPUT);
  }
  for (int x = 0; x<9; x++){ //declares the entire row of pins 1-9 as an output
    pinMode(ledPins[x], OUTPUT);
  }
  for (int j = 0; j<9; j++){  //declares the special spiral array as an output
    pinMode(ledPinsRotate[j], OUTPUT); 
  }
  Serial.begin(9600); 
  randomSeed(analogRead(0));  // used to generate a random number by using the analog pin
  
}

void loop(){

  
 RoutineSix();
  
}

void RoutineOne(){ //Light up each horizontal level and pulse them up and down 3 times
  for(int g = 0; g<3; g++){ 
    for (int h = 0; h<9; h++){  //sets an entire row of pins to ON or HIGH
    digitalWrite(ledPins[h], HIGH);
  }
for (int i = 0; i<3; i++){ //sets every layer to off at the start of the loop and then specifically turns one on and does it 3 times
  for (int g = 0; g<3; g++){
    digitalWrite(ledLayers[g], HIGH);
  } 
  delay(1000); 
  digitalWrite(ledLayers[i],LOW);
  delay(1000);
  } 
 for (int t = 1; t> 0; t--){ 
  for (int k = 3; k>0; k--){
  digitalWrite(ledLayers[k], HIGH);
  } 
  delay(1000); 
  digitalWrite(ledLayers[t],LOW);
  delay(1000);
  }
  }
}


void RoutineTwo(){ //Light up each vertical level and pulse them left to right 3 times
int pin1 = 0; //declares the following pin locations in the array
int pin2 = 1;
int pin3 = 2;
int pinBack1 = 6; //declares the following pin locations in the array
int pinBack2 = 7;
int pinBack3 = 8;
for (int h=0; h<3; h++){ //turns all layers on
  digitalWrite(ledLayers[h], LOW);
}  
for (int i = 0; i<3; i++){ //makes the pins turn on to the right
  digitalWrite(ledPins[pin1], HIGH); 
  digitalWrite(ledPins[pin2], HIGH);
  digitalWrite(ledPins[pin3], HIGH); 
  delay(1000); 
  digitalWrite(ledPins[pin1], LOW); 
  digitalWrite(ledPins[pin2], LOW);
  digitalWrite(ledPins[pin3], LOW);  
 pin1 = pin1 +3; //this allows it so that we can turn on the next set of pins so pins 1,4,7
 pin2 = pin2 +3; //pins 2,5,8
 pin3 = pin3 +3; //pins 3,6,9
}

for (int i = 0; i<3; i++){ //does what the above does but in backwards mode so moving from right ot left and using pinback 
  digitalWrite(ledPins[pinBack1], HIGH);
  digitalWrite(ledPins[pinBack2], HIGH);
  digitalWrite(ledPins[pinBack3], HIGH);
  delay(1000);
  digitalWrite(ledPins[pinBack1], LOW); 
  digitalWrite(ledPins[pinBack2], LOW);
  digitalWrite(ledPins[pinBack3], LOW);    
  pinBack1 = pinBack1 - 3;
  pinBack2 = pinBack2 - 3;
  pinBack3 = pinBack3 - 3;
}
}

void RoutineThree(){//starburst, start with the middle led lit and burst the led's outward to the corners
  digitalWrite(ledLayers[0], HIGH); 
  digitalWrite(ledLayers[2], HIGH);
  digitalWrite(ledLayers[1], LOW);
  for(int i = 0; i<9; i++){
    digitalWrite(ledPins[i], LOW); 
  }  
 digitalWrite(ledPins[4], HIGH); //the 6 lines above this allow it so that we start off with only the middle led on
 delay(1000);
  //does this loop 100x to quickly switch beetween on and off so that the middle led can appear to be off
 for (int g = 0; g<3; g++){ 
   digitalWrite(ledLayers[g], LOW);
 }
 for (int z = 0; z<9; z++){
   digitalWrite(ledPins[z], HIGH);
   digitalWrite(ledPins[4], LOW);
 } // the code above this turns on everything but the leds above and below the middle
   digitalWrite(ledLayers[0],LOW);
   digitalWrite(ledLayers[1],HIGH);
   digitalWrite(ledLayers[2],LOW); 
   for (int y = 0; y<9; y++){
     digitalWrite(ledPins[y], HIGH);
     
   }
  delay(1000);   //this code up until the delay turns on everything but the leds side by side to the middle led.
}



void RoutineFour(){ //rotating wall, from the center, light up a wall and rotate it in a direction for 3 revolutions
//this entire loop uses the special array designed in a spiral to make this easier
    for (int i = 0; i <3; i++){

  int h = 6; //pins h and t set the line in a diagonal position
  int t = 2;
  digitalWrite(ledLayers[0], LOW); //turns all the layers on
  digitalWrite(ledLayers[1], LOW);
  digitalWrite(ledLayers[2], LOW);
  digitalWrite(ledPinsRotate[8],HIGH); //pin 9 the middle pin of the spiral is always on
  
    for (int x = 0; x<9; x++){ //lights up the h and t pins
      digitalWrite(ledPinsRotate[h], HIGH);
      digitalWrite(ledPinsRotate[t], HIGH);
      delay(1000);
      digitalWrite(ledPinsRotate[h], LOW); //turns off the h and t pins
      digitalWrite(ledPinsRotate[t], LOW);
      h = h++; //add one to both pins which are in the opposite direction of each other
      t = t++;
      if (t == 8){ //because there is no rotating into pin 9, if t or h is added up to 9 reset whichever back to 1
        t = 0;
      }
      if (h == 8){
        h = 0;
      }
    }
  }  
}

void RoutineFive(){ //randomly light up a single led for a total of 50 times - STAR TWINKLE.
    randPin = random(9); //generates a random number from 0 to 9
    randLayer = random(3); //generates a random number from 0 to 3
  for (int i = 0; i<50; i++){ // will do everything within the loop 50x
    digitalWrite(ledLayers[0], HIGH); 
    digitalWrite(ledLayers[1], HIGH);
    digitalWrite(ledLayers[2], HIGH);
    for (int z = 0; z<9; z++){ //turns all the pins to off
      digitalWrite(ledPins[z], LOW); 
    }
    digitalWrite(ledPins[randPin], HIGH); //turns on only the randomly generated number pins
    digitalWrite(ledLayers[randLayer], LOW);
    delay(50);
  } 
}

void RoutineSix(){ //Count up/down, light up each led one at a time from the bottom to top and back
 
 for (int x = 0; x<3; x++){ //turns off every pin and turns on the x pin, which increases to the next everytime the loop is completed.
  digitalWrite(ledLayers[1], HIGH);
  digitalWrite(ledLayers[2], HIGH);
  digitalWrite(ledLayers[3], HIGH);
  digitalWrite(ledLayers[x], LOW);
  
  for (int i = 0; i<9; i++){ // turns off every ledPins pin and turns on only the i pin.
    for (int k = 0; k<9; k++){
      digitalWrite(ledPins[k], LOW);
    }
    digitalWrite(ledPinsRotate[i], HIGH);
    delay(1000);
    digitalWrite(ledPinsRotate[i], LOW);
  }
  digitalWrite(ledLayers[x], HIGH);
}


 for (int x = 2; x>=0; x--){ //turns off every pin and turns on the x pin, which increases to the next everytime the loop is completed.
  digitalWrite(ledLayers[1], HIGH);
  digitalWrite(ledLayers[2], HIGH);
  digitalWrite(ledLayers[3], HIGH);
  digitalWrite(ledLayers[x], LOW);
  
  for (int i = 8; i>=0; i--){ // turns off every ledPins pin and turns on only the i pin.
    for (int k = 0; k<9; k++){
      digitalWrite(ledPins[k], LOW);
    }
    digitalWrite(ledPinsRotate[i], HIGH);
    delay(1000);
    digitalWrite(ledPinsRotate[i], LOW);
    
  }
  digitalWrite(ledLayers[x], HIGH);
}
}


