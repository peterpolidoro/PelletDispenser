// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace pellet_dispenser
{
namespace constants
{
// Pins

// Units
// Properties
const long steps_per_position_units_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  2520, // microsteps/mm = (24steps/rev)*(256microsteps/step)/((0.048in/rev)*(25.4mm/in))
  8063, // microsteps/mm = (200steps/rev)*(256microsteps/step)/((0.250in/rev)*(25.4mm/in))
  8063, // microsteps/mm = (200steps/rev)*(256microsteps/step)/((0.250in/rev)*(25.4mm/in))
};

const long velocity_max_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  7,
  20,
  20,
};

const long velocity_min_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  1,
  2,
  2,
};

const long acceleration_max_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  1200,
  1200,
  1200,
};

const long home_velocity_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  -7,
  -20,
  -20,
};

const bool right_switches_enabled_default[step_dir_controller::constants::CONTROLLER_COUNT_MAX] =
{
  right_switches_enabled_element_default,
  right_switches_enabled_element_default,
  right_switches_enabled_element_default,
};

const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
};

const bool invert_driver_direction_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  true,
  false,
  false,
};

const long run_current_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  run_current_0_element_default,
  run_current_1_2_element_default,
  run_current_1_2_element_default,
};

const long hold_current_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  hold_current_0_element_default,
  hold_current_1_2_element_default,
  hold_current_1_2_element_default,
};

const long hold_delay_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  hold_delay_element_default,
  hold_delay_element_default,
  hold_delay_element_default,
};

const long stage_position_min_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  0,
  0,
  0,
};

const long stage_position_max_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  20,
  80,
  80,
};

const long buzz_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  10,
  25,
  65,
};

const long load_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  1,
  25,
  65,
};

const long next_deliver_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  17,
  26,
  64,
};

const long next_dispense_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  13,
  21,
  74,
};

const long dispense_velocity_default[stepper_controller::constants::CHANNEL_COUNT_MAX] =
{
  500,
  100,
  100,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
