#ifndef CKP_SENSOR_H
#define CKP_SENSOR_H

struct ckp_sensor {
        float v_min;
        float v_max;

        int current_tooth;
};

// 0 indexed
#define TOOTH_COUNT 59
#define TOOTH_GAP 2

void ckp_sensor_init (struct ckp_sensor *ckp);
int ckp_sensor_read (struct ckp_sensor *ckp, float *v);
int ckp_sensor_update (struct ckp_sensor *ckp, float dt, int running, int rpm);

#endif
