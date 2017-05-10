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

CONSTANT_STRING(state_string,"state");
CONSTANT_STRING(state_assay_not_started_string,"ASSAY_NOT_STARTED");
CONSTANT_STRING(state_assay_started_string,"ASSAY_STARTED");
CONSTANT_STRING(state_homing_string,"HOMING");
CONSTANT_STRING(state_move_to_base_start_string,"MOVE_TO_BASE_START");
CONSTANT_STRING(state_moving_to_base_start_string,"MOVING_TO_BASE_START");
CONSTANT_STRING(state_move_to_deliver_string,"MOVE_TO_DELIVER");
CONSTANT_STRING(state_moving_to_deliver_string,"MOVING_TO_DELIVER");
CONSTANT_STRING(state_wait_to_play_tone_string,"WAIT_TO_PLAY_TONE");
CONSTANT_STRING(state_waiting_to_play_tone_string,"WAITING_TO_PLAY_TONE");
CONSTANT_STRING(state_play_tone_string,"PLAY_TONE");
CONSTANT_STRING(state_playing_tone_string,"PLAYING_TONE");

CONSTANT_STRING(state_move_to_dispense_string,"MOVE_TO_DISPENSE");
CONSTANT_STRING(state_moving_to_dispense_string,"MOVING_TO_DISPENSE");

CONSTANT_STRING(state_assay_finished_string,"ASSAY_FINISHED");
CONSTANT_STRING(state_move_to_base_stop_string,"MOVE_TO_BASE_STOP");
CONSTANT_STRING(state_moving_to_base_stop_string,"MOVING_TO_BASE_STOP");

const long seconds_per_minute = 60;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;

// Interrupts

// Units
CONSTANT_STRING(mm_unit,"mm");
CONSTANT_STRING(seconds_unit,"s");
CONSTANT_STRING(minutes_unit,"min");

// Properties
CONSTANT_STRING(base_positions_property_name,"basePositions");

CONSTANT_STRING(deliver_positions_property_name,"deliverPositions");

CONSTANT_STRING(dispense_positions_property_name,"dispensePositions");

CONSTANT_STRING(tone_delay_min_property_name,"toneDelayMin");
const long tone_delay_min = 0;
const long tone_delay_max = 60;
const long tone_delay_min_default = 2;

CONSTANT_STRING(tone_delay_max_property_name,"toneDelayMax");
const long tone_delay_max_default = 10;

CONSTANT_STRING(return_delay_property_name,"returnDelay");
const long return_delay_min = 1;
const long return_delay_max = 15;
const long return_delay_default = 15;

// Parameters

// Functions
CONSTANT_STRING(get_assay_status_function_name,"getAssayStatus");

// Callbacks
CONSTANT_STRING(deliver_callback_name,"deliver");
CONSTANT_STRING(abort_callback_name,"abort");

// Errors
}
}
