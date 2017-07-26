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

// Interrupts

// Units

// Properties
const double steps_per_position_units_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    31.496, // steps/mm = (200steps/rev)/((0.250in/rev)*(25.4mm/in))
    31.496, // steps/mm = (200steps/rev)/((0.250in/rev)*(25.4mm/in))
    12.88, // steps/pellet
  };

const double velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    40,
    40,
    20,
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

const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    false,
    false,
    true,
  };

const double home_velocity_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    -20,
    -20,
    5,
  };

const long run_current_default[stepper_controller::constants::DRIVER_COUNT] =
  {
    run_current_element_default,
    run_current_element_default,
    run_current_element_default,
  };

const long hold_current_default[stepper_controller::constants::DRIVER_COUNT] =
  {
    hold_current_element_default,
    hold_current_element_default,
    hold_current_element_default,
  };

const long hold_delay_default[stepper_controller::constants::DRIVER_COUNT] =
  {
    hold_delay_element_default,
    hold_delay_element_default,
    hold_delay_element_default,
  };

const long stage_channel_count_min = step_dir_controller::constants::CHANNEL_COUNT;
const long stage_channel_count_max = step_dir_controller::constants::CHANNEL_COUNT;
const long stage_channel_count_default = step_dir_controller::constants::CHANNEL_COUNT;

const double stage_positions_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    0,
    0,
    -19,
  };

const double stage_positions_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    20,
    140,
    0,
  };

const double base_positions_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    20,
    130,
    -17.5,
  };

const double deliver_positions_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    5,
    135,
    -17.5,
  };

const double dispense_positions_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    5,
    135,
    -5
  };

const bool inverted[optical_switch_interface::constants::OUTPUT_COUNT] =
  {
    false,
    true,
    false,
    false,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
