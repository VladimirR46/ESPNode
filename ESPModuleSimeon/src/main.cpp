#include <Arduino.h>
#include <CAN.h>
#include "Settings.h"
#include "WiFi.h"
#include "WiFiUdp.h"

Settings settings;

bool isSend = false;
uint8_t rx_buff[8];
uint8_t can_id = 0;

uint32_t mc_time = 0;

// UDP
bool connected = false;
WiFiUDP UDP;
unsigned int localPort = 1234;

// define functions
void onReceive(int packetSize);
void WiFiEvent(WiFiEvent_t event);

//------------------------------------------------------------------
void setup()
{
    // Init settings
    settings.init(115200);

    // Init WiFi
    WiFi.disconnect(true);
    WiFi.onEvent(WiFiEvent);
    WiFi.begin(settings.GetSSID(), settings.GetPass());

    // Init Can bus
    if (!CAN.begin(1000E3))
    {
        Serial.println("Starting CAN failed!");
    }

    CAN.onReceive(onReceive);
}

//------------------------------------------------------------------
void loop()
{
    if (!settings.update())
        return;

    if (connected)
    {
        size_t size = UDP.parsePacket();
        if (size)
        {

            uint8_t udp_buff[9];
            UDP.read(udp_buff, size);
            /*
            UDP.beginPacket(settings.GetServerIP(), settings.GetServerPort());
            UDP.write(udp_buff, sizeof(udp_buff));
            UDP.endPacket();
            */

            CAN.beginExtendedPacket(udp_buff[0]);
            CAN.write(udp_buff + 1, sizeof(udp_buff) - 1);
            CAN.endPacket();
        }

        if (isSend)
        {
            isSend = false;

            uint8_t udp_buff[9];
            udp_buff[0] = can_id;
            memcpy(udp_buff + 1, rx_buff, sizeof(rx_buff));

            UDP.beginPacket(settings.GetServerIP(), settings.GetServerPort());
            UDP.write(udp_buff, sizeof(udp_buff));
            UDP.endPacket();
        }
    }
}

void onReceive(int packetSize)
{
    // only print packet data for non-RTR packets
    if (CAN.available())
    {
        for (int i = 0; i < packetSize; i++)
            rx_buff[i] = CAN.read();

        can_id = CAN.packetId();
        isSend = true;
    }
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.print("WiFi connected! IP address: ");
        Serial.println(WiFi.localIP());
        UDP.begin(WiFi.localIP(), localPort);
        connected = true;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        connected = false;
        break;
    default:
        break;
    }
}
