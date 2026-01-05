#ifndef CLT_SENSOR_H
#define CLT_SENSOR_H

struct clt_sensor {
	float r_pullup;
	float v_ref;

	float temp_cur;
};

#define OP_TEMP 100
#define CLT_TAU 80
#define AMB_TEMP 20

void clt_sensor_init (struct clt_sensor *clt);
int clt_sensor_read (struct clt_sensor *clt, float *v);
int clt_sensor_update (struct clt_sensor *clt, float dt, int running);

#endif
