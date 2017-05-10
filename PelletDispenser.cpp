// ----------------------------------------------------------------------------
// PelletDispenser.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "PelletDispenser.h"


using namespace pellet_dispenser;

PelletDispenser::PelletDispenser()
{
}

void PelletDispenser::setup()
{
  // Parent Setup
  StageController::setup();

  // Event Controller Setup
  event_controller_.setup();

  // Pin Setup

  // Assay Status Setup
  assay_status_.state_ptr = &constants::state_assay_not_started_string;

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & steps_per_position_unit_property = modular_server_.property(step_dir_controller::constants::steps_per_position_unit_property_name);
  steps_per_position_unit_property.setDefaultValue(constants::steps_per_position_unit_default);

  modular_server::Property & velocity_max_property = modular_server_.property(step_dir_controller::constants::velocity_max_property_name);
  velocity_max_property.setDefaultValue(constants::velocity_max_default);

  modular_server::Property & velocity_min_property = modular_server_.property(step_dir_controller::constants::velocity_min_property_name);
  velocity_min_property.setDefaultValue(constants::velocity_min_default);

  modular_server::Property & acceleration_max_property = modular_server_.property(step_dir_controller::constants::acceleration_max_property_name);
  acceleration_max_property.setDefaultValue(constants::acceleration_max_default);

  modular_server::Property & switch_active_polarity_property = modular_server_.property(step_dir_controller::constants::switch_active_polarity_property_name);
  switch_active_polarity_property.setDefaultValue(constants::switch_active_polarity_default);

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::left_switch_stop_enabled_property_name);
  left_switch_stop_enabled_property.setDefaultValue(constants::left_switch_stop_enabled_default);

  modular_server::Property & right_switches_enabled_property = modular_server_.property(step_dir_controller::constants::right_switches_enabled_property_name);
  right_switches_enabled_property.setDefaultValue(constants::right_switches_enabled_default);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setDefaultValue(constants::right_switch_stop_enabled_default);

  modular_server::Property & home_velocity_property = modular_server_.property(step_dir_controller::constants::home_velocity_property_name);
  home_velocity_property.setDefaultValue(constants::home_velocity_default);

  modular_server::Property & current_scale_property = modular_server_.property(stepper_controller::constants::current_scale_property_name);
  current_scale_property.setDefaultValue(constants::current_scale_default);

  modular_server::Property & stage_channel_count_property = modular_server_.property(stage_controller::constants::stage_channel_count_property_name);
  stage_channel_count_property.setDefaultValue(constants::stage_channel_count_default);
  stage_channel_count_property.setRange(constants::stage_channel_count_min,constants::stage_channel_count_max);
  stage_channel_count_property.setArrayLengthRange(constants::stage_channel_count_min,constants::stage_channel_count_max);

  modular_server::Property & stage_positions_min_property = modular_server_.property(stage_controller::constants::stage_positions_min_property_name);
  stage_positions_min_property.setDefaultValue(constants::stage_positions_min_default);

  modular_server::Property & stage_positions_max_property = modular_server_.property(stage_controller::constants::stage_positions_max_property_name);
  stage_positions_max_property.setDefaultValue(constants::stage_positions_max_default);

  modular_server::Property & base_positions_property = modular_server_.createProperty(constants::base_positions_property_name,constants::base_positions_default);

  modular_server::Property & deliver_positions_property = modular_server_.createProperty(constants::deliver_positions_property_name,constants::deliver_positions_default);

  modular_server::Property & dispense_positions_property = modular_server_.createProperty(constants::dispense_positions_property_name,constants::dispense_positions_default);

  modular_server::Property & tone_delay_min_property = modular_server_.createProperty(constants::tone_delay_min_property_name,constants::tone_delay_min_default);
  tone_delay_min_property.setUnits(constants::seconds_unit);
  tone_delay_min_property.setRange(constants::tone_delay_min,constants::tone_delay_max);

  modular_server::Property & tone_delay_max_property = modular_server_.createProperty(constants::tone_delay_max_property_name,constants::tone_delay_max_default);
  tone_delay_max_property.setUnits(constants::seconds_unit);
  tone_delay_max_property.setRange(constants::tone_delay_min,constants::tone_delay_max);

  modular_server::Property & return_delay_property = modular_server_.createProperty(constants::return_delay_property_name,constants::return_delay_default);
  return_delay_property.setUnits(constants::minutes_unit);
  return_delay_property.setRange(constants::return_delay_min,constants::return_delay_max);

  // Parameters
  modular_server::Parameter & stage_positions_parameter = modular_server_.parameter(stage_controller::constants::stage_positions_parameter_name);
  stage_positions_parameter.setUnits(constants::mm_unit);

  // Functions
  modular_server::Function & get_assay_status_function = modular_server_.createFunction(constants::get_assay_status_function_name);
  get_assay_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::getAssayStatusHandler));
  get_assay_status_function.setReturnTypeObject();

  // Callbacks
  modular_server::Callback & deliver_callback = modular_server_.createCallback(constants::deliver_callback_name);
  deliver_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&PelletDispenser::deliverHandler));
  deliver_callback.attachTo(modular_device_base::constants::bnc_a_interrupt_name,modular_server::interrupt::mode_falling);

  modular_server::Callback & abort_callback = modular_server_.createCallback(constants::abort_callback_name);
  abort_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&PelletDispenser::abortHandler));
  abort_callback.attachTo(modular_device_base::constants::bnc_b_interrupt_name,modular_server::interrupt::mode_falling);

  // Clients
  // audio_controller_.setStream(Serial1);
}

