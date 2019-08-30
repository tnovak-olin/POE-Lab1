/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
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
//the blinking period
const short int interval = 100;


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
  Serial.println("---------------------------------");
  Serial.print("button: ");
  Serial.println(buttonState);
  Serial.print ("LED: ");
  Serial.println(programState);
  //MARK: Sense
  //update the current time
  currentTime = millis();
  // read the state of the pushbutton value:
  buttonState = digitalRead(2);

  //MARK: Think
  //Change state
  switch (programState) {
    case 0 :
      Serial.println("running case 0");
      //update the state to turn all the LEDs on
      for (short int i = 0; i < 3; i++) ledState[i] = 1;
      break;
    case 1 :
      Serial.println("running case 1");
      //update the state to turn all the LEDs off
      for (short int i = 0; i < 3; i++) ledState[i] = 0;
      break;
    case 2 :
      if (currentTime - timeLastRun > interval) {
        Serial.println("running case 2");
        //finds the current state of the lights

        //find the inverse of the first light's state
        if (ledState[0] == 0 ){
          
          inverseState = 1;
        }else{
          
          inverseState = 0;
        }
        //set all of the values of the Leds to be the inverse of the first LEDs state
        for (short int i = 0; i < 3; i++) ledState[i] = inverseState;
      }
      break;
    default :
      Serial.println("case 3 default");
      //reset button state
      programState = 0;
      break;
  }
  //MARK: ACT
  //update the ledstates to be the same as the stored states
  digitalWrite(13, ledState[0]);
  digitalWrite(11, ledState[1]);
  digitalWrite(12, ledState[2]);

  //if the button was just pressed update the program state to the next value
  if (buttonState == HIGH && buttonPreviousState == LOW) {
    Serial.println("incremented");
    programState += 1;
    //say that the previous state of the button was pressed
    buttonPreviousState = HIGH;

    //if the button is not pressed change the previous state to be off.
  }else if (buttonState == LOW){
    buttonPreviousState = LOW;
  }


  /*digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);// turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);// turn the LED off by making the voltage LOW
    delay(1000);  */
}
