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
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=8};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

// Interrupts

// Units
extern ConstantString mm_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const ConstantString * const switch_active_polarity_default;

// Parameters
extern ConstantString stage_positions_parameter_name;
extern const double stage_position_min;
extern const double stage_position_max;

// Functions
extern ConstantString dispense_pellet_function_name;
extern ConstantString enable_dispenser_function_name;
extern ConstantString disable_dispenser_function_name;
extern ConstantString home_stage_function_name;
extern ConstantString stage_homing_function_name;
extern ConstantString stage_homed_function_name;
extern ConstantString move_stage_to_function_name;
extern ConstantString get_stage_positions_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
