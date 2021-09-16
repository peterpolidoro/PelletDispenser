// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef PELLET_DISPENSER_CONSTANTS_H
#define PELLET_DISPENSER_CONSTANTS_H
#include <ConstantVariable.h>
#include <StepDirController.h>
#include <StepperController.h>
#include <StageController.h>

#include <AudioController.h>
#include <PowerSwitchController.h>


namespace pellet_dispenser
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=21};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=4};
enum{CALLBACK_COUNT_MAX=3};

enum{EVENT_COUNT_MAX=32};

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
extern ConstantString state_move_to_buzz_string;
extern ConstantString state_moving_to_buzz_string;
extern ConstantString state_move_to_load_string;
extern ConstantString state_moving_to_load_string;
extern ConstantString state_wait_at_load_string;
extern ConstantString state_waiting_at_load_string;
extern ConstantString state_move_to_next_deliver_string;
extern ConstantString state_moving_to_next_deliver_string;
extern ConstantString state_ready_to_dispense_string;
extern ConstantString state_wait_to_dispense_string;
extern ConstantString state_waiting_to_dispense_string;
extern ConstantString state_move_to_dispense_string;
extern ConstantString state_moving_to_dispense_string;
extern ConstantString state_wait_to_return_string;
extern ConstantString state_waiting_to_return_string;
extern ConstantString state_assay_finished_string;
extern ConstantString state_buzz_string;
extern ConstantString state_buzzing_string;
extern ConstantString state_tap_string;
extern ConstantString state_tapping_string;

extern const long seconds_per_minute;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;

extern ConstantString set_value_string;

// Clients
extern const size_t audio_controller_address[1];

extern const size_t power_switch_controller_address[2];

enum{BUZZ_CHANNEL_COUNT=1};
extern const size_t buzz_channels[BUZZ_CHANNEL_COUNT];
extern const size_t buzz_channel_group;

// Pins

// Units
extern ConstantString mm_units;
extern ConstantString ms_units;
extern ConstantString seconds_units;
extern ConstantString minutes_units;
extern ConstantString percent_units;

extern const long tone_frequency_min;
extern const long tone_frequency_max;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern const long velocity_max_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern const long velocity_min_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern const long acceleration_max_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern const long home_velocity_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern const bool right_switches_enabled_default[step_dir_controller::constants::CONTROLLER_COUNT_MAX];
extern const bool right_switches_enabled_element_default;

extern const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX];
extern const bool right_switch_stop_enabled_element_default;

extern const bool invert_driver_direction_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern const long run_current_default[stepper_controller::constants::CHANNEL_COUNT_MAX];
extern const long run_current_0_element_default;
extern const long run_current_1_2_element_default;

extern const long hold_current_default[stepper_controller::constants::CHANNEL_COUNT_MAX];
extern const long hold_current_0_element_default;
extern const long hold_current_1_2_element_default;

extern const long hold_delay_default[stepper_controller::constants::CHANNEL_COUNT_MAX];
extern const long hold_delay_element_default;

extern const long stage_position_min_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern const long stage_position_max_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern ConstantString buzz_position_property_name;
extern const long buzz_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern ConstantString load_position_property_name;
extern const long load_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern ConstantString next_deliver_position_property_name;
extern const long next_deliver_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern ConstantString next_dispense_position_property_name;
extern const long next_dispense_position_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

extern ConstantString position_property_name;
enum{POSITION_SUBSET_LENGTH=2};
extern ConstantString position_left;
extern ConstantString position_right;
extern modular_server::SubsetMemberType position_subset[POSITION_SUBSET_LENGTH];
extern const ConstantString * const position_ptr_default;

extern ConstantString position_tone_frequency_property_name;
extern const long position_tone_frequency_default;

extern ConstantString position_tone_volume_property_name;
extern const long position_tone_volume_default;

extern ConstantString position_tone_delay_property_name;
extern const double position_tone_delay_min;
extern const double position_tone_delay_max;
extern const double position_tone_delay_default;

extern ConstantString position_tone_duration_property_name;
extern const double position_tone_duration_min;
extern const double position_tone_duration_max;
extern const double position_tone_duration_default;

extern ConstantString dispense_delay_property_name;
extern const double dispense_delay_min;
extern const double dispense_delay_max;
extern const double dispense_delay_default;

extern ConstantString return_delay_min_property_name;
extern const double return_delay_min;
extern const double return_delay_max;
extern const double return_delay_min_default;

extern ConstantString return_delay_max_property_name;
extern const double return_delay_max_default;

extern ConstantString buzz_power_property_name;
extern const long buzz_power_min;
extern const long buzz_power_max;
extern const long buzz_power_default;

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

extern ConstantString wait_at_load_duration_property_name;
extern const long wait_at_load_duration_min;
extern const long wait_at_load_duration_max;
extern const long wait_at_load_duration_default;

extern ConstantString tap_period_property_name;
extern const long tap_period_min;
extern const long tap_period_max;
extern const long tap_period_default;

extern ConstantString tap_on_duration_property_name;
extern const long tap_on_duration_min;
extern const long tap_on_duration_max;
extern const long tap_on_duration_default;

extern ConstantString tap_count_property_name;
extern const long tap_count_min;
extern const long tap_count_max;
extern const long tap_count_default;

extern ConstantString dispense_velocity_property_name;
extern const long dispense_velocity_min;
extern const long dispense_velocity_max;
extern const long dispense_velocity_default[stepper_controller::constants::CHANNEL_COUNT_MAX];

// Parameters

// Functions
extern ConstantString set_client_property_values_function_name;
extern ConstantString get_assay_status_function_name;
extern ConstantString play_position_tone_function_name;
extern ConstantString buzz_function_name;

// Callbacks
extern ConstantString start_assay_callback_name;
extern ConstantString dispense_callback_name;
extern ConstantString abort_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
