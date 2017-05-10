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
enum{PROPERTY_COUNT_MAX=8};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

struct AssayStatus
{
  const ConstantString * state_ptr;
};

extern ConstantString state_string;
extern ConstantString state_assay_not_started_string;
extern ConstantString state_assay_started_string;
extern ConstantString state_homing_string;
extern ConstantString state_move_to_base_start_string;
extern ConstantString state_moving_to_base_start_string;
extern ConstantString state_move_to_deliver_string;
extern ConstantString state_moving_to_deliver_string;
extern ConstantString state_wait_to_play_tone_string;
extern ConstantString state_waiting_to_play_tone_string;
extern ConstantString state_play_tone_string;
extern ConstantString state_playing_tone_string;

extern ConstantString state_move_to_dispense_string;
extern ConstantString state_moving_to_dispense_string;

extern ConstantString state_move_to_base_stop_string;
extern ConstantString state_moving_to_base_stop_string;
extern ConstantString state_assay_finished_string;

extern const long seconds_per_minute;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;

// Interrupts

// Units
extern ConstantString mm_unit;
extern ConstantString seconds_unit;
extern ConstantString minutes_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString base_positions_property_name;

extern ConstantString deliver_positions_property_name;

extern ConstantString dispense_positions_property_name;

extern ConstantString tone_delay_min_property_name;
extern const long tone_delay_min;
extern const long tone_delay_max;
extern const long tone_delay_min_default;

extern ConstantString tone_delay_max_property_name;
extern const long tone_delay_max_default;

extern ConstantString return_delay_property_name;
extern const long return_delay_min;
extern const long return_delay_max;
extern const long return_delay_default;

// Parameters

// Functions
extern ConstantString get_assay_status_function_name;

// Callbacks
extern ConstantString deliver_callback_name;
extern ConstantString abort_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
