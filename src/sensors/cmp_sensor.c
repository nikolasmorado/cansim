#include "cmp_sensor.h"

void
cmp_sensor_init(struct cmp_sensor *cmp) {
        cmp->v_min = 0;
        cmp->v_max = 5.;
        cmp->current_tooth = 0;
}

int
cmp_sensor_read(struct cmp_sensor *cmp, float *v) {
        if (cmp->current_tooth > TOOTH_COUNT)
                return 1;

        if (cmp->current_tooth <= TOOTH_COUNT - TOOTH_GAP)
                *v = cmp->v_max;
        else 
                *v =cmp->v_min;

        return 0;
}

int
cmp_sensor_update(struct cmp_sensor *cmp, float dt, int running, int rpm) {
        if (!running)
                return 0;

        if (cmp->current_tooth > TOOTH_COUNT)
                return 1;

        int sec_per_rev = 60. / rpm;
        int sec_per_tooth = sec_per_rev / 60.;
        float teeth_passed = dt / sec_per_tooth;

        int nct = cmp->current_tooth + (int)teeth_passed;

        if (nct > TOOTH_COUNT)
                cmp->current_tooth = nct - TOOTH_COUNT;
        else
                cmp->current_tooth = nct;

        return 0;
}

