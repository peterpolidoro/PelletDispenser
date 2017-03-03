// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef PELLET_DISPENSER_3X2_CONSTANTS_H
#define PELLET_DISPENSER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace pellet_dispenser
{
namespace constants
{
// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const double steps_per_position_unit_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double velocity_min_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double acceleration_max_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double home_velocity_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long current_scale_default[stepper_controller::constants::TMC26X_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
