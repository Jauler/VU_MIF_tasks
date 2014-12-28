/*

	Connector class to get accelerometer and gyroscope measurements from device
	Author: Rytis Karpuška
		rytis@elektromotus.lt

*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <endian.h>


#include "connector.h"

#define CONNECTOR_PORT_NUM		10001


static void (*notifier_f)(union measurement *m);
static int sockfd, clientfd;
static struct sockaddr_in server_addr, client_addr;


int connector_register_notifier(void (*notifier)(union measurement *m))
{
	notifier_f = notifier;
	return 0;
}




static void wait_for_measurements()
{
	uint8_t buff[2048];
	int len;
	int i;
	int buff_offset = 0;
	int meas_offset = 0;
	union measurement m;
	void *pm = &m;

	while(1){
		//Read data
		len = read(clientfd, buff, sizeof(buff));

		while(len > buff_offset){

			//Check how much can we copy
			int copy_cnt = len - buff_offset;
			if(meas_offset + copy_cnt > sizeof(m))
				copy_cnt = sizeof(m) - meas_offset;

			//copy data
			memcpy(pm + meas_offset, buff + buff_offset, copy_cnt);
			meas_offset += copy_cnt;
			buff_offset += copy_cnt;

			//Check if we should give away our measurement
			if(sizeof(m) == meas_offset){
				//reverse byte order
				m.ints.type = be32toh(m.ints.type);
				m.ints.value[0] = be32toh(m.ints.value[0]);
				m.ints.value[1] = be32toh(m.ints.value[1]);
				m.ints.value[2] = be32toh(m.ints.value[2]);
				m.ints.timestamp = be64toh(m.ints.timestamp);

				if(notifier_f) notifier_f(&m);
				meas_offset = 0;
			}

		}
		buff_offset = 0;

	}


	return;
}

static void wait_for_connection()
{
	int client_len = sizeof(client_addr);

	//Notify
	fprintf(stderr, "Listening on %s at %d\n", 
					inet_ntoa(server_addr.sin_addr),
					CONNECTOR_PORT_NUM);

	//Handle connections
	while(1){
		//wait for connection
		clientfd = accept(sockfd, (struct sockaddr *)&client_addr,
								&client_len);
		//check conenction
		if(clientfd < 0){
			fprintf(stderr, "Connector: Error accepting: %s\n",
								strerror(sockfd));
			continue;
		}

		fprintf(stderr, "New Connection from %s\n",
					inet_ntoa(client_addr.sin_addr));

		wait_for_measurements();
	}

	return;
}

void connector_run()
{
	//This is thread entry point for connector module,
	//Here we create socket and then wait_for_connection is called

	int status;

	//Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		fprintf(stderr, "Connector: Error opening socket: %s\n",
								strerror(sockfd));
		return;
	}

	//Bind socket
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(CONNECTOR_PORT_NUM);
	status = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(status < 0){
		fprintf(stderr, "Connector: Error binding socket: %s\n",
								strerror(status));
		return;
	}

	//Start listening on socket
	listen(sockfd, 1);

	//call connections handler
	wait_for_connection();

	return;
}

