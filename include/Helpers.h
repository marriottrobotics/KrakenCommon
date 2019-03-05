#ifndef EMS_HELPERS
#define EMS_HELPERS

#define MOTOR_DEF MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES
#define MOTOR_REV MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES

#define ABS(x) (((x) >= 0) ? (x) : (-(x)))

const bool RED = true;
const bool BLUE = false;
const bool TOP = true;
const bool BOTTOM = false;

#endif /* end of include guard: EMS_HELPERS */
