// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef PELLET_DISPENSER_CONSTANTS_H
#define PELLET_DISPENSER_CONSTANTS_H
#include "ConstantVariable.h"
#include "StepDirController.h"
#include "StepperController.h"


namespace pellet_dispenser
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=4};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=3};
enum{CALLBACK_COUNT_MAX=2};

enum{STAGE_CHANNEL_COUNT=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

// Interrupts

// Units
extern ConstantString mm_unit;
extern ConstantString seconds_unit;
extern ConstantString minutes_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const ConstantString * const switch_active_polarity_default;

extern const bool right_switches_enabled_default;

extern const long stage_channel_count_min;
extern const long stage_channel_count_max;
extern const long stage_channel_count_default;

extern const double stage_position_min_default;

extern const double stage_position_max_default;

extern ConstantString base_position_property_name;

extern ConstantString deliver_position_property_name;

// Parameters
extern const double stage_position_min;
extern const double stage_position_max;

// Functions
extern ConstantString home_rig_function_name;
// extern ConstantString rig_homed_function_name;
// extern ConstantString dispense_pellet_function_name;
// extern ConstantString enable_dispenser_function_name;
// extern ConstantString disable_dispenser_function_name;

// Callbacks
extern ConstantString deliver_callback_name;
extern ConstantString abort_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
