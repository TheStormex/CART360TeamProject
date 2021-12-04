// Sightless Dancer Glove

// motor pins
// A - thumb
// B - index finger
// C - middle finger
// D - ring finger
// E - pinky
// F - palm middle
// moves list: 6
// up, down, forward, backwards, left, right
const int motorAPin = 13; 
const int motorBPin = 11;
const int motorCPin = 9;
const int motorDPin = 6;
const int motorEPin = 4;
const int motorFPin = 2;

// accelerometer pins
const int xPin = A1;
const int yPin = A2;
const int zPin = A3;


// start button
const int startPin = 8;

// if the program is started (the button is clicked)
bool started = false;

// the loop: 
// (0) choose action
// (1) give signal
// (2) wait for user actions
// (3) respond if correct

// if the player has done all of the directions correctly this time
bool win = false;

// how many vibration motors are activated for this move
int amount;

// the 5 fingers motor vibration meanings 
// 0, 1, 2, 3, 4 = left, up, forward, down, right

int currentAction = 0;

void setup() {
  // put your setup code here, to run once:
  // set up the pins and their functions
  Serial.begin(57600);
  pinMode(motorAPin, OUTPUT);
  pinMode(motorBPin, OUTPUT);
  pinMode(motorCPin, OUTPUT);
  pinMode(motorDPin, OUTPUT);
  pinMode(motorEPin, OUTPUT);
  pinMode(motorFPin, OUTPUT);
  pinMode(startPin, INPUT); 
  // 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (started == true) {
  // Play Mode
      stopDance();
      // choose the direction
      currentAction = random(0, 6);
      // send the signal
       switch (currentAction) {
          case 0: // thumb - left
            digitalWrite(motorAPin, HIGH);
            break;
          case 1: // index - up
            digitalWrite(motorBPin, HIGH);
            break;
          case 2: // middle - forward
            digitalWrite(motorCPin, HIGH);
            break;
          case 3: // ring - down
            digitalWrite(motorDPin, HIGH);
            break;
          case 4: // pinky - right
            digitalWrite(motorEPin, HIGH);
            break;
          case 5: // palm - backwards
            digitalWrite(motorFPin, HIGH);
            break;
        }        
      stopDance();
      delay(250); // wait a quarter of a second (half a beat) then shut down any and all vibration motors
      stopDance();
      digitalWrite(motorAPin, LOW);
      digitalWrite(motorBPin, LOW);
      digitalWrite(motorCPin, LOW);
      digitalWrite(motorDPin, LOW);
      digitalWrite(motorEPin, LOW);
      digitalWrite(motorFPin, LOW);
      // taking in and seeing if the detected actions of the accelerometer is correct
      // check if the action is correct
      stopDance();
      bool correct = true; // check if correct
      // check current numbers
//      float scaledXOld = mapf(analogRead(xPin), 0, 675, -3, 3);
//      float scaledYOld = mapf(analogRead(yPin), 0, 675, -3, 3);
//      float scaledZOld = mapf(analogRead(zPin), 0, 675, -3, 3);
      Serial.println(analogRead(xPin));
      Serial.println(analogRead(yPin));
      Serial.println(analogRead(zPin));
     int loopsAmount = 250; // so that the final amount of loops * delay time always equals 750
      for (int i = 0; i < 1; i++) { // if there is one or two directions
        correct = false; // set the correct to false so that if during any of the loops it becomes true, it stays true. If it never does, it did not detect the right move
        for (int i2 = 0; i2 < loopsAmount; i2++) { // for many times, check the value of the appropriate pin of the accelerometer. If at least one time the value passes the threshold, it is correct
         float scaledXNew = mapf(analogRead(xPin), 0, 675, -3, 3);
         float scaledYNew = mapf(analogRead(yPin), 0, 675, -3, 3);
         float scaledZNew = mapf(analogRead(zPin), 0, 675, -3, 3);
        switch (currentAction) { // depending on the direction
          case 0: // thumb - left
              if (true) {
               correct = true;
             }
            break;
          case 1: // index - up
              if (true) {
               correct = true;
             }
            break;
          case 2: // middle - forward
              if (true) {
               correct = true;
             }
            break;
          case 3: // ring - down
              if (true) {
               correct = true;
             }
            break;
          case 4: // pinky - right
              if (true) {
               correct = true;
             }
            break;
          case 5: // palm - backwards
              if (true) {
               correct = true;
             }
            break;
          }
        delay(3);
        }
      }
  // Print out scaled X,Y,Z accelerometer readings
      stopDance();
      if (correct == true) { // if the action is correct
        win = true; // the player won this time
      } else if (correct == false) {
        win = false; // the player lost this time
      }
     // giving a response through the C and F / A and E motor pin if the action is correct or incorrect
        if (win) { // if the player won, C and F pins
          digitalWrite(motorCPin, HIGH); // turn on
          digitalWrite(motorFPin, HIGH); // turn on
          stopDance();
          delay(250); // wait for a quarter of a second
          stopDance();
          digitalWrite(motorCPin, LOW); // turn off
          digitalWrite(motorFPin, LOW); // turn off
          delay(750);
          stopDance();
        } else if (!win) { // if the player lost, A and E pins
          digitalWrite(motorAPin, HIGH); // turn on
          digitalWrite(motorEPin, HIGH); // turn on
          stopDance();
          delay(250); // wait for a quarter of a second
          stopDance();
          digitalWrite(motorAPin, LOW); // turn off
          digitalWrite(motorEPin, LOW); // turn off
          delay(750);
          stopDance();
        }

  } else if (started == false) {
    // Waiting Mode
    // when the Arduino is booted up, wait for signal to begin the dance.
        if (digitalRead(startPin) == HIGH) { // if the start button is clicked and that circuit is completed
          for (int i = 0; i < 4; i++) { // give 4 beats (60 bpm) of vibration signals to prepare the user
            // turn on all 6 vibration motors so the user can know if they all work or if one is broken
             digitalWrite(motorFPin, HIGH); // turn on
             digitalWrite(motorAPin, HIGH);
             digitalWrite(motorBPin, HIGH);
             digitalWrite(motorCPin, HIGH);
             digitalWrite(motorDPin, HIGH);
             digitalWrite(motorEPin, HIGH);
             delay(250); // wait for quarter of a second
             digitalWrite(motorFPin, LOW); // turn off
             digitalWrite(motorAPin, LOW);
             digitalWrite(motorBPin, LOW);
             digitalWrite(motorCPin, LOW);
             digitalWrite(motorDPin, LOW);
             digitalWrite(motorEPin, LOW);
             delay(750); // wait for the rest of the second
          }
             started = true; // the dance starts
        }
  }
}

void stopDance() {
// check if the start button is clicked while the dance is happening, to go back to start mode
// this code is peppered all over the loop so the user only needs to hold it for a short period of time
// to stop the program and go back to waiting mode
  if (digitalRead(startPin) == HIGH) {
    for (int i = 0; i < 5; i++) {          
      digitalWrite(motorFPin, HIGH); // turn on
      delay(100);
      digitalWrite(motorFPin, LOW); // turn off
      delay(100);
    }
    started = false;
  }
}

// map float function from https://gist.github.com/nadavmatalon/71ccaf154bc4bd71f811289e78c65918
float mapf(double val, double in_min, double in_max, double out_min, double out_max)
{
   return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
