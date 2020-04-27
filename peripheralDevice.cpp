#include <ArduinoBLE.h>
#include "Arduino.h"

// Relay on D8
int relay = 8;

 // BLE PersonDetection Service
BLEService PersonDetectionService("1801");

// BLE Alert Level Characteristic
BLEByteCharacteristic alertLevelChar("2A06",  // standard 16-bit characteristic UUID
    BLERead | BLEWrite); // remote clients will be able to get notifications if this characteristic changes


void setup() {
  Serial.begin(9600);    // initialize serial communication
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT); // initialize the built-in LED pin to indicate when a central is connected
  //pinMode(LEDR, OUTPUT);
  //pinMode(LEDG, OUTPUT);
  //pinMode(LEDB, OUTPUT);
  //pinMode(relay, OUTPUT);

  //digitalWrite(LEDR, LOW);
  //digitalWrite(LEDG, LOW);
  //digitalWrite(LEDB, LOW);
  digitalWrite(relay, LOW);
  
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet
  */
  BLE.setLocalName("PersonDetectionMonitor");
  BLE.setAdvertisedService(PersonDetectionService); // add the service UUID
  PersonDetectionService.addCharacteristic(alertLevelChar); // add the alert level characteristic
  BLE.addService(PersonDetectionService); // Add the battery service
  alertLevelChar.writeValue((byte)0x00);
  
  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // wait for a BLE central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    // while the central is connected:
    while (central.connected()) {
      //Serial.println("Getting Alert Level:");
      if (alertLevelChar.written()){
        if (alertLevelChar.value()){
          Serial.println("Got high alert");
          digitalWrite(relay, HIGH);
          Serial.println("Set relay to HIGH");
        } else{
          Serial.println("Got low alert");
          digitalWrite(relay, LOW);
          Serial.println("Set relay to LOW");
        }
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
