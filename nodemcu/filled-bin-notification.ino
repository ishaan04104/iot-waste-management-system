#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

// ----------- Enter your Wi-Fi Details -----------
const char* ssid = "your_SSID"; // SSID
const char* password = "your_password"; // Password
// ------------------------------------------------

const int buzzer = D1;
const int triggerPin1 = D2; // Trigger pin for sensor 1
const int echoPin1 = D3;    // Echo pin for sensor 1
const int triggerPin2 = D4; // Trigger pin for sensor 2
const int echoPin2 = D5;    // Echo pin for sensor 2

const int ChannelField1 = 1; // Which channel to write data for sensor 1
const int ChannelField2 = 2; // Which channel to write data for sensor 2
const int notificationThreshold = 3; // Distance threshold for triggering notification (in cm)

// WhatsApp configuration
String phoneNumber = "+91xxxxxxxxxx"; // Your phone number
String apiKey = "your_api_key";       // CallMeBot API key

void sendMessageToWhatsApp(String message) {
    // Data to send with HTTP POST
    String url = "http://api.callmebot.com/whatsapp.php?phone=" +
                 phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
    
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, url);
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(url);
    if (httpResponseCode == 200) {
        Serial.print("Message sent successfully");
    } else {
        Serial.println("Error sending the message");
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
    }
    
    // Free resources
    http.end();
}

long pulseInMultiple(int pin, int timeout = 20000) {
    long pulseDuration = pulseIn(pin, HIGH, timeout);
    return pulseDuration;
}

void setup() {
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(triggerPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(triggerPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    
    WiFi.mode(WIFI_STA);
    
    // Connect to Wi-Fi
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected to WiFi");
}

void loop() {
    // Sensor 1
    digitalWrite(triggerPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin1, LOW);
    long duration1 = pulseInMultiple(echoPin1);
    float distance1 = duration1 * 0.034 / 2;
    
    // Sensor 2
    digitalWrite(triggerPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin2, LOW);
    long duration2 = pulseInMultiple(echoPin2);
    float distance2 = duration2 * 0.034 / 2;
    
    Serial.print("Distance Sensor 1 (cm): ");
    Serial.println(distance1);
    Serial.print("Distance Sensor 2 (cm): ");
    Serial.println(distance2);
    
    if (distance1 < notificationThreshold || distance2 < notificationThreshold) {
        tone(buzzer, 5000);
        noTone(buzzer);
        delay(1500);
        tone(buzzer, 1800);
        delay(1500);
        noTone(buzzer);
        delay(1000);
        
        // Send message to WhatsApp
        String message = "I am full please clear me.";
        sendMessageToWhatsApp(message);
        Serial.println("WhatsApp message sent");
        delay(1000);
    }
}
