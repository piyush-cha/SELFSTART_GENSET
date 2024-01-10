#include <ESP32Servo.h>
#include <WiFi.h>
#define ACCEPT_TYPE "text/csv"
int x=0;
int y = 0;
#include <HTTPClient.h>
WiFiClient client;

Servo myServo;  // Create a servo object

const int relayPin = 32;  // GPIO pin connected to the relay

//______________________________________________________________________


const char* ssid = "Sid";
const char* password = "qazwsxedc";

const char* host = "thingworx.scetngp.com";
const int httpsPort = 80;
//THING-PROP  DCS_SMART_POWER_SWITCH_V1.0
const char Thing[] = "SELF-START(GENSET)thing";

const char get_Property1[] = "Button";

const char appKey[] = "b2ce6fb5-c76e-4085-8aa0-192d7f26e183";

String Get(String get_Thing, String get_Property)
{
  HTTPClient http;
  int httpCode = -1;
  String fullRequestURL = "http://" + String(host) + ":" + String(httpsPort) + "/Thingworx/Things/"
                          + get_Thing + "/Properties/" + get_Property + "?appKey=" + appKey;

  Serial.println(fullRequestURL);
  http.begin(client, fullRequestURL);
  http.addHeader("Accept", ACCEPT_TYPE, false, false);
  httpCode = http.GET();
  Serial.println(httpCode);

  String responses;
  if (httpCode > 0)
  {
    responses = http.getString();
    //Serial.println(responses);
    //Serial.print(responses[9]);
  }
  else
  {
    Serial.printf("[httpGetPropertry] failed, error: %s\n\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  return responses;
}


void setup() {
  myServo.attach(26);  // Attach the servo to pin 9
  pinMode(relayPin, OUTPUT);  // Set relay pin as output
  //--------------------------------------------------------

  Serial.begin(115200);

  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //-------------------------------------------------------------
}

void loop() {


  //Get();
  //------------------------------------------------------------get-----------------
   //Get(Thing,Property2);


  String res = Get(Thing, get_Property1);
  Serial.print(" GET DATA.......................");
  Serial.print(res);
  Serial.println(res[11]);
  if ( (res[11] == 'f')&& (x == 0)) {
    for (int angle = 0; angle <= 180; angle++) {
      myServo.write(angle);  // Set servo position
      delay(15);             // Wait for the servo to reach the position
    }

    digitalWrite(relayPin, HIGH);  // Turn on the relay
    delay(1000);  // Pause for 1 second
x=1;y=0;

  }
  else if ((res[11] == 't') && (y == 0) )
  {
    for (int angle = 180; angle >= 0; angle--) {
      myServo.write(angle);  // Set servo position
      delay(15);             // Wait for the servo to reach the position
    }
x=0;y=1;
    digitalWrite(relayPin, LOW);  // Turn off the relay
    delay(1000);  // Pause for 1 second

  }







  Serial.println();
  delay(2000);
}


/*String Get(String get_Thing, String get_Property)
{
  HTTPClient http;
  int httpCode = -1;
  String fullRequestURL = "http://" + String(host) + ":" + String(httpsPort) + "/Thingworx/Things/"
                          + get_Thing + "/Properties/" + get_Property + "?appKey=" + appKey;

  Serial.println(fullRequestURL);
  http.begin(client, fullRequestURL);
  http.addHeader("Accept", ACCEPT_TYPE, false, false);
  httpCode = http.GET();
  Serial.println(httpCode);

  String responses;
  if (httpCode > 0)
  {
    responses = http.getString();
    //Serial.println(responses);
    //Serial.print(responses[9]);
  }
  else
  {
    Serial.printf("[httpGetPropertry] failed, error: %s\n\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  return responses;
}*/
