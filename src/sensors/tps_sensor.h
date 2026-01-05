#ifndef TPS_SENSOR_H
#define TPS_SENSOR_H

struct tps_sensor {
	float v_min;
	float v_max;

	float current_percent;
};

#define DBW_SLEW 1.5

void tps_sensor_init (struct tps_sensor *tps);
int tps_sensor_read (struct tps_sensor *tps, float *v);
int tps_sensor_update (struct tps_sensor *tps, float dt, float target);

#endif
