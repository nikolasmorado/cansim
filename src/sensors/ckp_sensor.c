#include "ckp_sensor.h"

void
ckp_sensor_init(struct ckp_sensor *ckp) {
        ckp->v_min = 0;
        ckp->v_max = 5.;
        ckp->current_tooth = 0;
}

int
ckp_sensor_read(struct ckp_sensor *ckp, float *v) {
        if (ckp->current_tooth > TOOTH_COUNT)
                return 1;

        if (ckp->current_tooth <= TOOTH_COUNT - TOOTH_GAP)
                *v = ckp->v_max;
        else 
                *v =ckp->v_min;

        return 0;
}

int
ckp_sensor_update(struct ckp_sensor *ckp, float dt, int running, int rpm) {
        if (!running)
                return 0;

        if (ckp->current_tooth > TOOTH_COUNT)
                return 1;

        int sec_per_rev = 60. / rpm;
        int sec_per_tooth = sec_per_rev / 60.;
        float teeth_passed = dt / sec_per_tooth;

        int nct = ckp->current_tooth + (int)teeth_passed;

        if (nct > TOOTH_COUNT)
                ckp->current_tooth = nct - TOOTH_COUNT;
        else
                ckp->current_tooth = nct;

        return 0;
}

