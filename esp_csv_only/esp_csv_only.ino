#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ESP8266WiFi.h>

String wifi_names[] = {"Baka_kun", "Doctors", "Hosam Salim", "Mhossam", "Monir", "Anter", "Hamada", "ashraf", "Abdo" };
String ssid_names[] = {"", "", "", "", "", "", "", "", ""};
int temp_rssi_values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int rssi_values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

int s_len = sizeof(wifi_names)/sizeof(wifi_names[0]);
int k = 0;

void setup()
{
    // Debug console
    Serial.begin(9600);
}

void loop()
{
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println(s_len);

    Serial.println(child_name);

    Serial.print("DATA,");

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

    for (int i = 0; i < s_len; i++)
    {
        Serial.print(rssi_values[i]);
        Serial.print(",");
        delay(10);
    }

    Serial.println();
    
    // Wait a bit before scanning again
    delay(2000);
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
