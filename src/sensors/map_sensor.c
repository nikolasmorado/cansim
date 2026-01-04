#include "map_sensor.h"

void
map_sensor_init (struct map_sensor *map) {
        map->v_min = 0.5;
        map->v_max = 4.5;

        map->kpa_current = 0;
}

int
map_sensor_read (struct map_sensor *map, float *v) {
        float cur = map->v_min + 
                (map->kpa_current / 100) * 
                (map->v_min * map->v_max);

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
map_sensor_update (struct map_sensor *map, float dt, int rpm, float tps) {
        float target = IDLE_KPA + (tps / 100) * (ATMO_KPA - IDLE_KPA);
        float alpha = dt / (MANF_TAU / dt);

        // When the throttle is mostly closed, and the engine is revving high
        // we can expect the KPA to be a bit lower than if the RPM was lower.
        //
        // The engine is sucking more air than the TB is giving it so theres
        // vacuum.
        //
        // 5000 - 800 = 4200, high enough in my head? Can probs find math later
        // done by people smarter than me.
        //
        // rpm - 800 to accomadate idle

        if (tps < 10) {
                float rpm_adj = (rpm - 800) * 0.005;
                if (rpm_adj > 0)
                        target += rpm_adj;
        }

        map->kpa_current += (target - map->kpa_current) * alpha;

        return 0;
}
