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

#define CAN_ID_ENGINE_TIMING 0x101
#define CAN_DLC_ENGINE_TIMING 4
int encode_engine_timing (struct can_frame *frame, int ckp, int cmp, int knk);
int decode_engine_timing (struct can_frame *frame, int *ckp, int *cmp, int *knk);

#define CAN_ID_ENGINE_PRESSURES 0x102
#define CAN_DLC_ENGINE_PRESSURES 4
int encode_engine_pressures (struct can_frame *frame, int oil, int fuel);
int decode_engine_pressures (struct can_frame *frame, int *oil, int *fuel);

#define CAN_ID_ENGINE_DEMAND 0x103
#define CAN_DLC_ENGINE_DEMAND 2
int encode_engine_demand (struct can_frame *frame, int tps, int map);
int decode_engine_demand (struct can_frame *frame, int *tps, int *map);

// assuming temperatures in celsius, reassures me itll fit in a byte
#define CAN_ID_ENGINE_TEMPS 0x104
#define CAN_DLC_ENGINE_TEMPS 3
int encode_temps (struct can_frame *frame, int coolant, int iat, int oil);
int decode_temps (struct can_frame *frame, int *coolant, int *iat, int *oil);

#endif
