#include <ArduinoSort.h>
#include <string.h>
#include <stdio.h>

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseFS.h>
#include <FirebaseJson.h>

// Configure Firebase Variables
#define FIREBASE_HOST "tracking-a-person-using-wifi.firebaseio.com"
#define FIREBASE_AUTH "c9tHc8KtbUUNqEKhBLSCYYvfDexS9Sap0oMMCe5c"
#define WIFI_SSID "BODY-ALREFAEY 9031"
#define WIFI_PASSWORD "%rG15399"

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

//String wifi_names[] = {"BODY-ALREFAEY 9031", "Baka_kun", "Doctors", "Hosam Salim", "Mhossam", "Monir", "Anter", "Hamada", "Abdo" };
//const char * testarr[] = {"BODY-ALREFAEY 9031", "Baka_kun", "Doctors", "Hosam Salim", "Mhossam", "Monir", "Anter", "Hamada", "Abdo" };
//String ssid_names[] = {"", "", "", "", "", "", "", "", ""};       // SSID names after scanning, not ordered.
//int temp_rssi_values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};              // RSSI values after scanning, not ordered.
//int rssi_values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};                   // RSSI values after scanning, ordered with wifi_names.

String saved_networks[] = {"Baka_kun", "Doctors", "Hosam Salim", "BODY-ALREFAEY 9031", "Mhossam", "Monir"};
String scanned_ssids[] = {"", "", "", "", "", ""};
int rssi_values[] = {0, 0, 0, 0, 0, 0};

int w_len = sizeof(saved_networks)/sizeof(saved_networks[0]);
int s_len = sizeof(scanned_ssids)/sizeof(scanned_ssids[0]);
int s_index = 0;          // index for scanned_ssids
int w_index = 0;          // index for saved_networks

//int s_len = sizeof(wifi_names)/sizeof(wifi_names[0]);
//int k = 0;

void setup()
{
    // Debug console
    Serial.begin(115200);
  
    // connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
        
    // Enable auto reconnect the WiFi when connection lost
    Firebase.reconnectWiFi(true);
}

void loop()
{
    Serial.println("WiFi scan started");
  
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();

    Serial.println("Wifi scan ended");

    // Save SSIDs and RSSIs to array
    for (int i = 0; i < n; ++i)
    {
        // Check if the ssid exists in the saved networks
        s_index = findElement(saved_networks, w_len, WiFi.SSID(i));
        if (s_index != -1)
        {
            scanned_ssids[s_index] = WiFi.SSID(i);
            rssi_values[s_index] = WiFi.RSSI(i);
        }
    }

    // Check if there's a network in saved and not scanned (Error while scanning)
    // So put it's RSSI = 0 (Take average later)
    for (int i = 0; i < w_len; i++)
    {
        w_index = findElement(scanned_ssids, w_len, saved_networks[i]);
        // If it is saved network and not scanned -> put rssi = 0
        if (w_index == -1)
        {
            scanned_ssids[i] = saved_networks[i];
            rssi_values[i] = 0;
        }
    }

    // Displaying the scanned WiFis
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
    
        for (int i = 0; i < s_len; ++i)
        {
            // Print SSID and RSSI for each network found
            Serial.print("(");
            Serial.print(i + 1);
            Serial.print(") ");
            Serial.print(scanned_ssids[i]);       // SSID
            Serial.print("  ");
                                    
            Serial.print(rssi_values[i]);       //Signal strength in dBm  
            Serial.println(" dBm");
      
            delay(20);
        }

        // Send Data to Firebase
        for (int i = 0; i < s_len; ++i)
        {
            // Set Attributes in Firebase
            if (Firebase.setInt(firebaseData, scanned_ssids[i], rssi_values[i])) {
                // Success
                Serial.println("Set int data success");
            } else {
                // Failed?, get the error reason from firebaseDate
                Serial.print("Error in setInt, ");
                Serial.println(firebaseData.errorReason());
            }
            delay(200);
        }
        
    }
    Serial.println("");
  
    // Wait a bit before scanning again
    delay(5000);
    WiFi.scanDelete();  
    
}


// Function to find element in an array
// return its index if found and -1 if not
int findElement(String arr[], int n, String val)
{
    int indx = -1;

    for (int i = 0; i < n; i++)
    {
        // if found -> 0 -> !0 = 1 = True
        if(val == String(arr[i]))
        {
            indx = i;
            break;
        }
    }
    return indx;
}
