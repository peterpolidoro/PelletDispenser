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
enum{PROPERTY_COUNT_MAX=12};
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
extern ConstantString state_buzz_string;
extern ConstantString state_buzzing_string;
extern ConstantString state_wait_to_play_tone_string;
extern ConstantString state_waiting_to_play_tone_string;
extern ConstantString state_play_tone_string;
extern ConstantString state_playing_tone_string;
extern ConstantString state_move_to_dispense_string;
extern ConstantString state_moving_to_dispense_string;
extern ConstantString state_wait_to_return_string;
extern ConstantString state_waiting_to_return_string;
extern ConstantString state_move_to_base_stop_string;
extern ConstantString state_moving_to_base_stop_string;
extern ConstantString state_assay_finished_string;

extern const long seconds_per_minute;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;

// Interrupts

// Units
extern ConstantString mm_units;
extern ConstantString ms_units;
extern ConstantString seconds_units;
extern ConstantString minutes_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString base_positions_property_name;

extern ConstantString deliver_positions_property_name;

extern ConstantString dispense_positions_property_name;

extern ConstantString buzz_period_property_name;
extern const long buzz_period_min;
extern const long buzz_period_max;
extern const long buzz_period_default;

extern ConstantString buzz_on_duration_property_name;
extern const long buzz_on_duration_min;
extern const long buzz_on_duration_max;
extern const long buzz_on_duration_default;

extern ConstantString buzz_count_property_name;
extern const long buzz_count_min;
extern const long buzz_count_max;
extern const long buzz_count_default;

extern ConstantString tone_delay_min_property_name;
extern const long tone_delay_min;
extern const long tone_delay_max;
extern const long tone_delay_min_default;

extern ConstantString tone_delay_max_property_name;
extern const long tone_delay_max_default;

extern ConstantString tone_frequency_property_name;
extern const long tone_frequency_min;
extern const long tone_frequency_max;
extern const long tone_frequency_default;

extern ConstantString tone_duration_property_name;
extern const long tone_duration_min;
extern const long tone_duration_max;
extern const long tone_duration_default;

extern ConstantString tone_volume_property_name;
extern const double tone_volume_default;

extern ConstantString return_delay_property_name;
extern const double return_delay_min;
extern const double return_delay_max;
extern const double return_delay_default;

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
