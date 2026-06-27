#include <Adafruit_LiquidCrystal.h>

// Initialize the Tinkercad-native I2C display driver at default index 0
Adafruit_LiquidCrystal lcd(0); 

// Pin Allocations
const byte INTERRUPT_PIN = 2; // Connected to Motor Encoder Channel A
const byte POT_PIN = A0;       // Connected to Potentiometer Center Pin (Wiper)
const byte MOTOR_ENA = 3;      // Connected to L293D Pin 1 (Enable 1,2 - PWM Speed)
const byte MOTOR_IN1 = 9;      // Connected to L293D Pin 2 (Input 1 - Direction)
const byte MOTOR_IN2 = 8;      // Connected to L293D Pin 7 (Input 2 - Direction)

// Interrupt Tracking Variables
volatile unsigned long pulseCount = 0;
unsigned long previousMillis = 0;
const unsigned long calculationWindow = 1000; // Calculate RPM every 1 second (1000ms)

// The standard yellow Tinkercad encoder motor generates roughly 358 pulses per full revolution
const int pulsesPerRevolution = 358; 

void setup() {
  // Configure control and sensor pins
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  
  // Establish fixed motor direction (Forward)
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  
  // Initialize the 16x2 character display grid
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  
  // Attach external hardware interrupt to Pin 2 on falling pulse edge
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), countEncoderPulse, FALLING);
  previousMillis = millis();
}

void loop() {
  // 1. Read the potentiometer value (0 to 1023)
  int potValue = analogRead(POT_PIN);
  
  // 2. Map the value to safe 8-bit PWM duty cycle limits (0 to 255)
  byte pwmValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(MOTOR_ENA, pwmValue);
  
  // 3. Calculate target duty cycle speed percentage for display
  int targetPercentage = map(pwmValue, 0, 255, 0, 100);

  // 4. Run calculations strictly once per second window
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= calculationWindow) {
    
    // Temporarily pause interrupts to safely clone the volatile counter variable
    noInterrupts();
    unsigned long capturedPulses = pulseCount;
    pulseCount = 0; // Clear accumulator for the next 1-second window
    interrupts();
    
    // Convert pulse count data into Rotations Per Minute (RPM)
    float rps = (float)capturedPulses / pulsesPerRevolution;
    unsigned int calculatedRPM = rps * 60;
    
    // 5. Update the LCD Interface
    // Line 1: Target speed set by user
    lcd.setCursor(0, 0);
    lcd.print("Set Speed: ");
    lcd.print(targetPercentage);
    lcd.print("%   "); // Trailing spaces clear old characters
    
    // Line 2: Real-time calculated encoder speed
    lcd.setCursor(0, 1);
    lcd.print("RPM: ");
    lcd.print(calculatedRPM);
    lcd.print("        "); // Trailing spaces clear old characters
    
    previousMillis = currentMillis;
  }
}

// Hardware Interrupt Service Routine (ISR) triggered by Channel A pulses
void countEncoderPulse() {
  pulseCount++;
}
