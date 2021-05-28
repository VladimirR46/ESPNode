#include "socketcan.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>


int socketcan_open() 
{
	int s;
    struct ifreq ifr;
    struct sockaddr_can addr;

    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0) 
    {
		perror("Socket");
		return s;
	}

    strcpy(ifr.ifr_name, "any" );
	ioctl(s, SIOCGIFINDEX, &ifr);
    
    memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = 0; // any
	

    bind(s, (struct sockaddr *)&addr, sizeof(addr));

	// Set to non blocking
	fcntl(s, F_SETFL, O_NONBLOCK);
    
	return s;
}


void socketcan_close(int s) {
	close(s);
}


int socketcan_read(int s, my_can_frame* frame /*, int timeout*/) {
	// Wait for data or timeout
	int nbytes, t;
	struct can_frame f;
    struct sockaddr_can addr;
    struct ifreq ifr;

	struct pollfd p[1];
	p[0].fd = s;
	p[0].events = POLLIN;
	p[0].revents = 0;
	t = poll(p, 1, TIME_OUT_CAN);

	if(t <= 0) return -3;

	socklen_t len = sizeof(addr);
    // Try to read available data
    nbytes = recvfrom(s, &f, sizeof(struct can_frame),
                0, (struct sockaddr*)&addr, &len);		

	if(nbytes <= 0) {
		// Error, no bytes read
		frame->id = 0;
		frame->dlc = 0;
		if (nbytes == 0) {
			return SOCKETCAN_TIMEOUT;
		}
		return SOCKETCAN_ERROR;
	}

    //get interface name of the received CAN frame 
    ifr.ifr_ifindex = addr.can_ifindex;
    ioctl(s, SIOCGIFNAME, &ifr);
    
    strcpy(frame->ifname,ifr.ifr_name);
	frame->id = f.can_id;
	frame->dlc = f.can_dlc;
	memcpy(frame->data, f.data, sizeof(frame->data));
	return s;
}


int socketcan_write(int s, char *ifname, uint16_t id, uint8_t data[]) {

	struct can_frame frame;
	struct sockaddr_can addr;
    struct ifreq ifr;

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	addr.can_ifindex = ifr.ifr_ifindex;
	addr.can_family  = AF_CAN;

	frame.can_id = id;
	frame.can_dlc = 8;

	memcpy(frame.data,data,8);

	int nbytes = sendto(s, &frame, sizeof(struct can_frame),
			0, (struct sockaddr*)&addr, sizeof(addr));
			
	if(nbytes < 0) {
		// Error, no data written
		return SOCKETCAN_ERROR;
	}
	return 0;
}
