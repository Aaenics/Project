 #include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 13

#define pin1  A0
#define pin2  A1
#define pin3  A2
#define pin4  A3

#define delaytime 100   //delay time in ms to control the stepper motor delaytime.
                      //Our tests showed that 8 is about the fastest that can yield reliable operation w/o missing steps
               
MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT);
  
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) 
    {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Tap card key: ");
  Serial.println(strID);

if (strID.indexOf("36:48:63:32") >= 0) // put your RFID TAG no here
  {
   digitalWrite(pin1, HIGH);
   delay(30000);
   digitalWrite(pin1, LOW);
}
if (strID.indexOf("A1:48:61:7B") >= 0) // put your RFID TAG no here
  {
   digitalWrite(pin2, HIGH);
   delay(30000);
   digitalWrite(pin2, LOW);
}
if (strID.indexOf("66:36:C8:73") >= 0) // put your RFID TAG no here
  {
   digitalWrite(pin3, HIGH);
   delay(30000);
   digitalWrite(pin3, LOW);
}
if (strID.indexOf("DC:57:82:32") >= 0) // put your RFID TAG no here
  {
   digitalWrite(pin4, HIGH);
   delay(30000);
   digitalWrite(pin4, LOW);
}

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}