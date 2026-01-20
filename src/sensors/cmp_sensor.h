#ifndef CMP_SENSOR_H
#define CMP_SENSOR_H

struct cmp_sensor {
        float v_min;
        float v_max;

        int current_tooth;
};

#define TOOTH_COUNT 4
#define TOOTH_GAP 3

void cmp_sensor_init(struct cmp_sensor *cmp);
int cmp_sensor_read(struct cmp_sensor *cmp, float *v);
int cmp_sensor_update(struct cmp_sensor *cmp, float dt, int running, int rpm);

#endif
