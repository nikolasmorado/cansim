#include "can.h"
#include <stdio.h>

int
main () {
	struct can_frame f;
	int rpm = 0;
	int load = 0;

	int coolant = 0;
	int iat = 0;
	int oil = 0;

	printf ("ENCODING ENGINE STATE RPM = 2500, LOAD = 10\n");
	if (encode_engine_state (&f, 2500, 10))
		return 1;
	if (decode_engine_state (&f, &rpm, &load))
		return 1;
	printf ("DECODED ENGINE STATE RPM = %d, LOAD = %d\n", rpm, load);

	printf ("ENCODING TEMPS COOLANT = 60, IAT = 20, OIL = 120\n");
	if (encode_temps (&f, 60, 20, 120))
		return 1;
	if (decode_temps (&f, &coolant, &iat, &oil))
		return 1;
	printf ("DECODED TEMPS COOLANT = %d, IAT = %d, OIL = %d\n", coolant,
		iat, oil);

	return 0;
}