void PelletDispenser::update()
{
  // Parent Update
  StageController::update();

  const ConstantString * state_ptr = assay_status_.state_ptr;

  if (state_ptr == &constants::state_assay_started_string)
  {
    if (stageHomed())
    {
      assay_status_.state_ptr = &constants::state_move_to_base_start_string;
    }
    else
    {
      assay_status_.state_ptr = &constants::state_homing_string;
      homeStage();
    }
  }
  else if (state_ptr == &constants::state_homing_string)
  {
    if (stageHomed())
    {
      assay_status_.state_ptr = &constants::state_move_to_base_start_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_base_start_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_base_start_string;
    moveStageSoftlyToBase();
  }
  else if (state_ptr == &constants::state_moving_to_base_start_string)
  {
    if (stageAtTargetPositions())
    {
      assay_status_.state_ptr = &constants::state_move_to_deliver_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_deliver_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_deliver_string;
    moveStageSoftlyToDeliver();
  }
  else if (state_ptr == &constants::state_moving_to_deliver_string)
  {
    if (stageAtTargetPositions())
    {
      assay_status_.state_ptr = &constants::state_wait_to_play_tone_string;
    }
  }
  else if (state_ptr == &constants::state_wait_to_play_tone_string)
  {
    assay_status_.state_ptr = &constants::state_waiting_to_play_tone_string;
    waitToPlayTone();
  }
  else if (state_ptr == &constants::state_waiting_to_play_tone_string)
  {
  }
  else if (state_ptr == &constants::state_play_tone_string)
  {
    assay_status_.state_ptr = &constants::state_playing_tone_string;
    playTone();
  }
  else if (state_ptr == &constants::state_move_to_dispense_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_dispense_string;
    moveStageSoftlyToDispense();
  }
  else if (state_ptr == &constants::state_moving_to_dispense_string)
  {
    if (stageAtTargetPositions())
    {
      assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_base_stop_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_base_stop_string;
    moveStageSoftlyToBase();
  }
  else if (state_ptr == &constants::state_moving_to_base_stop_string)
  {
    if (stageAtTargetPositions())
    {
      assay_status_.state_ptr = &constants::state_assay_finished_string;
    }
  }
}

constants::AssayStatus PelletDispenser::getAssayStatus()
{
  return assay_status_;
}

StageController::PositionsArray PelletDispenser::getBasePositions()
{
  double base_positions[constants::STAGE_CHANNEL_COUNT];
  modular_server_.property(constants::base_positions_property_name).getValue(base_positions);

  StageController::PositionsArray base_positions_array(base_positions);
  return base_positions_array;
}

StageController::PositionsArray PelletDispenser::getDeliverPositions()
{
  double deliver_positions[constants::STAGE_CHANNEL_COUNT];
  modular_server_.property(constants::deliver_positions_property_name).getValue(deliver_positions);

  StageController::PositionsArray deliver_positions_array(deliver_positions);
  return deliver_positions_array;
}

StageController::PositionsArray PelletDispenser::getDispensePositions()
{
  double dispense_positions[constants::STAGE_CHANNEL_COUNT];
  modular_server_.property(constants::dispense_positions_property_name).getValue(dispense_positions);

  StageController::PositionsArray dispense_positions_array(dispense_positions);
  return dispense_positions_array;
}

long PelletDispenser::getToneDelay()
{
  long tone_delay_min;
  modular_server_.property(constants::tone_delay_min_property_name).getValue(tone_delay_min);

  long tone_delay_max;
  modular_server_.property(constants::tone_delay_max_property_name).getValue(tone_delay_max);

  long tone_delay = random(tone_delay_min,tone_delay_max);
  tone_delay = tone_delay*constants::milliseconds_per_second;
  return tone_delay;
}

void PelletDispenser::moveStageSoftlyToBase()
{
  StageController::PositionsArray base_positions = getBasePositions();
  moveStageSoftlyTo(base_positions);
}

void PelletDispenser::moveStageSoftlyToDeliver()
{
  StageController::PositionsArray deliver_positions = getDeliverPositions();
  moveStageSoftlyTo(deliver_positions);
}

void PelletDispenser::moveStageSoftlyToDispense()
{
  StageController::PositionsArray dispense_positions = getDispensePositions();
  moveStageSoftlyTo(dispense_positions);
}

void PelletDispenser::waitToPlayTone()
{
  long tone_delay = getToneDelay();
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::playToneHandler),
                                                          tone_delay);
  event_controller_.enable(event_id);
}

void PelletDispenser::setPlayToneState()
{
  assay_status_.state_ptr = &constants::state_play_tone_string;
}

void PelletDispenser::playTone()
{
}

void PelletDispenser::deliver()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    assay_status_.state_ptr = &constants::state_assay_started_string;
  }
}

void PelletDispenser::abort()
{
  Serial << "abort!\n";
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void PelletDispenser::getAssayStatusHandler()
{
  constants::AssayStatus assay_status = getAssayStatus();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::state_string,assay_status.state_ptr);

  modular_server_.response().endObject();

}

void PelletDispenser::playToneHandler(int arg)
{
  setPlayToneState();
}

void PelletDispenser::deliverHandler(modular_server::Interrupt * interrupt_ptr)
{
  deliver();
}

void PelletDispenser::abortHandler(modular_server::Interrupt * interrupt_ptr)
{
  abort();
}

