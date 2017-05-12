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
enum{STAGE_CHANNEL_COUNT=3};
enum{EVENT_COUNT_MAX=32};

extern const size_t h_bridge_controller_address[1];

extern const size_t optical_switch_interface_address[2];

extern const size_t audio_controller_address[3];

enum{BUZZ_CHANNEL_COUNT=1};
extern const size_t buzz_channels[BUZZ_CHANNEL_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const double steps_per_position_unit_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double velocity_min_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double acceleration_max_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const ConstantString * const switch_active_polarity_default;

extern const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const bool right_switches_enabled_default;

extern const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double home_velocity_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long current_scale_default[stepper_controller::constants::DRIVER_COUNT];

extern const long stage_channel_count_min;
extern const long stage_channel_count_max;
extern const long stage_channel_count_default;

extern const double stage_positions_min_default[STAGE_CHANNEL_COUNT];

extern const double stage_positions_max_default[STAGE_CHANNEL_COUNT];

extern const double base_positions_default[STAGE_CHANNEL_COUNT];

extern const double deliver_positions_default[STAGE_CHANNEL_COUNT];

extern const double dispense_positions_default[STAGE_CHANNEL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
