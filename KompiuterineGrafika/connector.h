/*

	Connector class to get accelerometer and gyroscope measurements from device
	Author: Rytis Karpuška
		rytis@elektromotus.lt

*/

#ifndef __CONNECTOR_H
#define __CONNECTOR_H

#include <stdint.h>

struct __attribute__((packed)) measurement_floats {
	uint32_t type;
	float value[3];
	long long int timestamp;
};

struct __attribute__((packed)) measurement_ints {
	uint32_t type;
	uint32_t value[3];
	long long int timestamp;
};

union __attribute__((packed)) measurement {
	struct measurement_floats floats;
	struct measurement_ints ints;

};

int connector_register_notifier(void (*notifier)(union measurement *m));

void connector_run();

#endif

