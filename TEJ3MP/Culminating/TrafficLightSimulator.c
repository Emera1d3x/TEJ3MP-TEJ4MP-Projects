/*
Sehan Munir, Rishi Bhargava, Andy Zhang
Mr. Wong
May 10, 2024
This code simulates an traffic light intersection. (Arduino Compatible)
*/

// Importing of necessary libraries
#include <Servo.h>
#include <IRremote.h>

Servo servo;                   // Servo motor
int trigPin = 3;               // Trig pin for ultrasonic sensor
int echoPin = 2;               // Echo pin for ultrasonic sensor
int R_LED_LeftBound = 13;      // Left-most Red LED
int Y_LED_LeftBound = 12;      // Left-most Yellow LED
int G_LED_LeftBound = 11;      // Left-most Green LED
int R_LED_Adjacent = 10;       // Red LEDs with the same timing
int Y_LED_Adjacent = 9;        // Yellow LEDs with the same timing
int G_LED_Adjacent = 8;        // Green LEDs with the same timing
int pedestrianSTOP = 7;        // Red LED used to signal stop for pedestrian stop
int pedestrianGO = 6;          // Green LED used to signal stop for pedestrian stop
bool pedestrianButton = false; // Used to check whetehr button has been pressed
// These integer variables represent extra/less amount of time for a specific moment when in delay
// The program has 6 different moments where there is a delay
// In these intervals, by adjusting the extra variables
// You can change the timing
int extraOne = 0;
int extraTwo = 0;
int extraThree = 0;
int extraFour = 0;
int extraFive = 0;
int extraSix = 0;
int remoteButton = 0;              // Button pressed on remote
unsigned long previousMillis = 0;  // Timer used when ultrasonic sensor distance is > 150 and < 200
int lastPressed = -1;              // Stores last button pressed
unsigned long buttonPressTime = 0; // Timer used when button on remote control is used

// Setup
void setup()
{
    pinMode(trigPin, OUTPUT); // Sets trig pin as output
    pinMode(echoPin, INPUT);  // Sets echo pin as input
    servo.attach(A1);         // Signal for servo motor is A1
    // The next 8 lines are used to set the light LEDS as output
    pinMode(R_LED_LeftBound, OUTPUT);
    pinMode(Y_LED_LeftBound, OUTPUT);
    pinMode(G_LED_LeftBound, OUTPUT);
    pinMode(R_LED_Adjacent, OUTPUT);
    pinMode(Y_LED_Adjacent, OUTPUT);
    pinMode(G_LED_Adjacent, OUTPUT);
    pinMode(pedestrianGO, OUTPUT);
    pinMode(pedestrianSTOP, OUTPUT);
    // Button pin set as input
    pinMode(5, INPUT);
    // Photoresistor is set as input
    pinMode(A0, INPUT);
    // Street light LED is set as output
    pinMode(4, OUTPUT);
    // IR sensor signal is from A2
    IrReceiver.begin(A2);
}

// Used to run LED timings and customDelay
void loop()
{ // The delay is right now on the tinkercad timing version, not the in real life timing version
    // LED control logic
    // The following lines in the method
    // are just a timeline with a custom delay method
    // the custom delay method has an extra variable attached
    // so it can dynamically change as a result of the button
    digitalWrite(R_LED_LeftBound, HIGH);
    customDelay(1000 + extraOne, 1);
    digitalWrite(R_LED_Adjacent, LOW);
    digitalWrite(G_LED_Adjacent, HIGH);
    customDelay(2000 + extraTwo, 2);
    digitalWrite(G_LED_Adjacent, LOW);
    digitalWrite(Y_LED_Adjacent, HIGH);
    customDelay(2000 + extraThree, 3);
    digitalWrite(Y_LED_Adjacent, LOW);
    digitalWrite(R_LED_Adjacent, HIGH);
    customDelay(1000 + extraFour, 4);
    digitalWrite(R_LED_LeftBound, LOW);
    digitalWrite(G_LED_LeftBound, HIGH);
    digitalWrite(pedestrianSTOP, LOW);
    digitalWrite(pedestrianGO, HIGH);
    customDelay(2000 + extraFive, 5);
    digitalWrite(G_LED_LeftBound, LOW);
    digitalWrite(pedestrianGO, LOW);
    digitalWrite(pedestrianSTOP, HIGH);
    digitalWrite(Y_LED_LeftBound, HIGH);
    customDelay(2000 + extraSix, 6);
    digitalWrite(Y_LED_LeftBound, LOW);
}

