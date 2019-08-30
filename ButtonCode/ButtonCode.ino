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

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int ledState = 0;

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
  Serial.println(ledState);
  //MARK: Sense
  // read the state of the pushbutton value:
  buttonState = digitalRead(2);

  //MARK: Think
  //Change state
  switch (ledState) {
    case 0 :
      Serial.println("running case 0");
      //all on
      //turn on leds
      digitalWrite(13, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      break;
    case 1 :
      Serial.println("running case 1");
      //all off
      //turn off leds
      digitalWrite(13, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      break;
    case 2 :
      Serial.println("running case 2");
      //all blinking
      //leds on
      digitalWrite(13, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      //wait
      delay(1000);
      //leds off
      digitalWrite(13, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      //wait
      delay(1000);
      break;
    default :
      Serial.println("case 3 default");
      //reset button state
      ledState = 0;
      break;
  }

  if (buttonState == HIGH) {
    Serial.println("incremented");
    ledState += 1;
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
