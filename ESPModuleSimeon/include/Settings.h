#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <EEPROM.h>

#define VERSION_NUM "1.0"

enum Menu_mode
{
    EMPTY_MODE,
    MENU_MODE,
    SETUP_MODE,
};

struct Configs
{
    char ssid[30];
    char pass[30];
    uint8_t ServerIP[4];
    uint32_t ServerPort;
};

class Settings
{
public:
    Settings();

    void init(unsigned long baud);
    bool CheckSettings();
    void LoadSettings();
    void SaveSettings();
    void WriteDefaultSettings();
    void WriteConfigStruct(const char *ssid, const char *pass, uint8_t *s_ip, uint32_t s_port);
    void PrintSetup();
    void PrintMenu();
    bool update();

    char *GetSSID();
    char *GetPass();
    IPAddress GetServerIP();
    uint32_t GetServerPort();

    ~Settings();

private:
    Configs configs;
    Menu_mode state;

protected:
};

#endif