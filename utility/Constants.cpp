// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace pellet_dispenser
{
namespace constants
{
CONSTANT_STRING(device_name,"pellet_dispenser");

CONSTANT_STRING(firmware_name,"PelletDispenser");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

// Interrupts

// Units
CONSTANT_STRING(mm_unit,"mm");
CONSTANT_STRING(seconds_unit,"s");
CONSTANT_STRING(minutes_unit,"min");

// Properties
const ConstantString * const switch_active_polarity_default = &step_dir_controller::constants::polarity_high;

const long stage_channel_count_min = STAGE_CHANNEL_COUNT;
const long stage_channel_count_max = STAGE_CHANNEL_COUNT;
const long stage_channel_count_default = STAGE_CHANNEL_COUNT;

const double stage_position_min_default = 0;

const double stage_position_max_default = 140;

CONSTANT_STRING(base_position_property_name,"basePosition");
CONSTANT_STRING(deliver_position_property_name,"deliverPosition");

// Parameters

// Functions
CONSTANT_STRING(dispense_pellet_function_name,"dispensePellet");
CONSTANT_STRING(enable_dispenser_function_name,"enableDispenser");
CONSTANT_STRING(disable_dispenser_function_name,"disableDispenser");

// Callbacks
CONSTANT_STRING(deliver_callback_name,"deliver");
CONSTANT_STRING(abort_callback_name,"abort");

// Errors
}
}
