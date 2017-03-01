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
const double steps_per_position_unit_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    31.496, // steps/mm = (200steps/rev)/((0.250in/rev)*(25.4mm/in))
    31.496, // steps/mm = (200steps/rev)/((0.250in/rev)*(25.4mm/in))
    12.88, // steps/pellet
  };

const double velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    10,
    10,
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

const long current_scale_default[stepper_controller::constants::TMC26X_COUNT] =
  {
    50,
    50,
    50
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
