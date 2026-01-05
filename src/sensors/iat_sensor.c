#include "iat_sensor.h"

// i havent gone and verified that this table lines up with my sensor as well,
// for now using info from these sources:
//
// https://www.jeepforum.com/threads/iat-resistance-value.1428278/
// 5-90 here says that AMC and chrysler use the GM thermistors, and was
// kind enough to share a curve he found. The engine I'm putting in SHOULD
// follow these curves if he's right, and I'm going to trust his data for now.
//
// https://www.jeepforum.com/threads/coolant-temperature-sensor-ohms.915224/
// parity with numbers here for the 4.0 gives me confidence.
//
// I'll verify on my own before any real testing.
//
// ignore this function being bad, i dont care, this may not even be real data
// so im not going to linearlly interpolate it or do anything good, chain of
// ifs is fine.

static float
temp_to_res (float t) {
	if (t <= -40)
		return 100700;
	if (t <= -18)
		return 25000;
	if (t <= -7)
		return 13500;
	if (t <= 4)
		return 7500;
	if (t <= 20)
		return 3400;
	if (t <= 38)
		return 1600;
	if (t <= 70)
		return 450;
	if (t <= 100)
		return 185;
	else
		return 0;
}

void
iat_sensor_init (struct iat_sensor *iat, float ambient) {
	iat->r_pullup = 10000;
	iat->v_ref = 5.;
	iat->temp_amb = ambient;
	iat->temp_cur = ambient;
}

int
iat_sensor_read (struct iat_sensor *iat, float *v) {
	float r_therm = temp_to_res (iat->temp_cur);

	if (r_therm == 0)
		return 1;

	*v = iat->v_ref * (r_therm / iat->r_pullup + r_therm);
	return 0;
}

int
iat_sensor_update (struct iat_sensor *iat, float ambient) {
	// ill make this heat soak later, no point in stepping the
	// iat temp to ambient for now.
	return 0;
}
