#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include <string.h>

struct can_frame {
	int id;
	uint8_t dlc;
	uint8_t data[8];
};

enum can_parse_err {
	ok = 0,
	id_mismatch = 1,
        dlc_mismatch = 2,
};

int handle_parse_err (enum can_parse_err err);

#define CAN_ID_ENGINE_STATE 0x100
#define CAN_DLC_ENGINE_STATE 3
int encode_engine_state (struct can_frame *frame, int rpm, int load);
int decode_engine_state (struct can_frame *frame, int *rpm, int *load);

// assuming temperatures in celsius, reassures me itll fit in a byte
#define CAN_ID_TEMPS 0x200
#define CAN_DLC_TEMPS 3
int encode_temps (struct can_frame *frame, int coolant, int iat, int oil);
int decode_temps (struct can_frame *frame, int *coolant, int *iat, int *oil);

#endif
