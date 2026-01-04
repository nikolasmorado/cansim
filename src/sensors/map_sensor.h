#ifndef MAP_SENSOR_H
#define MAP_SENSOR_H

struct map_sensor {
        float v_min;            // 0.5v
        float v_max;            // 4.5v

        float kpa_current;      // 0
};

#define IDLE_KPA 35.0
#define ATMO_KPA 100.0
#define MANF_TAU 0.05

void map_sensor_init (struct map_sensor *map); 
int map_sensor_read (struct map_sensor *map, float *v);
int map_sensor_update (struct map_sensor *map, float dt, int rpm, float tps);

#endif
