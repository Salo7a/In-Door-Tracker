#include <ArduinoSort.h>

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

String wifi_names[] = {"BODY-ALREFAEY 9031", "Baka_kun", "Doctors", "Hosam Salim", "Mhossam", "Monir", "Anter", "Hamada", "Abdo" };
const char * testarr[] = {"BODY-ALREFAEY 9031", "Baka_kun", "Doctors", "Hosam Salim", "Mhossam", "Monir", "Anter", "Hamada", "Abdo" };
String ssid_names[] = {"", "", "", "", "", "", "", "", ""};       // SSID names after scanning, not ordered.
int temp_rssi_values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};              // RSSI values after scanning, not ordered.
int rssi_values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};                   // RSSI values after scanning, ordered with wifi_names.

int s_len = sizeof(wifi_names)/sizeof(wifi_names[0]);
int k = 0;

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

    sortArray(testarr, s_len);
    for (int i = 0; i < s_len; i++)
    {
        Serial.println(testarr[i]);
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

        // Save SSIDs and RSSIs to array
        for (int i = 0; i < n; ++i)
        {
            ssid_names[i] = WiFi.SSID(i);
            temp_rssi_values[i] = WiFi.RSSI(i);
        }

        // Get Index of each wifi and sort rssi
        for (int i = 0; i < s_len; ++i)
        {
            k = getIndex(ssid_names , s_len, wifi_names[i]);
            rssi_values[i] = temp_rssi_values[k];
        }

        // Sort SSID names
        sortArray(ssid_names, s_len);

    
        for (int i = 0; i < s_len; ++i)
        {
            // Print SSID and RSSI for each network found
            Serial.print("(");
            Serial.print(i + 1);
            Serial.print(") ");
            Serial.print(ssid_names[i]);       // SSID
            Serial.print("  ");
                                    
            Serial.print(rssi_values[i]);       //Signal strength in dBm  
            Serial.println(" dBm");
      
            delay(20);
        }

        for (int i = 0; i < n; ++i)
        {
            // Set Attributes in Firebase
            if (Firebase.setInt(firebaseData,ssid_names[i], rssi_values[i])) {
                // Success
                Serial.println("Set int data success");
            } else {
                // Failed?, get the error reason from firebaseDate
                Serial.print("Error in setString, ");
                Serial.println(firebaseData.errorReason());
            }
            delay(300);
        }
        
    }
    Serial.println("");
  
    // Wait a bit before scanning again
    delay(3000);
    WiFi.scanDelete();  
    
}

//// Defining comparator function as per the requirement
//static int myCompare(const void* a, const void* b)
//{
//    // setting up rules for comparison
//    return strcmp(*(const char**)a, *(const char**)b);
//}
//
//// Function to sort the array
//void sort_array(const char* arr[], int n)
//{
//    // calling qsort function to sort the array
//    // with the help of Comparator
//    qsort(arr, n, sizeof(const char*), myCompare);
//}

// Function to get Index of an element in an array
int getIndex(String arr[], int n, String val)
{
    int indx = -1;

    for (int i = 0; i < n; i++)
    {
        if ( val != String(arr[i])  )
        {
            continue;
        }
        indx = i;
        break;
    }
    return indx;
}