// Function used to read in ultrasonic sensor distance, whether the
// remote was pressed, and to check whether the button was pressed.
void customDelay(int ms, int identifier)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    unsigned long duration = pulseIn(echoPin, HIGH); // reads in distance from ultrasonic sensor
    long distanceCm = duration * 0.034 / 2 + 30;     // reads ultrasonic sensor distance in cm
    remoteButton = readInfrared();                   // reads remote control button input
    if (remoteButton > -1)
    { // sets lastPressed as the actual button pressed
        lastPressed = remoteButton;
        buttonPressTime = millis(); // sets buttonPressTime to current time
    }
    // This is the polling system main for loop,
    // where it constantly checks for any input to react to
    // and adjusts accordingly
    for (int i = 0; i < ms / 10; i++)
    {
        // Check input for button and adjust accordingly
        pedestrianButton = digitalRead(5);
        if (pedestrianButton == HIGH)
        { // If button is pressed, do delay logic
            if (identifier == 1 || identifier == 2 || identifier == 3 || identifier == 4)
            {
                extraFive = 750;
                if (identifier == 1)
                { // When light is red, put delay amounts according to the instructions
                    extraTwo = -750;
                    extraThree = -750;
                    extraFour = -250;
                }
                else if (identifier == 2)
                { // When light is red, put delay amounts according to the instructions
                    extraThree = -750;
                    extraFour = -250;
                }
                else if (identifier == 3)
                { // When light is red, put delay amounts according to the instructions
                    extraFour = -250;
                }
            }
            else if (identifier == 6)
            { // When light is green, put delay amounts according to the instructions
                extraFive = 750;
                extraOne = -250;
                extraTwo = -750;
                extraThree = -750;
                extraFour = -250;
            }
            else if (identifier == 5)
            { // When light is yellow, put delay amounts according to the instructions
                extraSix = -750;
                extraOne = -250;
                extraTwo = -750;
                extraThree = -750;
                extraFour = -250;
            }
        }

        int sensorValue = analogRead(A0);
        digitalWrite(4, sensorValue > 199 ? HIGH : LOW); // sets street light HIGH when sensor is brought to halfway

        unsigned long currentMillis = millis(); // updates to current time

        if ((distanceCm > 150 && distanceCm < 200))
        {
            currentMillis = millis();
            if (currentMillis - previousMillis >= 2000)
            { // checks how long it has been before turning the motor 60 degrees
                servo.write(60);
            }
            if (currentMillis - previousMillis >= 3500)
            { // lowers the gate after 1.5 seconds
                servo.write(0);
                previousMillis = currentMillis;
            }
        }
        else
        { // lowers gate otherwise
            servo.write(0);
        }
        if (lastPressed >= 0)
        { // checks whether remote button has been pressed
            if (currentMillis - buttonPressTime >= 2000)
            { // checks whether 2 seconds have elapsed
                servo.write(60);
                if (currentMillis - buttonPressTime >= 3500)
                { // lowers after an additional 1.5 seconds
                    servo.write(0);
                    lastPressed = -1;
                }
            }
        }

        delay(ms / 100);
    }
    // This ensures the delays due to button press
    // are emmitted after a "round", so the traffic light
    // loop is back to normal
    if (identifier == 1)
        extraOne = 0;
    else if (identifier == 2)
        extraTwo = 0;
    else if (identifier == 3)
        extraThree = 0;
    else if (identifier == 4)
        extraFour = 0;
    else if (identifier == 5)
        extraFive = 0;
    else if (identifier == 6)
        extraSix = 0;
}

// This function reads in any remote control input and converts it
int mapCodeToButton(unsigned long code)
{
    if ((code & 0x0000FFFF) == 0x0000BF00)
    {
        code >>= 16;
        if (((code >> 8) ^ (code & 0x00FF)) == 0x00FF)
        {
            return code & 0xFF;
        }
    }
    return -1;
}

// Sets button to specfic value and returns the specfic value
int readInfrared()
{
    int result = -1;
    if (IrReceiver.decode())
    {
        unsigned long code = IrReceiver.decodedIRData.decodedRawData;
        result = mapCodeToButton(code);
        IrReceiver.resume();
    }
    return result;
}