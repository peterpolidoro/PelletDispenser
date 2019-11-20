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
  .version_major=8,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(state_string,"state");
CONSTANT_STRING(state_assay_not_started_string,"ASSAY_NOT_STARTED");
CONSTANT_STRING(state_assay_started_string,"ASSAY_STARTED");
CONSTANT_STRING(state_homing_string,"HOMING");
CONSTANT_STRING(state_move_to_next_deliver_string,"MOVE_TO_NEXT_DELIVER");
CONSTANT_STRING(state_moving_to_next_deliver_string,"MOVING_TO_NEXT_DELIVER");
CONSTANT_STRING(state_move_to_shake_string,"MOVE_TO_SHAKE");
CONSTANT_STRING(state_moving_to_shake_string,"MOVING_TO_SHAKE");
CONSTANT_STRING(state_wait_at_shake_string,"WAIT_AT_SHAKE");
CONSTANT_STRING(state_waiting_at_shake_string,"WAITING_AT_SHAKE");
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
const size_t audio_controller_address[1] =
{
  3,
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
const long run_current_0_element_default = 4;
const long run_current_1_2_element_default = 20;

const long hold_current_0_element_default = 2;
const long hold_current_1_2_element_default = 10;

const long hold_delay_element_default = 50;

CONSTANT_STRING(next_deliver_position_property_name,"nextDeliverPosition");

CONSTANT_STRING(dispense_channel_position_property_name,"dispenseChannelPosition");
const long dispense_channel_position_default = 10;

CONSTANT_STRING(shake_position_property_name,"shakePosition");

CONSTANT_STRING(shake_duration_property_name,"shakeDuration");
const long shake_duration_min = 1;
const long shake_duration_max = 10;
const long shake_duration_default = 3;

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
const long position_tone_frequency_default = 5400;

CONSTANT_STRING(position_tone_volume_property_name,"positionToneVolume");
const long position_tone_volume_default = 25;

CONSTANT_STRING(position_tone_delay_property_name,"positionToneDelay");
const double position_tone_delay_min = 0.0;
const double position_tone_delay_max = 100.0;
const double position_tone_delay_default = 3.0;

CONSTANT_STRING(position_tone_duration_property_name,"positionToneDuration");
const double position_tone_duration_min = 0.001;
const double position_tone_duration_max = 10.0;
const double position_tone_duration_default = 1.0;

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
CONSTANT_STRING(play_position_tone_function_name,"playPositionTone");

// Callbacks
CONSTANT_STRING(start_assay_callback_name,"startAssay");
CONSTANT_STRING(dispense_callback_name,"dispense");
CONSTANT_STRING(abort_callback_name,"abort");

// Errors
}
}
