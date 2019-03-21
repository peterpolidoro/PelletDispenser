// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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
  .version_major=4,
  .version_minor=1,
  .version_patch=1,
};

CONSTANT_STRING(state_string,"state");
CONSTANT_STRING(state_assay_not_started_string,"ASSAY_NOT_STARTED");
CONSTANT_STRING(state_assay_started_string,"ASSAY_STARTED");
CONSTANT_STRING(state_homing_string,"HOMING");
CONSTANT_STRING(state_move_to_deliver_string,"MOVE_TO_DELIVER");
CONSTANT_STRING(state_moving_to_deliver_string,"MOVING_TO_DELIVER");
CONSTANT_STRING(state_move_to_clean_string,"MOVE_TO_CLEAN");
CONSTANT_STRING(state_moving_to_clean_string,"MOVING_TO_CLEAN");
CONSTANT_STRING(state_wait_at_clean_string,"WAIT_AT_CLEAN");
CONSTANT_STRING(state_waiting_at_clean_string,"WAITING_AT_CLEAN");
CONSTANT_STRING(state_buzz_string,"BUZZ");
CONSTANT_STRING(state_buzzing_string,"BUZZING");
CONSTANT_STRING(state_ready_to_dispense_string,"READY_TO_DISPENSE");
CONSTANT_STRING(state_wait_to_dispense_string,"WAIT_TO_DISPENSE");
CONSTANT_STRING(state_waiting_to_dispense_string,"WAITING_TO_DISPENSE");
CONSTANT_STRING(state_move_to_dispense_string,"MOVE_TO_DISPENSE");
CONSTANT_STRING(state_moving_to_dispense_string,"MOVING_TO_DISPENSE");
CONSTANT_STRING(state_wait_to_return_string,"WAIT_TO_RETURN");
CONSTANT_STRING(state_waiting_to_return_string,"WAITING_TO_RETURN");
CONSTANT_STRING(state_assay_finished_string,"ASSAY_FINISHED");

const long seconds_per_minute = 60;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;

CONSTANT_STRING(set_value_string,"setValue");

// Clients
const size_t optical_switch_interface_address[1] =
{
  3,
};

const size_t h_bridge_controller_address[2] =
{
  3,
  3,
};

const size_t audio_controller_address[3] =
{
  3,
  3,
  3,
};

const size_t buzz_channels[BUZZ_CHANNEL_COUNT] =
{
  0,
};

// Pins

// Units
CONSTANT_STRING(mm_units,"mm");
CONSTANT_STRING(ms_units,"ms");
CONSTANT_STRING(seconds_units,"s");
CONSTANT_STRING(minutes_units,"min");
CONSTANT_STRING(hz_units,"Hz");

const long tone_frequency_min = 200;
const long tone_frequency_max = 22000;

// Properties
const long run_current_element_default = 20;

const long hold_current_element_default = 10;

const long hold_delay_element_default = 50;

CONSTANT_STRING(deliver_position_property_name,"deliverPosition");

CONSTANT_STRING(dispense_channel_position_property_name,"dispenseChannelPosition");
const long dispense_channel_position_default = -23;

CONSTANT_STRING(clean_position_property_name,"cleanPosition");

CONSTANT_STRING(clean_duration_property_name,"cleanDuration");
const long clean_duration_min = 1;
const long clean_duration_max = 10;
const long clean_duration_default = 3;

CONSTANT_STRING(buzz_period_property_name,"buzzPeriod");
const long buzz_period_min = 100;
const long buzz_period_max = 1000;
const long buzz_period_default = 100;

CONSTANT_STRING(buzz_on_duration_property_name,"buzzOnDuration");
const long buzz_on_duration_min = 5;
const long buzz_on_duration_max = 20;
const long buzz_on_duration_default = 20;

CONSTANT_STRING(buzz_count_property_name,"buzzCount");
const long buzz_count_min = 1;
const long buzz_count_max = 5;
const long buzz_count_default = 5;

CONSTANT_STRING(position_property_name,"position");
CONSTANT_STRING(position_left,"LEFT");
CONSTANT_STRING(position_right,"RIGHT");
modular_server::SubsetMemberType position_subset[POSITION_SUBSET_LENGTH] =
{
  {.cs_ptr=&position_left},
  {.cs_ptr=&position_right},
};
const ConstantString * const position_ptr_default = &position_left;

CONSTANT_STRING(position_tone_frequency_property_name,"positionToneFrequency");
const long position_tone_frequency_default = 5000;

CONSTANT_STRING(position_tone_volume_property_name,"positionToneVolume");
const long position_tone_volume_default = 25;

CONSTANT_STRING(position_tone_duration_property_name,"positionToneDuration");
const double position_tone_duration_min = 0.001;
const double position_tone_duration_max = 10.0;
const double position_tone_duration_default = 1.0;

CONSTANT_STRING(dispense_tone_frequency_property_name,"dispenseToneFrequency");
const long dispense_tone_frequency_default = 3400;

CONSTANT_STRING(dispense_tone_volume_property_name,"dispenseToneVolume");
const long dispense_tone_volume_default = 25;

CONSTANT_STRING(dispense_delay_property_name,"dispenseDelay");
const double dispense_delay_min = 0.0;
const double dispense_delay_max = 100.0;
const double dispense_delay_default = 4.0;

CONSTANT_STRING(return_delay_min_property_name,"returnDelayMin");
const double return_delay_min = 1.0;
const double return_delay_max = 3600.0;
const double return_delay_min_default = 10.0;

CONSTANT_STRING(return_delay_max_property_name,"returnDelayMax");
const double return_delay_max_default = 10.0;

// Parameters

// Functions
CONSTANT_STRING(set_client_property_values_function_name,"setClientPropertyValues");
CONSTANT_STRING(get_assay_status_function_name,"getAssayStatus");
CONSTANT_STRING(move_stage_to_deliver_position_function_name,"moveStageToDeliverPosition");
CONSTANT_STRING(move_stage_to_dispense_position_function_name,"moveStageToDispensePosition");
CONSTANT_STRING(move_stage_to_clean_position_function_name,"moveStageToCleanPosition");
CONSTANT_STRING(play_position_tone_function_name,"playPositionTone");
CONSTANT_STRING(play_dispense_tone_function_name,"playDispenseTone");
CONSTANT_STRING(stop_dispense_tone_function_name,"stopDispenseTone");

// Callbacks
CONSTANT_STRING(dispense_callback_name,"dispense");
CONSTANT_STRING(abort_callback_name,"abort");

// Errors
}
}
