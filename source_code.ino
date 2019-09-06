/*
  Bike Light

  This code is used to turn on three LEDs in various ways based on the state of the system. The state is determined
  by a button that, when pressed, increments the state of the system.
  States:
      0 - all lights on
      1 - all lights off
      2 - all lights flash quickly
      3 - all lights flash slowly
      4 - lights turn on sequentially in response to microphone input
      5 - lights turn on sequentially without input
*/

//MARK: variables and constants

//variable for reading the button status
short int buttonState = 0;
short int buttonPreviousState = LOW;
//variable for storing the current state of the program
int programState = 0;
//variables for storing the current state of the LEDs
short int ledState[] = {0, 0, 0};
//a variable which stores the inverse value of the current value (not updated continuously)
short int inverseState = 1;
//MARK: variables for time calcualtions
//the current time
unsigned long currentTime = 0;
//the time that the blink program was last run
unsigned long timeLastRun = 0;
//the blinking period for the fast blinking state
const short int fastBlinkInterval = 100;
//the blinking period for the slow blinking state
const short int longBlinkInterval = 1000;
//the waiting period for updating the sequential lights
const short int circusBlinkInterval = 200;
// the waiting period for screaming into the bike light
const short int screamBlinkInterval = 50;
// get the sensor value of the microphone
int micVal = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 11-13 as outputs.
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  // initalize pin 2 as an input from the button
  pinMode(2, INPUT);
  //start text ouput
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  //MARK: Sense
  //update the current time
  currentTime = millis();
  // read the state of the pushbutton value:
  buttonState = digitalRead(2);
  // read the state of the microphone sensor
  micVal = analogRead(A0);

  //MARK: Think
  //Change state
  Serial.print("System State: "); Serial.println(programState);
  switch (programState) {
    case 0 :
      //update the state to turn all the LEDs on
      for (short int i = 0; i < 3; i++) ledState[i] = 1;
      break;
    case 1 :
      //update the state to turn all the LEDs off
      for (short int i = 0; i < 3; i++) ledState[i] = 0;
      break;
    case 2 :
      //applies the desired interval
      if (currentTime - timeLastRun > fastBlinkInterval) {
        //finds the current state of the lights

        //find the inverse of the first light's state
        if (ledState[0] == 0 ) {

          inverseState = 1;
        } else {

          inverseState = 0;
        }
        //set all of the values of the Leds to be the inverse of the first LEDs state
        for (short int i = 0; i < 3; i++) ledState[i] = inverseState;

        //update the time last run for the blinking programs
        timeLastRun = currentTime;
      }
      break;
    case 3 :
      //Applies the desired interval
      if (currentTime - timeLastRun > longBlinkInterval) {
        //finds the current state of the lights

        //find the inverse of the first light's state
        if (ledState[0] == 0 ) {

          inverseState = 1;
        } else {

          inverseState = 0;
        }
        //set all of the values of the Leds to be the inverse of the first LEDs state
        for (short int i = 0; i < 3; i++) ledState[i] = inverseState;

        //update the time last run for the blinking programs
        timeLastRun = currentTime;
      }
      break;
    case 4:
      if (micVal > 0) {
        //applies the desired interval
        if (currentTime - timeLastRun > screamBlinkInterval) {
          //finds the current state of the lights
          for (short int i = 0; i < 3; i++) {
            //if the current light is on
            if (ledState[i] == 1) {
              //turns itself off
              ledState[i] = 0;
              //turns next in line on
              ledState[(i + 1) % 3] = 1;
              break;

              //if all the lights are off
            } else if (i == 2 && ledState[i] == 0 ) {
              //turn on the first light
              ledState[0] = 1;
            }
          }
          timeLastRun = currentTime;
        }
      }
      break;
    case 5:
      //applies the desired interval
      if (currentTime - timeLastRun > circusBlinkInterval) {

        //finds the current state of the lights
        for (short int i = 0; i < 3; i++) {
          //if the current light is on
          if (ledState[i] == 1) {
            //turns itself off
            ledState[i] = 0;
            //turns next in line on
            ledState[(i + 1) % 3] = 1;
            break;

            //if all the lights are off
          } else if (i == 2 && ledState[i] == 0 ) {
            //turn on the first light
            ledState[0] = 1;
          }
        }
        timeLastRun = currentTime;
      }
      break;
    default :
      //reset button state
      programState = 0;
      break;
  }
  //MARK: ACT
  //update the ledstates to be the same as the stored states
  digitalWrite(13, ledState[0]);
  digitalWrite(12, ledState[1]);
  digitalWrite(11, ledState[2]);

  //if the button was just pressed update the program state to the next value
  if (buttonState == HIGH && buttonPreviousState == LOW) {
    programState += 1;
    //say that the previous state of the button was pressed
    buttonPreviousState = HIGH;

    //if the button is not pressed change the previous state to be off.
  } else if (buttonState == LOW) {
    buttonPreviousState = LOW;
  }
}
