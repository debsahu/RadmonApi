#include "RadmonApi.h"

RadmonApi::RadmonApi(WiFiClient &client, String username, String password)	{
	this->client = &client;
	_username = username;
	_password = password;
}

bool RadmonApi::postRadmon(int CPM) {
  if(client->connected()) {client->flush(); client->stop();} 
  if (client->connect(RM_API_HOST, RM_API_PORT)) {
    client->print("GET /radmon.php?function=submit&user="); 
    client->print(_username); client->print("&password="); 
    client->print(_password); client->print("&value="); 
    client->print(String(CPM)); 
    client->print("&unit=CPM"); 
    client->println(" HTTP/1.0"); 
    client->println("HOST: radmon.org"); 
    client->println();
	return true;
  } else {
    return false;
  }
}

bool RadmonApi::postRadmonCity(String city) {
  if(client->connected()) {client->flush(); client->stop();} 
  if (client->connect(RM_API_HOST, RM_API_PORT)) {
    client->print("GET /radmon.php?function=updatelocation&user="); 
    client->print(_username); client->print("&password="); 
    client->print(_password); client->print("&location="); 
    client->print(city); 
    client->println(" HTTP/1.0"); 
    client->println("HOST: radmon.org"); 
    client->println();
	return true;
  } else {
    return false;
  }
}

bool RadmonApi::postRadmonLatLong(String latitude, String longitude) {
  if(client->connected()) {client->flush(); client->stop();} 
  if (client->connect(RM_API_HOST, RM_API_PORT)) {
    client->print("GET /radmon.php?function=setlatitudelongitude&user="); 
    client->print(_username); client->print("&password="); 
    client->print(_password); client->print("&latitude="); 
    client->print(latitude); // Latitude DD.dddddd
    client->print("&longitude="); 
    client->print(longitude);  // Longitude DD.dddddd
    client->println(" HTTP/1.0"); 
    client->println("HOST: radmon.org"); 
    client->println();
	return true;
  } else {
    return false;
  }
}

bool RadmonApi::postRadmonConvFact(double conversion_factor) {
  if(client->connected()) {client->flush(); client->stop();} 
  if (client->connect(RM_API_HOST, RM_API_PORT)) {
    client->print("GET /radmon.php?function=setconversionfactor&user="); 
    client->print(_username); client->print("&password="); 
    client->print(_password); client->print("&value="); 
    client->print(String(conversion_factor,5));
    client->println(" HTTP/1.1"); 
    client->println("HOST: radmon.org"); 
    client->println();
	return true;
  } else {
    return false;
  }
}

bool RadmonApi::postRadmonDescription(String description) {
  if(client->connected()) {client->flush(); client->stop();} 
  if (client->connect(RM_API_HOST, RM_API_PORT)) {
    client->print("GET /radmon.php?function=updatedescription&user="); 
    client->print(_username); client->print("&password="); 
    client->print(_password); client->print("&description="); 
    client->print(description);
    client->println(" HTTP/1.0"); 
    client->println("HOST: radmon.org"); 
    client->println();
    return true;	
  } else {
    return false;
  }
}

bool RadmonApi::postRadmonWarning(int warn, int alert) {
  if(client->connected()) {client->flush(); client->stop();} 
  if (client->connect(RM_API_HOST, RM_API_PORT)) {
    client->print("GET /radmon.php?function=setwarnalert&user="); 
    client->print(_username); client->print("&password="); 
    client->print(_password);
    client->print("&warn=");
    client->print(String(warn));
    client->print("&alert=");
    client->print(String(alert));
    client->println(" HTTP/1.0"); 
    client->println("HOST: radmon.org"); 
    client->println();
	return true;
  } else {
    return false;
  }
}

bool RadmonApi::postRadmonAlarmEnabled(bool expt) {
  if(client->connected()) {client->flush(); client->stop();} 
  if (expt) {
    if (client->connect(RM_API_HOST, RM_API_PORT)) {
      client->print("GET /radmon.php?function=setalertsdisabled&user="); 
      client->print(_username); client->print("&password="); 
      client->print(_password);
      client->println(" HTTP/1.0"); 
      client->println("HOST: radmon.org"); 
      client->println();
	  return true;
    } else {
      return false;
    }
  } else {
    if (client->connect(RM_API_HOST, RM_API_PORT)) {
      client->print("GET /radmon.php?function=setalertsenabled&user="); 
      client->print(_username); client->print("&password="); 
      client->print(_password);
      client->println(" HTTP/1.0"); 
      client->println("HOST: radmon.org"); 
      client->println();
	  return true;
    } else {
      return false;
    }
  }
}