#include <ESP8266WiFi.h>
#include <RadmonApi.h>
//#include "secret.h"                  // (uncomment/comment) if (using/not using) a secret.h header with predefined declarations of secrets

//////////////////////// Config Begin ////////////////////////
double conversion_factor = 0.00812;  // J305b from https://www.cooking-hacks.com/documentation/tutorials/geiger-counter-radiation-sensor-board-arduino-raspberry-pi-tutorial#cpm_to_servants
const int inputPin = D3;             // Pin to detect signals
bool postrad = true;                 // If post to Radmon.org

#ifndef mySSID
  #define mySSID "wifi_ssid"         // WiFi SSID
#endif
#ifndef myPASSWORD
  #define myPASSWORD "wifi_pwd"      // WiFi Password
#endif
// Create an account on Radmon.org first http://radmon.org/index.php/log-in
// Then obtain Radmon.org credentials by posting here: http://radmon.org/index.php/kunena/introduce-yourself
#ifndef UserName
  #define UserName "radmon_username" // Radmon.org username
#endif
#ifndef PassWord
  #define PassWord "radmon_password" // Radmon.org pasword
#endif
///////////////////////// Config Done /////////////////////////

WiFiClient ethClient;
RadmonApi api(ethClient, UserName, PassWord);

#define LOG_PERIOD 20000             // Logging period in milliseconds
#define MINUTE_PERIOD 60000          // 1 min in ms
#define WIFI_TIMEOUT_DEF 30          // WiFi TimeOut

volatile unsigned long counts = 0;   // Tube events
unsigned long cpm = 0;               // CPM
unsigned long previousMillis;        // Time measurement

void ISR_impulse() { // Captures count of events from Geiger counter board
  counts++;
}

void setup() {
  Serial.begin(115200);
 
  Serial.print("\nConnecting to ");
  Serial.print(mySSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(mySSID, myPASSWORD);
  int wifi_loops=0;
  while (WiFi.status() != WL_CONNECTED) {
    wifi_loops++;
    Serial.print(".");
    delay(500);
    if (wifi_loops > (int) WIFI_TIMEOUT_DEF) ESP.restart();
  }
  Serial.println("connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  // Radmon.org stuff
  if (postrad){
    // Online Stuff
    Serial.print("Sending Device Data to Radmon ");
    (api.postRadmonCity("State College, USA"))? Serial.print(".") : Serial.print("x");                     // Location in words
    (api.postRadmonLatLong("40.803685", "-77.862319"))? Serial.print(".") : Serial.print("x");             // Latitude, Longitude
    (api.postRadmonConvFact(conversion_factor))? Serial.print(".") : Serial.print("x");                    // Post Conversion Factor
    (api.postRadmonDescription("Geiger counter with J305b tube"))? Serial.print(".") : Serial.print("x");  // Detector Description
    (api.postRadmonWarning(50, 100))? Serial.print(".") : Serial.print("x");                               // Warn, Alert                 
    (api.postRadmonAlarmEnabled(true))? Serial.print(".") : Serial.print("x");                             // Alarm en/disabled         
    Serial.println(" done!");
  } 
  pinMode(inputPin, INPUT);    //     Attaching Interupt                   // Set pin for capturing Tube events
  interrupts();                                                            // Enable interrupts
  attachInterrupt(digitalPinToInterrupt(inputPin), ISR_impulse, FALLING);  // Define interrupt on falling edge
  //attachInterrupt(digitalPinToInterrupt(inputPin), ISR_impulse, RISING);
}

void loop() {  
  if (WiFi.status() != WL_CONNECTED) ESP.restart();

  if (millis() - previousMillis > LOG_PERIOD) {
    previousMillis = millis();
    cpm = counts * MINUTE_PERIOD / LOG_PERIOD;
    Serial.print("Counts/min: ");
    Serial.print(cpm);
    Serial.print(" Counts: ");
    Serial.print(counts);
    Serial.println();
    counts = 0;
    if(postrad) { 
      (api.postRadmon(cpm)) ? Serial.println("Success!") : Serial.println("Fail:("); 
    }
  }
}