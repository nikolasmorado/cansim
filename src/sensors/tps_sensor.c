#include "tps_sensor.h"

void
tps_sensor_init (struct tps_sensor *tps) {
	tps->v_min = 0.5;
	tps->v_max = 4.5;
	tps->current_percent = 0;
}

int
tps_sensor_read (struct tps_sensor *tps, float *v) {
	float cur = tps->v_min
		    + (tps->current_percent / 100) * (tps->v_min * tps->v_max);

	if (cur < 0.5) {
		return 1;
	}
	if (cur > 4.5) {
		return 2;
	}

	*v = cur;

	return 0;
}

int
tps_sensor_update (struct tps_sensor *tps, float dt, float target) {
	if (target < 0 || target > 100) {
		return 3;
	}

	float dc = target - tps->current_percent;
	float max_change = dt * DBW_SLEW;

	if (dc > max_change) {
		tps->current_percent += max_change;
	} else if (dc < -max_change) {
		tps->current_percent -= max_change;
	} else {
		tps->current_percent = target;
	}

	return 0;
}
