# RadmonApi

An Arduino library to talk to Radmon.org using [RadmonApi](http://radmon.org/)

## Radmon Username and Password
In order to talk to Radmon,

* Create an account on Radmon.org http://radmon.org/index.php/log-in if not created one already
* Then obtain Radmon.org credentials by posting here: http://radmon.org/index.php/kunena/introduce-yourself
* Wait a few days to obtain your credentials

Fill the obtained Username and Password inside the sketch.

## Using the Library
* Download this GitHub [library](https://github.com/debsahu/RadmonApi/archive/master.zip).
* In Arduino, Goto Sketch -> Include Library -> Add .ZIP Library... and point to the zip file downloaded.

To use in your sketch include these lines.
```
#include <RadmonApi.h>
```
Enter the Radmon.org credentials obtained from the steps listed above
```
// Create an account on Radmon.org first http://radmon.org/index.php/log-in
// Then obtain Radmon.org credentials by posting here: http://radmon.org/index.php/kunena/introduce-yourself
#define UserName "radmon_username" // Radmon.org username
#define PassWord "radmon_password" // Radmon.org pasword
```
Declare clients before setup().
```
WiFiClient ethClient;
RadmonApi api(ethClient, UserName, PassWord);
```
**Include detector location inside setup() **
Mandatory or else wont show up on map.
```
Serial.print("Sending Device Data to Radmon ");
(api.postRadmonCity("State College, USA"))? Serial.print(".") : Serial.print("x");                    // Location in words
(api.postRadmonLatLong("40.803685", "-77.862319"))? Serial.print(".") : Serial.print("x");            // Latitude, Longitude
(api.postRadmonConvFact(conversion_factor))? Serial.print(".") : Serial.print("x");                   // Post Conversion Factor
(api.postRadmonDescription("Geiger counter with J305b tube"))? Serial.print(".") : Serial.print("x"); // Detector Description
(api.postRadmonWarning(50, 100))? Serial.print(".") : Serial.print("x");                              // Warn, Alert                 
(api.postRadmonAlarmEnabled(true))? Serial.print(".") : Serial.print("x");                            // Alarm en/disabled         
Serial.println(" done!");
```
**Post CPM to Radmon.org**
Note that cpm is "int"
```
// cpm is int
(api.postRadmon(cpm)) ? Serial.println("Success!") : Serial.println("Fail:("); 
```