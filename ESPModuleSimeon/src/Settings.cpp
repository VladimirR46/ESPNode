#include "Settings.h"

const char *setup_items[4] = {"SSID", "PASS", "Server IP", "Server Port"};

Settings::Settings()
{
    state = EMPTY_MODE;
}
//-------------------------------------------------------------------
void Settings::init(unsigned long baud)
{
    Serial.begin(baud);
    Serial.println("\n\r ESP Node");
    Serial.printf(" Firmware Version: %s\n\r", VERSION_NUM);
    Serial.printf(" Esc - Enter to Menu\n\r");
    EEPROM.begin(sizeof(Configs));

    if (CheckSettings())
    {
        LoadSettings();
    }
    else
    {
        WriteDefaultSettings();
        delay(2000);
        ESP.restart();
    }
}
//------------------------------------------------------------------
bool Settings::update()
{
    if (Serial.available() > 0)
    {
        char c;
        char cmd = Serial.read();
        char buff[30];
        int index = 0;

        if (cmd == 27) // Esc
        {
            if (state != MENU_MODE)
            {
                PrintMenu();
                state = MENU_MODE;
            }
            else
            {
                Serial.println(" Exit the menu");
                state = EMPTY_MODE;
            }
        }

        switch (state)
        {
        case MENU_MODE:
            if (cmd == 's')
            {
                PrintSetup();
                state = SETUP_MODE;
            }
            if (cmd == 'r')
            {
                SaveSettings();
                Serial.println(" Restart ESP.........");
                delay(1000);
                ESP.restart();
            }
            break;
        case SETUP_MODE:

            if (cmd <= 48 || cmd > 48 + (sizeof(setup_items) / sizeof(setup_items[0])))
            {
                Serial.println(" Unknown command");
                break;
            }

            Serial.printf(" Enter %s: ", setup_items[atoi(&cmd) - 1]);
            while (true)
            {
                if (index == 29) // Max limit
                    break;

                if (Serial.available() > 0)
                {
                    c = Serial.read();
                    if (c == 13 || c == 27) // Enter or Esc
                    {
                        if (c == 13)
                            c = Serial.read();
                        buff[index] = '\0';
                        break;
                    }
                    else
                    {
                        if (c == 8) // <-
                        {
                            if (index > 0)
                            {
                                Serial.print(c);
                                index--;
                                Serial.print(' ');
                                Serial.print(c);
                            }
                        }
                        else
                        {
                            Serial.print(c);
                            buff[index] = c;
                            index++;
                        }
                    }
                }
                delay(10);
            }

            if (index > 0 && c != 27)
            {
                if (!strcmp(setup_items[atoi(&cmd) - 1], "SSID"))
                    strcpy(configs.ssid, buff);

                if (!strcmp(setup_items[atoi(&cmd) - 1], "PASS"))
                    strcpy(configs.pass, buff);

                if (!strcmp(setup_items[atoi(&cmd) - 1], "Server IP"))
                {
                    IPAddress addr;
                    addr.fromString(buff);
                    memcpy(configs.ServerIP, &addr[0], 4);
                }

                if (!strcmp(setup_items[atoi(&cmd) - 1], "Server Port"))
                    configs.ServerPort = atoi(buff);
            }

            PrintSetup();
            break;
        default:
            break;
        }
    }

    if (state == EMPTY_MODE)
        return true;

    return false;
}
//------------------------------------------------------------------
void Settings::PrintMenu()
{
    printf("\n\r\n\r");
    printf(" Commands:\n\r");
    printf(" s - Setup\n\r");
    printf(" r - Save and restart\n\r");
    printf(" esc - Exit to Menu\n\r");
}
//------------------------------------------------------------------
void Settings::PrintSetup()
{
    Serial.printf("\n\r\n\r Configuration Options \n\r\n\r");
    printf(" %-4s %-31s %-5s\n\r\n\r", "index", "parameter", "current value");
    printf(" %-4s %-31s  %s\n\r", "1", setup_items[0], configs.ssid);
    printf(" %-4s %-31s  %s\n\r", "2", setup_items[1], configs.pass);
    printf(" %-4s %-31s  %d.%d.%d.%d\n\r", "3", setup_items[2], configs.ServerIP[0], configs.ServerIP[1], configs.ServerIP[2], configs.ServerIP[3]);
    printf(" %-4s %-31s  %d\n\r", "4", setup_items[3], configs.ServerPort);
}
//------------------------------------------------------------------
void Settings::LoadSettings()
{
    EEPROM.readBytes(0, (uint8_t *)&configs, sizeof(Configs));
}
//-------------------------------------------------------------------
bool Settings::CheckSettings()
{
    uint8_t ssid_size = EEPROM.read(0);
    if (ssid_size == 0 || ssid_size == 255)
        return false;
    else
        return true;
}
//------------------------------------------------------------------
void Settings::WriteDefaultSettings()
{
    uint8_t s_ip[4] = {192, 168, 0, 4};
    WriteConfigStruct("DIR-615-6e9f", "innopolis", s_ip, 4443);
    SaveSettings();
    Serial.println("DefaultSettings");
}
//------------------------------------------------------------------
void Settings::WriteConfigStruct(const char *ssid, const char *pass, uint8_t *s_ip, uint32_t s_port)
{
    strcpy(configs.ssid, ssid);
    strcpy(configs.pass, pass);
    memcpy(configs.ServerIP, s_ip, 4);
    configs.ServerPort = s_port;
}
//------------------------------------------------------------------
void Settings::SaveSettings()
{
    EEPROM.writeBytes(0, (uint8_t *)&configs, sizeof(Configs));
    EEPROM.commit();
    delay(1000);
}
//-------------------------------------------------------------------
char *Settings::GetSSID()
{
    return configs.ssid;
}
//-------------------------------------------------------------------
char *Settings::GetPass()
{
    return configs.pass;
}
//-------------------------------------------------------------------
IPAddress Settings::GetServerIP()
{
    return IPAddress(configs.ServerIP[0], configs.ServerIP[1], configs.ServerIP[2], configs.ServerIP[3]);
}
//-------------------------------------------------------------------
uint32_t Settings::GetServerPort()
{
    return configs.ServerPort;
}
//-------------------------------------------------------------------
Settings::~Settings()
{
}