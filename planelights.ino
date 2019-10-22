// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 1;     // previous state of the button
unsigned long previousMillis = 0;
const long interval = 10000;//after this resets to one
const long strobedelay = 50;//


// Landing light settings
#define LL_PIN_LIGHT 3 // Landing light output pin number



// Strobe settings
#define STB_PIN_LIGHT 4 // Pin number for strobe light output
#define STB_PIN_LIGHTB 8 // Pin number for strobe light output
#define STB_BLINK_INTERVAL 20000 // Blink interval for strobe light in microseconds




// Anti-collision beacon settings
#define ACB1_PIN_LIGHT 5 // Pin number for anti-collision beacon 1
#define ACB2_PIN_LIGHT 6 // Pin number for anti-collision beacon 2
#define ACB_FADE_MIN 0 // Minimum fade level for beacon (0-255)
#define ACB_FADE_MAX 255 // Maximum fade level for beacon (0-255)
#define ACB_FADE_INTERVAL 4000 // Fade step interval, in microseconds (lower numbers = faster fade)

unsigned long lastFadeTime = 0;
unsigned long lastStrobeTime = 0;
int currentFade = ACB_FADE_MIN;
int fadeDirection = 1;



void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);


  // Declare output pins
  pinMode(LL_PIN_LIGHT, OUTPUT);
  pinMode(STB_PIN_LIGHT, OUTPUT);
  pinMode(STB_PIN_LIGHTB, OUTPUT);
  pinMode(ACB1_PIN_LIGHT, OUTPUT);
  pinMode(ACB2_PIN_LIGHT, OUTPUT);

// doStrobe(2);
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    buttonPushCounter = 0;
    previousMillis = currentMillis;

  }
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      //Serial.println("on");
      //Serial.print("number of button pushes: ");
      Serial.print ("Mode");
      Serial.println(buttonPushCounter + 1);
    } else {
      // if the current state is LOW then the button went from on to off:
      //Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;



  if (buttonPushCounter  == 4) {
    buttonPushCounter = 0;

  }

  if (buttonPushCounter == 0) {
    digitalWrite(LL_PIN_LIGHT, LOW); //Landing light off
  }
  else {}

  if (buttonPushCounter == 1) {
    digitalWrite(LL_PIN_LIGHT, HIGH); //landing light on
    if ((currentMillis - lastStrobeTime) > STB_BLINK_INTERVAL) {
      doStrobe();
      lastStrobeTime = currentMillis;
    }
  }

  else {}
  if (buttonPushCounter == 2) {
    digitalWrite(LL_PIN_LIGHT, LOW);//Landing light off
    doStrobe();
    if ((currentMillis - lastFadeTime) > ACB_FADE_INTERVAL) {
      if ((currentMillis - lastStrobeTime) > STB_BLINK_INTERVAL) {
        doStrobe();
        lastStrobeTime = currentMillis;
      }
      lastFadeTime = currentMillis;

    }
    else {}
    if (buttonPushCounter == 3) {
      digitalWrite(LL_PIN_LIGHT, HIGH);//Landing light off
      if ((currentMillis - lastStrobeTime) > STB_BLINK_INTERVAL) {
        doStrobe();
        lastStrobeTime = currentMillis;
      }
    }
    else {}
  }
}
// Fade anti-collision LEDs
void doFade() {
 
  currentFade += fadeDirection;
  if (currentFade == ACB_FADE_MAX || currentFade == ACB_FADE_MIN) {
    // If we hit the fade limit, flash the high beacon, and flip the fade direction
    if (fadeDirection == 1) {
      analogWrite(ACB1_PIN_LIGHT, 255);

    } else {
      analogWrite(ACB2_PIN_LIGHT, 255);
    }
    delay(50);
    fadeDirection *= -1;
  }

  analogWrite(ACB1_PIN_LIGHT, currentFade);
  analogWrite(ACB2_PIN_LIGHT, ACB_FADE_MAX - currentFade + ACB_FADE_MIN);
}

// Strobe double-blink
void doStrobe() {
   // while ( count-- )
 for (int i=0; i<=2;i++){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= strobedelay) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (STB_PIN_LIGHT == LOW) {
      digitalWrite(STB_PIN_LIGHT, HIGH);
      digitalWrite(STB_PIN_LIGHTB, HIGH);
    } else {
      digitalWrite(STB_PIN_LIGHT, LOW);
      digitalWrite(STB_PIN_LIGHTB, LOW);
    }
  }}

}
