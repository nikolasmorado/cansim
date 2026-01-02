#include <stdint.h>
#include "can.h"

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
encode_temps (struct can_frame *frame, int coolant, int iat, int oil) {
	frame->id = CAN_ID_TEMPS;
        frame->dlc = CAN_DLC_TEMPS;
        frame->data[0] = coolant;
        frame->data[1] = iat;
        frame->data[2] = oil;
	return 0;
}

int
decode_temps (struct can_frame *frame, int *coolant, int *iat, int *oil) {
	if (frame->id != CAN_ID_TEMPS)
		return 1;

        if (frame->dlc != CAN_DLC_TEMPS)
                return 2;

        *coolant = frame->data[0];
        *iat = frame->data[1];
        *oil = frame->data[2];

	return 0;
}
