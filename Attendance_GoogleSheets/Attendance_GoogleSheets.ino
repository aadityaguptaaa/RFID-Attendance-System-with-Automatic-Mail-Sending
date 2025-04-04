#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Include the LiquidCrystal I2C library

//-----------------------------------------
#define RST_PIN  D3
#define SS_PIN   D4
#define BUZZER   D2 // Buzzer connected to GPIO 16 (D2)

// Define I2C address for PCF8574T (adjust if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change address if necessary

//-----------------------------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;  
MFRC522::StatusCode status;      

//-----------------------------------------
int blockNum = 2;  
byte bufferLen = 18;
byte readBlockData[18];

//-----------------------------------------
String card_holder_name;
const String sheet_url = " ";    //Paste your Google sheet URL

//-----------------------------------------
const uint8_t fingerprint[32] = {
  0x1f, 0x97, 0xbf, 0x82, 0x32, 0x49, 0x5f, 0x69,
  0x04, 0x55, 0xc5, 0x3c, 0x33, 0x28, 0x95, 0x00,
  0xb0, 0x24, 0x66, 0x02, 0xb2, 0x0e, 0xc5, 0xdb,
  0x95, 0x77, 0xfd, 0xa9, 0xeb, 0xb6, 0x28, 0x00
};

//-----------------------------------------
#define WIFI_SSID " "       //Enter Your WIFI Username
#define WIFI_PASSWORD " "   //Enter Your WIFI Password

/****************************************************************************************************
 * Buzzer Function
 ****************************************************************************************************/
void beepBuzzer(int duration) {
    digitalWrite(BUZZER, HIGH); // Turn on the buzzer
    delay(duration);              // Wait for the specified duration
    digitalWrite(BUZZER, LOW);   // Turn off the buzzer
}

/****************************************************************************************************
 * setup() function
 ****************************************************************************************************/
void setup() {
    Serial.begin(9600);
    
    // Initialize the LCD
    lcd.init(); // Use init() instead of begin()
    lcd.backlight(); // Turn on the backlight
    lcd.print("Scan Your Card"); // Initial message
    
    // WiFi Connectivity
    Serial.println();
    Serial.print("Connecting to AP");
    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(200);
    }
    
    Serial.println("");
    Serial.println("WiFi connected.");
    
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW); // Ensure buzzer is off initially
    
    SPI.begin();
}

/****************************************************************************************************
 * loop() function
 ****************************************************************************************************/
void loop() {
    mfrc522.PCD_Init(); // Initialize MFRC522 module

    if (!mfrc522.PICC_IsNewCardPresent()) {
        return; // Exit if no new card is present
    }
    
    if (!mfrc522.PICC_ReadCardSerial()) {
        return; // Exit if card serial reading failed
    }

    // Buzzer beeps every time a card is scanned
    beepBuzzer(200); // Call beep function with duration of beep
    
    Serial.println(F("Reading last data from RFID..."));
    ReadDataFromBlock(blockNum, readBlockData);
    
    // Print the data read from block
    Serial.println();
    Serial.print(F("Last data in RFID:"));
    Serial.print(blockNum);
    Serial.print(F(" --> "));
    
    for (int j = 0; j < 16; j++) {
        Serial.write(readBlockData[j]);
    }
    
    Serial.println();
   
    if (WiFi.status() == WL_CONNECTED) {
        std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
        client->setInsecure();

        // Display "Scanning..." on the LCD while updating
        lcd.clear();          // Clear previous message on the LCD
        lcd.print("Scanning..."); // Show scanning message

        card_holder_name = sheet_url + String((char*)readBlockData);
        card_holder_name.trim();
        Serial.println(card_holder_name);
        
        HTTPClient https;
        Serial.print(F("READING DATA...\n"));
        
        if (https.begin(*client, (String)card_holder_name)) {
            Serial.print(F("UPDATING....\n"));
            
            int httpCode = https.GET();
            
            if (httpCode > 0) {
                Serial.printf("UPDATED SUCCESSFULLY\n", httpCode);
                lcd.clear(); // Clear previous message on the LCD
                lcd.print("Hey "); // Display greeting message
                lcd.print((char*)readBlockData); // Display name read from RFID card
                lcd.print("!!!"); // Add "!!!" after the name
            } else {
                Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            }
            
            https.end();
            delay(1000);
        } else {
            Serial.printf("[HTTPS} Unable to connect\n");
        }
    }

    // After processing the card and updating the name,
    // display "Scan Your Card" again.
    lcd.clear(); // Clear previous message on the LCD
    lcd.print("Scan Your Card"); // Display prompt to scan again
    
    // Allow some time before checking for the next card
    delay(200); // Short delay before next scan
    mfrc522.PICC_HaltA(); // Halt the current card
}

/****************************************************************************************************
 * ReadDataFromBlock() function
 ****************************************************************************************************/
void ReadDataFromBlock(int blockNum, byte readBlockData[]) { 
   for (byte i = 0; i < 6; i++) {
       key.keyByte[i] = 0xFF;
   }

   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));

   if (status != MFRC522::STATUS_OK) {
      Serial.print("Authentication failed for Read: ");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
   } else {
      Serial.println("Authentication success");
   }

   status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);

   if (status != MFRC522::STATUS_OK) {
      Serial.print("Reading failed: ");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
   } else {
      Serial.println("Block was read successfully");  
   }
}
