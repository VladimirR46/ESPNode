#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <signal.h>
#include <chrono>
#include <unistd.h>

#include "socketcan.h"

static volatile int running = 1;

using namespace std;

static void sigterm(int signo)
{
	running = 0;
}

int main(int argc, char **argv)
{
	signal(SIGTERM, sigterm);
	signal(SIGHUP, sigterm);
	signal(SIGINT, sigterm);

	int can_socket = socketcan_open();

	uint8_t can_data[8];
	my_can_frame frame;

	//socketcan_write(can_socket, "can0", 0x01, frame.data);
	//auto begin = std::chrono::steady_clock::now();

	while (running)
	{
		if (socketcan_read(can_socket, &frame) > 0)
		{
			//std::cout << "Read mess" << std::endl;
			socketcan_write(can_socket, "can0", 0x03, frame.data);
			/*
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms\n";
			usleep(900);
			auto begin = std::chrono::steady_clock::now();
			socketcan_write(can_socket, "can0", frame.id, frame.data);
			*/
		}
	}

	socketcan_close(can_socket);

	return 1;
}