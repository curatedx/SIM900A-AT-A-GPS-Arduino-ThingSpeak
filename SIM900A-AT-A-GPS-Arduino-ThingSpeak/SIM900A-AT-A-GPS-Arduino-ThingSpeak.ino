#include <SoftwareSerial.h>
/* Create object named SIM900 of the class SoftwareSerial */
SoftwareSerial SIM900(8, 7);

#define APN "UPDATE_YOUR_APN_HERE"
#define ThingSpeak_URL "api.thingspeak.com/update"

String ThingSpeak_api_key = "YOUR_THINGSPEAK_API_KEY";

//For now location coordinates are hard coded, but in the serial monitor you get actual coordinates.
// I'll extract location data using a seperate function and update code.

String latitude = "100.354848";
String longitude = "92.221402";

String HTTP_POST_DATA = "api_key=" + ThingSpeak_api_key + "&field1=" + latitude + "&field2=" + longitude;

int DELAY_VALUE = 5000;

void setup() {
  Serial.begin(9600);
  SIM900.begin(9600);

}

void loop() {

  SIM900.println("Starting in 5 sec...");
  delay(DELAY_VALUE);
  
  gsm_http_post();
  delay(DELAY_VALUE);

}

void gsm_http_post() {

  SIM900.println("AT");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+CGATT?");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+SAPBR=3,1,\"APN\",\"" + String(APN) + "\"");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+SAPBR=1,1");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+SAPBR=2,1");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+CIPGSMLOC=1,1");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+CIPGSMLOC=2,1");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+HTTPINIT");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+HTTPPARA=\"CID\",1");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+HTTPPARA=\"URL\",\"" + String(ThingSpeak_URL) + "\"");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+HTTPDATA=" + String(HTTP_POST_DATA.length()) + ",10000");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println(HTTP_POST_DATA);
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  SIM900.println("AT+HTTPACTION=1");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);

  //Terminate HTTP & GPRS and then switch off
  SIM900.println("AT+HTTPTERM");
  send_to_serial();//Print GSM Status an the Serial Output;
  delay(DELAY_VALUE);
}


//Print GSM Status
void send_to_serial() {
  while (SIM900.available() != 0) { /* If data is available on serial port */
    Serial.write(char (SIM900.read()));  /* Print character received on to the serial monitor */
  }

}

//Extract Location Coordinates from AT Command response
void extract_data() {

}
