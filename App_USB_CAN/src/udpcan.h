#ifndef UDPCAN_H
#define UDPCAN_H

#include <inttypes.h>
#include <net/if.h>
#include <netinet/in.h>

#define INUMBER 2

struct UDP_to_CAN
{
	char ifname[IFNAMSIZ];
	uint16_t receive_port;
	uint16_t send_port;
	in_addr_t send_addr;
};

#endif