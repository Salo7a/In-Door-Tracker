#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ESP8266WiFi.h>

String saved_networks[] = {"StudBME1", "STUDBME2", "SBME_STAFF3", "SBME_STAFF", "CUFE", "RehabLab", "lab001", "CMP_LAB1", "CMP_LAB2"};
String scanned_ssids[9];
int rssi_values[9];

int w_len = sizeof(saved_networks)/sizeof(saved_networks[0]);
int s_len = sizeof(scanned_ssids)/sizeof(scanned_ssids[0]);
int s_index = 0;          // index for scanned_ssids
int w_index = 0;          // index for saved_networks


void setup()
{
    // Debug console
    Serial.begin(9600);
}

void loop()
{
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();

    Serial.print("DATA,");

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

    // Send data to csv
    for (int i = 0; i < s_len; i++)
    {
        Serial.print(rssi_values[i]);
        Serial.print(",");
        delay(10);
    }

    Serial.println();
    
    // Wait a bit before scanning again
    delay(200);
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
//void sort(const char* arr[], int n)
//{
//    // calling qsort function to sort the array
//    // with the help of Comparator
//    qsort(arr, n, sizeof(const char*), myCompare);
//}

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
