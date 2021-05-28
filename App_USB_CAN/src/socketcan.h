#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#include <inttypes.h>
#include <net/if.h>

#define TIME_OUT_CAN 1

#define SOCKETCAN_ERROR   -1
#define SOCKETCAN_TIMEOUT -2

typedef struct {
    char ifname[IFNAMSIZ];
	uint16_t id;
	uint8_t dlc;
	uint8_t data[8];
} my_can_frame;

int socketcan_open();

void socketcan_close(int s);

int socketcan_read(int s, my_can_frame* frame);

int socketcan_write(int s, char *ifname, uint16_t id, uint8_t data[]);

#endif