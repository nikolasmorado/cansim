#ifndef BAT_SENSOR_H
#define BAT_SENSOR_H

struct bat_sensor {
        float v_min;
        float v_max;
};

void bat_sensor_init (struct bat_sensor *bat);
int bat_sensor_read (struct bat_sensor *bat, float *v);
int bat_sensor_update (struct bat_sensor *bat);

#endif
