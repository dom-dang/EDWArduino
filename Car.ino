#include <WiFi101.h>
#include <string.h>  //used for some string handling and processing.
//#include <LiquidCrystal.h>
//const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int status = WL_IDLE_STATUS;
WiFiServer server(80);

const int RESPONSE_TIMEOUT = 6000; //ms to wait for response from host
const int GETTING_PERIOD = 5000; //periodicity of getting a number fact.
const uint16_t IN_BUFFER_SIZE = 1000; //size of buffer to hold HTTP request
const uint16_t OUT_BUFFER_SIZE = 1000; //size of buffer to hold HTTP response
char request_buffer[IN_BUFFER_SIZE]; //char array buffer to hold HTTP request
char response_buffer[OUT_BUFFER_SIZE]; //char array buffer to hold HTTP response

char output[1000];

const uint8_t button_pin = 7;
const uint8_t button_pin2 = 6;

#define in1 0
#define in2 1
#define in3 4
#define in4 5


uint8_t drive;

uint8_t state;
#define REST 0
#define RIGHT 1
#define LEFT 2
#define BOTH 3

uint8_t id = 13; //TEAM ID


char network[] = "NAMY2.4";  //SSID CHANGE!!
char password[] = "QuynhThy9605!"; //Password for WiFi CHANGE!!!


void setup() {
  Serial.begin(115200); //for debugging if needed.
  delay(50); //pause to make sure comms get set up
  analogWrite(A3, 0);

 Serial.print("WiFi101 shield: ");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NOT PRESENT");
    return; // don't continue
  }
  Serial.println("DETECTED");
  Serial.println(WL_CONNECTED);
  uint8_t count = 0; //count used for Wifi check times
  while ( WiFi.status() != WL_CONNECTED && count < 6) { // try 6 times
    delay(10000);
    Serial.print("Attempting to connect to ");
    Serial.println(network);
    WiFi.begin(network, password); //attempt to connect to wifi
    Serial.println(WiFi.status());
    Serial.print(".");
    count++;
  }
  delay(2000);  //acceptable since it is in the setup function.
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("CONNECTED!");
    delay(500);
  } else { //if we failed to connect just Try again.
    Serial.println("Failed to Connect :/  Plz restart");
    Serial.println(WiFi.status());
    return;
  }


  state = REST;

  pinMode(button_pin, INPUT_PULLUP);
  pinMode(button_pin2, INPUT_PULLUP);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void loop() {

  get_drive(id); // returns 4 states 0 = REST 1, = RIGHT, 2 = LEFT, 3 = BOTH
  if (isdigit(output[0])) {
    state = atoi(output);
    Serial.println("State " + String(state));
  }

  switch (state) {
    case REST:
      analogWrite(in1,100);
      analogWrite(in3,100);
      break;
    case RIGHT:
      analogWrite(in1,255);
      analogWrite(in3,100);
      break;
    case LEFT:
      analogWrite(in1,100);
      analogWrite(in3,255);
      break;
    case BOTH:
      analogWrite(in1,255);
      analogWrite(in3,150);
      break;
  }
  delay(300);
}
