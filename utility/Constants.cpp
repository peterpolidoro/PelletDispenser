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

// Properties
const ConstantString * const switch_active_polarity_default = &step_dir_controller::constants::polarity_high;

// Parameters
CONSTANT_STRING(stage_positions_parameter_name,"stage_positions");
const double stage_position_min = 0;
const double stage_position_max = 140;

// Functions
CONSTANT_STRING(dispense_pellet_function_name,"dispensePellet");
CONSTANT_STRING(enable_dispenser_function_name,"enableDispenser");
CONSTANT_STRING(disable_dispenser_function_name,"disableDispenser");
CONSTANT_STRING(home_stage_function_name,"homeStage");
CONSTANT_STRING(stage_homing_function_name,"stageHoming");
CONSTANT_STRING(stage_homed_function_name,"stageHomed");
CONSTANT_STRING(move_stage_to_function_name,"moveStageTo");
CONSTANT_STRING(get_stage_positions_function_name,"getStagePositions");

// Callbacks

// Errors
}
}
