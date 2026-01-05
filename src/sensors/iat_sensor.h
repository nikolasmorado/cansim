#ifndef IAT_SENSOR_H
#define IAT_SENSOR_H

struct iat_sensor {
	float r_pullup;
	float v_ref;

	float temp_amb;
	float temp_cur;
};

void iat_sensor_init (struct iat_sensor *iat, float ambient);
int iat_sensor_read (struct iat_sensor *iat, float *v);
int iat_sensor_update (struct iat_sensor *iat, float ambient);

#endif
