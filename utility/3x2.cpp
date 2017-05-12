// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace pellet_dispenser
{
namespace constants
{
const size_t h_bridge_controller_address[1] =
  {
    3,
  };

const size_t optical_switch_interface_address[2] =
  {
    3,
    3,
  };

const size_t audio_controller_address[3] =
  {
    3,
    3,
    3,
  };

// Interrupts

// Units

// Properties
const double steps_per_position_unit_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    31.496, // steps/mm = (200steps/rev)/((0.250in/rev)*(25.4mm/in))
    31.496, // steps/mm = (200steps/rev)/((0.250in/rev)*(25.4mm/in))
    12.88, // steps/pellet
  };

const double velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    20,
    20,
    5,
  };

const double velocity_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    2,
    2,
    1,
  };

const double acceleration_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    100,
    100,
    50,
  };

const ConstantString * const switch_active_polarity_default = &step_dir_controller::constants::polarity_high;

const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    true,
    true,
    true,
  };

const bool right_switches_enabled_default = true;

const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    false,
    false,
    true,
  };

const double home_velocity_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    -10,
    -10,
    5,
  };

const long current_scale_default[stepper_controller::constants::DRIVER_COUNT] =
  {
    50,
    50,
    50
  };

const long stage_channel_count_min = STAGE_CHANNEL_COUNT;
const long stage_channel_count_max = STAGE_CHANNEL_COUNT;
const long stage_channel_count_default = STAGE_CHANNEL_COUNT;

const double stage_positions_min_default[STAGE_CHANNEL_COUNT] =
  {
    0,
    0,
    -19,
  };

const double stage_positions_max_default[STAGE_CHANNEL_COUNT] =
  {
    20,
    140,
    0,
  };

const double base_positions_default[STAGE_CHANNEL_COUNT] =
  {
    20,
    130,
    -18,
  };

const double deliver_positions_default[STAGE_CHANNEL_COUNT] =
  {
    20,
    140,
    -18
  };

const double dispense_positions_default[STAGE_CHANNEL_COUNT] =
  {
    20,
    140,
    -5
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
