#include "secrets.h"  // This file contains sensitive information like Wi-Fi credentials and certificates.
#include <WiFiClientSecure.h>  // Library to create a secure Wi-Fi client (SSL/TLS).
#include <MQTTClient.h>  // MQTT protocol library to communicate with AWS IoT.
#include <ArduinoJson.h>  // Library to parse and create JSON objects.
#include "WiFi.h"  // Library for Wi-Fi functions on ESP32.

// Topic for publishing updates to AWS IoT Device Shadow.
#define AWS_IOT_PUBLISH_TOPIC "$aws/things/[NAME]/shadow/update" 
// Topic to subscribe to for receiving data. 
#define AWS_IOT_SUBSCRIBE_TOPIC "$aws/things/[NAME]/shadow/name/[NAME_DEVICE]/get"  

WiFiClientSecure net = WiFiClientSecure();  // Creates a secure Wi-Fi client.
MQTTClient client = MQTTClient(256);  // Creates an MQTT client with a buffer size of 256 bytes.

const int outputPin = D1;  // Led connected to GPIO pin D1
const int buttonPin = D2;  // Button connected to GPIO pin D2.
int temp = 0;  // Variable to hold the temperature value.

void connectToAWS();  // Function to connect to AWS IoT.
void sendToAWS();  // Function to send data to AWS IoT.
void messageHandler(String &topic, String &payload);  // Function to handle incoming MQTT messages.

void setup() {
  Serial.begin(115200);  // Start the serial communication at 115200 baud rate.
  pinMode(buttonPin, INPUT_PULLUP);  // Set the button pin as input with internal pull-up resistor.
  pinMode(outputPin, OUTPUT);     // Set the led pin as output.
  digitalWrite(outputPin, LOW);   // Set the led pin as output LOW.

  WiFi.mode(WIFI_STA);  // Set Wi-Fi mode to station (client).
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Connect to Wi-Fi using credentials from "secrets.h".

  Serial.println("ESP32 connecting to Wi-Fi");

  // Wait for the Wi-Fi connection.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);  // Wait 500ms before checking again.
    Serial.print(".");  // Print a dot for each attempt.
  }
  Serial.println();  // New line after successful connection.

  connectToAWS();  // Call the function to connect to AWS IoT.
}

void loop() {
  client.loop();  // Keep the MQTT client loop running to handle incoming messages.

  // Check if the button is pressed.
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed! +30 Reset > 90");
    temp += 30;  // Increase the temperature by 30.
    if (temp > 90) temp = 30;  // If temperature exceeds 90, reset it to 30.
    Serial.print("Temperature: ");
    Serial.println(temp);  // Print the current temperature.
    sendToAWS();  // Send the updated temperature to AWS.
    delay(2500);  // Wait for 2.5 seconds before the next action.
  }
}

void connectToAWS() {
  // Configure WiFiClientSecure to use the AWS IoT device credentials.
  net.setCACert(AWS_CERT_CA);  // Set the CA certificate.
  net.setCertificate(AWS_CERT_CRT);  // Set the device certificate.
  net.setPrivateKey(AWS_CERT_PRIVATE);  // Set the private key.

  // Connect to the MQTT broker on the AWS endpoint.
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Set up the message handler for incoming messages.
  client.onMessage(messageHandler);

  Serial.print("ESP32 connecting to AWS IoT");

  // Attempt to connect to AWS IoT.
  while (!client.connect(THINGNAME)) {
    Serial.print(".");  // Print a dot for each attempt.
    delay(100);  // Wait 100ms before the next connection attempt.
  }
  Serial.println();  // New line after successful connection.

  // Check if the connection is successful.
  if (!client.connected()) {
    Serial.println("ESP32 - AWS IoT Timeout!");
    return;  // Return if the connection fails.
  }

  // Subscribe to the topic to receive incoming messages.
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("ESP32  - AWS IoT Connected!");
  Serial.println(" ");
}

void sendToAWS() {
  StaticJsonDocument<200> message;  // Create a JSON document with a 200-byte buffer.
  message["temperature"] = temp;  // Add the temperature value to the message.

  // Create a JSON document for the Device Shadow update.
  StaticJsonDocument<200> shadowMessage;
  shadowMessage["state"]["desired"]["temperature"] = temp;  // Set the desired temperature state in the shadow.

  char messageBuffer[512];  // Buffer to hold the serialized JSON message.
  serializeJson(shadowMessage, messageBuffer);  // Serialize the shadow message to the buffer.

  // Publish the update to the Device Shadow topic.
  client.publish(AWS_IOT_PUBLISH_TOPIC, messageBuffer);

  // Print the topic and payload for debugging purposes.
  Serial.print("TOPIC: ");
  Serial.println("$aws/things/ESP32_thing/shadow/update");
  Serial.print("PAYLOAD: ");
  Serial.println(messageBuffer);
  Serial.println(" ");
}

void messageHandler(String &topic, String &payload) {
  // Handle incoming MQTT messages.
  Serial.println("Received:");
  Serial.println("- topic: " + topic);
  Serial.println("PAYLOAD: ");
  Serial.println(payload);
  Serial.println(" ");

  // Power ON pinout D1 for 2,5s
  digitalWrite(outputPin, HIGH);
  delay(2500);
  digitalWrite(outputPin, LOW);

  // Deserialize the incoming payload as a JSON object.
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];  // Extract the "message" field from the JSON object.
}
