#include "can.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

int
encode_engine_state (struct can_frame *frame, int rpm, int load) {
	frame->id = CAN_ID_ENGINE_STATE;
	frame->dlc = CAN_DLC_ENGINE_STATE;
	frame->data[0] = rpm >> 8;
	frame->data[1] = rpm & 0xFF;
	frame->data[2] = load;
	return 0;
}

int
decode_engine_state (struct can_frame *frame, int *rpm, int *load) {
	if (frame->id != CAN_ID_ENGINE_STATE)
		return 1;

	if (frame->dlc != CAN_DLC_ENGINE_STATE)
		return 2;

	uint8_t rpm_high = frame->data[0];
	uint8_t rpm_low = frame->data[1];
	uint16_t rpm_bits = (rpm_high << 8) | rpm_low;

	*rpm = rpm_bits;
	*load = frame->data[2];

	return 0;
}

int
encode_engine_timing(struct can_frame *frame, int ckp, int cmp, int knk) {
        frame->id = CAN_ID_ENGINE_TIMING;
        frame->dlc = CAN_DLC_ENGINE_TIMING;
        frame->data[0] = ckp;
        frame->data[1] = cmp;

        uint8_t knk_high = knk << 8;
        uint8_t knk_low = knk & 0xFF;
        frame->data[2] = knk_high;
        frame->data[3] = knk_low;

        return 0;
}

int
decode_engine_timing(struct can_frame *frame, int *ckp, int *cmp, int *knk) {
        if (frame->id != CAN_ID_ENGINE_TIMING)
                return 1;

        if (frame->id != CAN_DLC_ENGINE_TIMING)
                return 2;

        *ckp = frame->data[0];
        *cmp = frame->data[1];

        uint8_t knk_high = frame->data[2];
        uint8_t knk_low = frame->data[3];
	uint16_t knk_bits = (knk_high << 8) | knk_low;

        *knk = knk_bits;
        return 0;
}

int
encode_engine_pressures(struct can_frame *frame, int oil, int fuel) {
        frame->id = CAN_ID_ENGINE_PRESSURES;
        frame->dlc = CAN_DLC_ENGINE_PRESSURES;

        uint8_t oil_high = oil << 8;
        uint8_t oil_low = oil & 0xFF;
        frame->data[0] = oil_high;
        frame->data[1] = oil_low;

        uint8_t fuel_high = fuel << 8;
        uint8_t fuel_low = fuel & 0xFF;
        frame->data[2] = fuel_high;
        frame->data[3] = fuel_low;

        return 0;
}

int
decode_engine_pressures(struct can_frame *frame, int *oil, int *fuel) {
        if (frame->id != CAN_ID_ENGINE_PRESSURES)
                return 1;

        if (frame->dlc != CAN_DLC_ENGINE_PRESSURES)
                return 2;

        uint8_t oil_low = frame->data[0];
        uint8_t oil_high = frame->data[1];
	uint16_t oil_bits = (oil_high << 8) | oil_low;

        uint8_t fuel_low = frame->data[2];
        uint8_t fuel_high = frame->data[3];
        uint16_t fuel_bits = (fuel_high << 8) | fuel_low;

        return 0;
}

int
encode_engine_demand(struct can_frame *frame, int tps, int map) {
        frame->id = CAN_ID_ENGINE_DEMAND;
        frame->dlc = CAN_DLC_ENGINE_DEMAND;

        frame->data[0] = tps;
        frame->data[1] = map;

        return 0; 
}

int
decode_engine_demand(struct can_frame *frame, int *tps, int *map) {
	if (frame->id != CAN_ID_ENGINE_DEMAND)
		return 1;

	if (frame->dlc != CAN_DLC_ENGINE_DEMAND)
		return 2;

        *tps = frame->data[0];
        *map = frame->data[1];

        return 0;
}

// todo:add support for negative temps
int
encode_temps (struct can_frame *frame, int coolant, int iat, int oil) {
	frame->id = CAN_ID_ENGINE_TEMPS;
	frame->dlc = CAN_DLC_ENGINE_TEMPS;
	frame->data[0] = coolant;
	frame->data[1] = iat;
	frame->data[2] = oil;
	return 0;
}

int
decode_temps (struct can_frame *frame, int *coolant, int *iat, int *oil) {
	if (frame->id != CAN_ID_ENGINE_TEMPS)
		return 1;

	if (frame->dlc != CAN_DLC_ENGINE_TEMPS)
		return 2;

	*coolant = frame->data[0];
	*iat = frame->data[1];
	*oil = frame->data[2];

	return 0;
}


int
handle_parse_err (enum can_parse_err err) {
	switch (err) {
	case 0:
		break;
	case 1:
		printf ("[SRC/CAN.C] ERROR: ID MISMATCH");
		break;
	case 2:
		printf ("[SRC/CAN.C] ERROR: DLC MISMATCH");
		break;
	default:
		break;
	}

	return 0;
}
