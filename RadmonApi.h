#ifndef RadmonApi_h
#define RadmonApi_h

#include <Client.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#define RM_API_HOST "www.radmon.org"
#define RM_API_PORT 80

class RadmonApi
{
  public:
    RadmonApi (WiFiClient &client, String username, String password);
    bool postRadmon(int CPM);
	bool postRadmonCity(String city);
	bool postRadmonLatLong(String latitude, String longitude);
	bool postRadmonConvFact(double conversion_factor);
	bool postRadmonDescription(String description);
	bool postRadmonWarning(int warn, int alert);
	bool postRadmonAlarmEnabled(bool expt);

  private:
    WiFiClient *client;
    String _username, _password;
};

#endif