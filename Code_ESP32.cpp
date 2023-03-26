#include <FastLED.h>
#include <WiFi.h>
#include "time.h"

//Connexion to the wifi setup off the name and the password
const char* ssid = "WIFI_name";
const char* password = "WIFI_password";

// Take the time information on a server
const char* ntpServer = "pool.ntp.org";
// Setup of the time zone in seconds
const long gmtOffset_sec = 0;
//const long gmtOffset_sec = 3600;

// Setup of the offset daylight
const int daylightOffset_sec = 3600;

// Set Up of the light parameter
const int led = 160;
#define NUM_LEDS 160
#define DATA_PIN 12
const int LED_r= 32;
const int LED_j= 33;
const int LED_v= 25;
//#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];


// Setup for the stepper motor
const int stepPin = 2;
const int dirPin = 15;
const int sleepPin = 16;
const int enablePin = 4;
const int stepsPerRev = 200;
int pulseWidthMicros = 1000;  // microseconds
int millisBtwnSteps = 10000;

int cpt = 0;
int cpt1=0;
void setup() {
  Serial.begin(115200);

  //WiFi.mode(WIFI_STA); //Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  //get time and initialize it
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  //printLocalTime(timeinfo);

  //Unconnect
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

  pinMode(LED_r,OUTPUT);
  pinMode(LED_j,OUTPUT);
  pinMode(LED_v,OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(sleepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  Serial.println(F("A4988 Initialized"));
  int cpt = 0;
  int cpt1=0;
}


//for print all the information on the date and the time
void printLocalTime(tm timeinfo) {
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  //Serial.print("Hour (12 hour format): ");
  //Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}

// function to turn the stepper motor and nurrish fish
void nourish() {
  //turn on the stepper
  Serial.println(F("Distribution of food"));  
  digitalWrite(LED_v, HIGH);

  //wake up the stepper
  digitalWrite(sleepPin, HIGH);
  digitalWrite(enablePin, LOW);
  delay(2000);
  
  digitalWrite(dirPin, LOW);  // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
  for (int i = 0; i < 1 * stepsPerRev; i++) 
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(millisBtwnSteps);
  }
  //turn off the stepper
  digitalWrite(sleepPin,LOW);
  digitalWrite(enablePin, HIGH);
  digitalWrite(LED_v, LOW);
}

//several fonction for turning ON led with different colors
void turn_on() {
  for (int i = 0; i <= led; i++) 
  {
    if (i % 2 == 0) 
    {
      leds[i] = CRGB::Blue;
    } 
    else 
    {
      leds[i] = CRGB::White;
    }
  }
  FastLED.show();
  Serial.println(F("Led turned on"));  
}
void turn_on1() 
{
  for (int i = 0; i <= led; i++) 
  {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  Serial.println(F("Led turned on"));  
}
void turn_on2() {
  for (int i = 0; i <= led; i++) 
  {
    if (i % 2 == 0) 
    {
      leds[i] = CRGB::Red;
    } 
    else 
    {
      leds[i] = CRGB::Green;
    }
