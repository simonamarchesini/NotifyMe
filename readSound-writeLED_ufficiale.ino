#include <SoftwareSerial.h>
//SoftwareSerial BTserial(2,3); // RX | TX  per Arduino Uno
SoftwareSerial BTserial(10, 11); // RX | TX  per Arduino Mega
String voice;
const int sound_Sensor = A0;
int inputVal = 0;
int nextvalue = 0;
int ledpin = 12;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(sound_Sensor, INPUT);   //Pin 2 is connected to the output of proximity sensor

  Serial.begin(9600);
  BTserial.begin(9600);
}

void loop() {
  //leggiSeriale();
  leggiSuono();
  leggiBT();
}

void leggiBT() {
  while (BTserial.available())
  {
    Serial.print("cisos");
    delay(10);
    char c = BTserial.read();
    voice += c;
  }
  if (voice.length() > 0)
  {
    Serial.print(voice);
    if (voice == "on")
    {
      digitalWrite(12, HIGH);
    }
    if (voice == "off")
    {
      Serial.print("spegni");
      digitalWrite(12, LOW);
    }
    voice = "";
  }
}

void leggiSeriale() {
  while (Serial.available())
  {
    delay(10);
    char c = Serial.read();
    voice += c;
  }
  if (voice.length() > 0)
  {
    Serial.println(voice);
    int bytesSent = BTserial.println(voice);
    if (voice == "on")
    {
      digitalWrite(12, HIGH);
    }
    if (voice == "off")
    {
      digitalWrite(12, LOW);
    }

    voice = "";
  }

}

void leggiSuono() {

  inputVal = analogRead(sound_Sensor); //connect mic sensor to Analog 0
  if  ((inputVal - nextvalue) > 1) {

    if (inputVal > 200) {
      accendiLed(ledpin);
      Serial.print("sound:");
      Serial.println(inputVal);
      BTserial.print(" " );
      BTserial.println(inputVal); //scrive su BT
      delay(20);              // wait
    }
    Serial.print("sound:");
    Serial.println(inputVal);
    BTserial.print(" " );
  }
  nextvalue = inputVal;
}

void accendiLed(int ledpin) {
  digitalWrite(ledpin, HIGH);// turn the LED on (HIGH is the voltage level)
  delay (1000);
}


