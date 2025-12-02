#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

#define LDR_PIN A0        // LDR connected to analog pin A0
#define LED_PIN 4         // LED connected to GPIO4 (D2)
#define IR_SENSOR_PIN 5   // IR sensor input - GPIO5 (D1)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;
int speedCar = 800;        // Default speed
int speed_Coeff = 3;
bool irDetected = false;

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);  // IR sensor

  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

// Movement Functions
void goAhead() {
  if (irDetected) {
    stopRobot();
    return;
  }
  digitalWrite(IN_1, LOW); digitalWrite(IN_2, HIGH); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW); digitalWrite(IN_4, HIGH); analogWrite(ENB, speedCar);
}

void goBack() {
  digitalWrite(IN_1, HIGH); digitalWrite(IN_2, LOW); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, HIGH); digitalWrite(IN_4, LOW); analogWrite(ENB, speedCar);
}

void goRight() {
  digitalWrite(IN_1, HIGH); digitalWrite(IN_2, LOW); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW);  digitalWrite(IN_4, HIGH); analogWrite(ENB, speedCar);
}

void goLeft() {
  digitalWrite(IN_1, LOW);  digitalWrite(IN_2, HIGH); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, HIGH); digitalWrite(IN_4, LOW); analogWrite(ENB, speedCar);
}

void goAheadRight() {
  if (irDetected) {
    stopRobot();
    return;
  }
  digitalWrite(IN_1, LOW); digitalWrite(IN_2, HIGH); analogWrite(ENA, speedCar / speed_Coeff);
  digitalWrite(IN_3, LOW); digitalWrite(IN_4, HIGH); analogWrite(ENB, speedCar);
}

void goAheadLeft() {
  if (irDetected) {
    stopRobot();
    return;
  }
  digitalWrite(IN_1, LOW); digitalWrite(IN_2, HIGH); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW); digitalWrite(IN_4, HIGH); analogWrite(ENB, speedCar / speed_Coeff);
}

void goBackRight() {
  digitalWrite(IN_1, HIGH); digitalWrite(IN_2, LOW); analogWrite(ENA, speedCar / speed_Coeff);
  digitalWrite(IN_3, HIGH); digitalWrite(IN_4, LOW); analogWrite(ENB, speedCar);
}

void goBackLeft() {
  digitalWrite(IN_1, HIGH); digitalWrite(IN_2, LOW); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, HIGH); digitalWrite(IN_4, LOW); analogWrite(ENB, speedCar / speed_Coeff);
}

void stopRobot() {
  digitalWrite(IN_1, LOW); digitalWrite(IN_2, LOW); analogWrite(ENA, 0);
  digitalWrite(IN_3, LOW); digitalWrite(IN_4, LOW); analogWrite(ENB, 0);
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}

void loop() {
  server.handleClient();

  // IR Sensor
  irDetected = (digitalRead(IR_SENSOR_PIN) == LOW);
  Serial.print("IR Obstacle: ");
  Serial.println(irDetected ? "Detected" : "Clear");

  // LDR LED Control
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR: "); Serial.println(ldrValue);
  if (ldrValue > 200) digitalWrite(LED_PIN, LOW);
  else digitalWrite(LED_PIN, HIGH);

  // Web Command Control
  command = server.arg("State");
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "0") speedCar = 400;
  else if (command == "1") speedCar = 470;
  else if (command == "2") speedCar = 540;
  else if (command == "3") speedCar = 610;
  else if (command == "4") speedCar = 680;
  else if (command == "5") speedCar = 750;
  else if (command == "6") speedCar = 820;
  else if (command == "7") speedCar = 890;
  else if (command == "8") speedCar = 960;
  else if (command == "9") speedCar = 1023;
  else if (command == "S") stopRobot();

  delay(100);
}