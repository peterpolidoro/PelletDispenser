// ----------------------------------------------------------------------------
// PelletDispenser.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../PelletDispenser.h"


using namespace pellet_dispenser;

PelletDispenser::PelletDispenser()
{
}

void PelletDispenser::setup()
{
  // Parent Setup
  StageController::setup();

  // Reset Watchdog
  resetWatchdog();

  // Event Controller Setup
  event_controller_.setup();

  // Clients Setup
  optical_switch_interface_ptr_ = &(createClientAtAddress(optical_switch_interface::constants::device_name,constants::optical_switch_interface_address));
  h_bridge_controller_ptr_ = &(createClientAtAddress(h_bridge_controller::constants::device_name,constants::h_bridge_controller_address));
  audio_controller_ptr_ = &(createClientAtAddress(audio_controller::constants::device_name,constants::audio_controller_address));

  // Pin Setup

  // Assay Status Setup
  assay_status_.state_ptr = &constants::state_assay_not_started_string;

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & steps_per_position_units_property = modular_server_.property(step_dir_controller::constants::steps_per_position_units_property_name);
  steps_per_position_units_property.setDefaultValue(constants::steps_per_position_units_default);

  modular_server::Property & velocity_max_property = modular_server_.property(step_dir_controller::constants::velocity_max_property_name);
  velocity_max_property.setDefaultValue(constants::velocity_max_default);

  modular_server::Property & velocity_min_property = modular_server_.property(step_dir_controller::constants::velocity_min_property_name);
  velocity_min_property.setDefaultValue(constants::velocity_min_default);

  modular_server::Property & acceleration_max_property = modular_server_.property(step_dir_controller::constants::acceleration_max_property_name);
  acceleration_max_property.setDefaultValue(constants::acceleration_max_default);

  modular_server::Property & home_velocity_property = modular_server_.property(step_dir_controller::constants::home_velocity_property_name);
  home_velocity_property.setDefaultValue(constants::home_velocity_default);

  modular_server::Property & run_current_property = modular_server_.property(stepper_controller::constants::run_current_property_name);
  run_current_property.setDefaultValue(constants::run_current_default);

  modular_server::Property & hold_current_property = modular_server_.property(stepper_controller::constants::hold_current_property_name);
  hold_current_property.setDefaultValue(constants::hold_current_default);

  modular_server::Property & hold_delay_property = modular_server_.property(stepper_controller::constants::hold_delay_property_name);
  hold_delay_property.setDefaultValue(constants::hold_delay_default);

  modular_server::Property & stage_position_min_property = modular_server_.property(stage_controller::constants::stage_position_min_property_name);
  stage_position_min_property.setDefaultValue(constants::stage_position_min_default);

  modular_server::Property & stage_position_max_property = modular_server_.property(stage_controller::constants::stage_position_max_property_name);
  stage_position_max_property.setDefaultValue(constants::stage_position_max_default);

  modular_server_.createProperty(constants::base_position_property_name,constants::base_position_default);

  modular_server_.createProperty(constants::deliver_position_property_name,constants::deliver_position_default);

  modular_server_.createProperty(constants::dispense_channel_position_property_name,constants::dispense_channel_position_default);

  modular_server_.createProperty(constants::clean_position_property_name,constants::clean_position_default);

  modular_server::Property & clean_duration_property = modular_server_.createProperty(constants::clean_duration_property_name,constants::clean_duration_default);
  clean_duration_property.setUnits(constants::seconds_units);
  clean_duration_property.setRange(constants::clean_duration_min,constants::clean_duration_max);

  modular_server::Property & buzz_period_property = modular_server_.createProperty(constants::buzz_period_property_name,constants::buzz_period_default);
  buzz_period_property.setUnits(constants::ms_units);
  buzz_period_property.setRange(constants::buzz_period_min,constants::buzz_period_max);

  modular_server::Property & buzz_on_duration_property = modular_server_.createProperty(constants::buzz_on_duration_property_name,constants::buzz_on_duration_default);
  buzz_on_duration_property.setUnits(constants::ms_units);
  buzz_on_duration_property.setRange(constants::buzz_on_duration_min,constants::buzz_on_duration_max);

  modular_server::Property & buzz_count_property = modular_server_.createProperty(constants::buzz_count_property_name,constants::buzz_count_default);
  buzz_count_property.setRange(constants::buzz_count_min,constants::buzz_count_max);

  modular_server::Property & tone_frequency_property = modular_server_.createProperty(constants::tone_frequency_property_name,constants::tone_frequency_default);
  tone_frequency_property.setUnits(audio_controller::constants::hz_units);
  tone_frequency_property.setRange(constants::tone_frequency_min,constants::tone_frequency_max);

  modular_server::Property & tone_duration_property = modular_server_.createProperty(constants::tone_duration_property_name,constants::tone_duration_default);
  tone_duration_property.setUnits(constants::seconds_units);
  tone_duration_property.setRange(constants::tone_duration_min,constants::tone_duration_max);

  modular_server::Property & tone_volume_property = modular_server_.createProperty(constants::tone_volume_property_name,constants::tone_volume_default);
  tone_volume_property.setRange(audio_controller::constants::volume_min,audio_controller::constants::volume_max);

  modular_server::Property & tone_delay_min_property = modular_server_.createProperty(constants::tone_delay_min_property_name,constants::tone_delay_min_default);
  tone_delay_min_property.setUnits(constants::seconds_units);
  tone_delay_min_property.setRange(constants::tone_delay_min,constants::tone_delay_max);

  modular_server::Property & tone_delay_max_property = modular_server_.createProperty(constants::tone_delay_max_property_name,constants::tone_delay_max_default);
  tone_delay_max_property.setUnits(constants::seconds_units);
  tone_delay_max_property.setRange(constants::tone_delay_min,constants::tone_delay_max);

  modular_server::Property & dispense_delay_property = modular_server_.createProperty(constants::dispense_delay_property_name,constants::dispense_delay_default);
  dispense_delay_property.setUnits(constants::seconds_units);
  dispense_delay_property.setRange(constants::dispense_delay_min,constants::dispense_delay_max);

  modular_server::Property & return_delay_min_property = modular_server_.createProperty(constants::return_delay_min_property_name,constants::return_delay_min_default);
  return_delay_min_property.setUnits(constants::minutes_units);
  return_delay_min_property.setRange(constants::return_delay_min,constants::return_delay_max);

  modular_server::Property & return_delay_max_property = modular_server_.createProperty(constants::return_delay_max_property_name,constants::return_delay_max_default);
  return_delay_max_property.setUnits(constants::minutes_units);
  return_delay_max_property.setRange(constants::return_delay_min,constants::return_delay_max);

  // Parameters
  modular_server::Parameter & stage_position_parameter = modular_server_.parameter(stage_controller::constants::stage_position_parameter_name);
  stage_position_parameter.setUnits(constants::mm_units);

  // Functions
  modular_server::Function & set_client_property_values_function = modular_server_.createFunction(constants::set_client_property_values_function_name);
  set_client_property_values_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::setClientPropertyValuesHandler));
  set_client_property_values_function.setResultTypeObject();

  modular_server::Function & get_assay_status_function = modular_server_.createFunction(constants::get_assay_status_function_name);
  get_assay_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::getAssayStatusHandler));
  get_assay_status_function.setResultTypeObject();

  modular_server::Function & move_stage_to_base_position_function = modular_server_.createFunction(constants::move_stage_to_base_position_function_name);
  move_stage_to_base_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::moveStageToBasePositionHandler));

  modular_server::Function & move_stage_to_deliver_position_function = modular_server_.createFunction(constants::move_stage_to_deliver_position_function_name);
  move_stage_to_deliver_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::moveStageToDeliverPositionHandler));

  modular_server::Function & move_stage_to_dispense_position_function = modular_server_.createFunction(constants::move_stage_to_dispense_position_function_name);
  move_stage_to_dispense_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::moveStageToDispensePositionHandler));

  modular_server::Function & move_stage_to_clean_position_function = modular_server_.createFunction(constants::move_stage_to_clean_position_function_name);
  move_stage_to_clean_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::moveStageToCleanPositionHandler));

  // Callbacks
  modular_server::Callback & deliver_callback = modular_server_.createCallback(constants::deliver_callback_name);
  deliver_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PelletDispenser::deliverHandler));
  deliver_callback.attachTo(modular_device_base::constants::bnc_b_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#if defined(__MK64FX512__)
  deliver_callback.attachTo(modular_device_base::constants::btn_b_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#endif

  modular_server::Callback & abort_callback = modular_server_.createCallback(constants::abort_callback_name);
  abort_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PelletDispenser::abortHandler));
  abort_callback.attachTo(modular_device_base::constants::bnc_a_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#if !defined(__AVR_ATmega2560__)
  abort_callback.attachTo(modular_device_base::constants::btn_a_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#endif

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
    moveStageToBasePosition();
  }
  else if (state_ptr == &constants::state_moving_to_base_start_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_move_to_deliver_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_deliver_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_deliver_string;
    moveStageToDeliverPosition();
  }
  else if (state_ptr == &constants::state_moving_to_deliver_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_buzz_string;
    }
  }
  else if (state_ptr == &constants::state_buzz_string)
  {
    assay_status_.state_ptr = &constants::state_buzzing_string;
    buzz();
  }
  else if (state_ptr == &constants::state_buzzing_string)
  {
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
  else if (state_ptr == &constants::state_playing_tone_string)
  {
  }
  else if (state_ptr == &constants::state_wait_to_dispense_string)
  {
    assay_status_.state_ptr = &constants::state_waiting_to_dispense_string;
    waitToDispense();
  }
  else if (state_ptr == &constants::state_waiting_to_dispense_string)
  {
  }
  else if (state_ptr == &constants::state_move_to_dispense_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_dispense_string;
    moveStageToDispensePosition();
  }
  else if (state_ptr == &constants::state_moving_to_dispense_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_wait_to_return_string;
    }
  }
  else if (state_ptr == &constants::state_wait_to_return_string)
  {
    assay_status_.state_ptr = &constants::state_waiting_to_return_string;
    waitToReturn();
  }
  else if (state_ptr == &constants::state_waiting_to_return_string)
  {
  }
  else if (state_ptr == &constants::state_move_to_clean_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_clean_string;
    moveStageToCleanPosition();
  }
  else if (state_ptr == &constants::state_moving_to_clean_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_wait_at_clean_string;
    }
  }
  else if (state_ptr == &constants::state_wait_at_clean_string)
  {
    assay_status_.state_ptr = &constants::state_waiting_at_clean_string;
    waitAtClean();
  }
  else if (state_ptr == &constants::state_waiting_at_clean_string)
  {
  }
  else if (state_ptr == &constants::state_move_to_base_stop_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_base_stop_string;
    moveStageToBasePosition();
  }
  else if (state_ptr == &constants::state_moving_to_base_stop_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_assay_finished_string;
    }
  }
}

constants::AssayStatus PelletDispenser::getAssayStatus()
{
  return assay_status_;
}

StageController::PositionArray PelletDispenser::getBasePosition()
{
  StageController::PositionArray base_position_array;
  modular_server_.property(constants::base_position_property_name).getValue(base_position_array);

  return base_position_array;
}

StageController::PositionArray PelletDispenser::getDeliverPosition()
{
  StageController::PositionArray deliver_position_array;
  modular_server_.property(constants::deliver_position_property_name).getValue(deliver_position_array);

  return deliver_position_array;
}

StageController::PositionArray PelletDispenser::getDispensePosition()
{
  StageController::PositionArray dispense_position_array;
  modular_server_.property(constants::deliver_position_property_name).getValue(dispense_position_array);

  long dispense_channel_position;
  modular_server_.property(constants::dispense_channel_position_property_name).getValue(dispense_channel_position);
  dispense_position_array[constants::DISPENSE_CHANNEL] = dispense_channel_position;

  return dispense_position_array;
}

StageController::PositionArray PelletDispenser::getCleanPosition()
{
  StageController::PositionArray clean_position_array;
  modular_server_.property(constants::clean_position_property_name).getValue(clean_position_array);

  return clean_position_array;
}

long PelletDispenser::getBuzzPeriod()
{
  long buzz_period;
  modular_server_.property(constants::buzz_period_property_name).getValue(buzz_period);

  return buzz_period;
}

long PelletDispenser::getBuzzOnDuration()
{
  long buzz_on_duration;
  modular_server_.property(constants::buzz_on_duration_property_name).getValue(buzz_on_duration);

  return buzz_on_duration;
}

long PelletDispenser::getBuzzCount()
{
  long buzz_count;
  modular_server_.property(constants::buzz_count_property_name).getValue(buzz_count);

  return buzz_count;
}

long PelletDispenser::getToneDelay()
{
  long tone_delay_min;
  modular_server_.property(constants::tone_delay_min_property_name).getValue(tone_delay_min);

  long tone_delay_max;
  modular_server_.property(constants::tone_delay_max_property_name).getValue(tone_delay_max);

  long tone_delay = random(tone_delay_min,tone_delay_max);
  tone_delay = tone_delay * constants::milliseconds_per_second;
  return tone_delay;
}

long PelletDispenser::getToneFrequency()
{
  long tone_frequency;
  modular_server_.property(constants::tone_frequency_property_name).getValue(tone_frequency);

  return tone_frequency;
}

long PelletDispenser::getToneDuration()
{
  double tone_duration;
  modular_server_.property(constants::tone_duration_property_name).getValue(tone_duration);

  return tone_duration * constants::milliseconds_per_second;
}

long PelletDispenser::getToneVolume()
{
  long tone_volume;
  modular_server_.property(constants::tone_volume_property_name).getValue(tone_volume);

  return tone_volume;
}

long PelletDispenser::getDispenseDelay()
{
  double dispense_delay;
  modular_server_.property(constants::dispense_delay_property_name).getValue(dispense_delay);

  long dispense_delay_ms = dispense_delay * constants::milliseconds_per_second;
  return dispense_delay_ms;
}

long PelletDispenser::getReturnDelay()
{
  double return_delay_min;
  modular_server_.property(constants::return_delay_min_property_name).getValue(return_delay_min);

  double return_delay_max;
  modular_server_.property(constants::return_delay_max_property_name).getValue(return_delay_max);

  long return_delay_min_ms = return_delay_min * constants::milliseconds_per_minute;
  long return_delay_max_ms = return_delay_max * constants::milliseconds_per_minute;
  long return_delay_ms = random(return_delay_min_ms,return_delay_max_ms);
  return return_delay_ms;
}

long PelletDispenser::getCleanDuration()
{
  long clean_duration;
  modular_server_.property(constants::clean_duration_property_name).getValue(clean_duration);

  return clean_duration * constants::milliseconds_per_second;
}

void PelletDispenser::moveStageToBasePosition()
{
  StageController::PositionArray base_position = getBasePosition();
  moveStageSoftlyTo(base_position);
}

void PelletDispenser::moveStageToDeliverPosition()
{
  StageController::PositionArray deliver_position = getDeliverPosition();
  moveStageSoftlyTo(deliver_position);
}

void PelletDispenser::moveStageToDispensePosition()
{
  StageController::PositionArray dispense_position = getDispensePosition();
  moveStageTo(dispense_position);
}

void PelletDispenser::moveStageToCleanPosition()
{
  StageController::PositionArray clean_position = getCleanPosition();
  moveStageSoftlyTo(clean_position);
}

void PelletDispenser::buzz()
{
  long buzz_period = getBuzzPeriod();
  long buzz_on_duration = getBuzzOnDuration();
  long buzz_count = getBuzzCount();

  Array<size_t,constants::BUZZ_CHANNEL_COUNT> buzz_channels_array(constants::buzz_channels);

  h_bridge_controller_ptr_->call(h_bridge_controller::constants::add_pwm_function_name,
    buzz_channels_array,
    h_bridge_controller::constants::polarity_positive,
    0,
    buzz_period,
    buzz_on_duration,
    buzz_count);
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::waitToPlayToneHandler),
    buzz_period*buzz_count);
  event_controller_.enable(event_id);
}

void PelletDispenser::setWaitToPlayToneState()
{
  assay_status_.state_ptr = &constants::state_wait_to_play_tone_string;
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
  long tone_frequency = getToneFrequency();
  long tone_duration = getToneDuration();
  long tone_volume = getToneVolume();

  audio_controller_ptr_->call(audio_controller::constants::add_tone_pwm_at_function_name,
    tone_frequency,
    audio_controller::constants::speaker_all,
    tone_volume,
    0,
    tone_duration,
    tone_duration,
    1);
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::waitToDispenseHandler),
    tone_duration);
  event_controller_.enable(event_id);
}

void PelletDispenser::setWaitToDispenseState()
{
  assay_status_.state_ptr = &constants::state_wait_to_dispense_string;
}

void PelletDispenser::waitToDispense()
{
  long dispense_delay = getDispenseDelay();
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::moveToDispenseHandler),
    dispense_delay);
  event_controller_.enable(event_id);
}

void PelletDispenser::setMoveToDispenseState()
{
  assay_status_.state_ptr = &constants::state_move_to_dispense_string;
}

void PelletDispenser::waitToReturn()
{
  long return_delay = getReturnDelay();
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::moveToCleanHandler),
    return_delay);
  event_controller_.enable(event_id);
}

void PelletDispenser::setMoveToCleanState()
{
  assay_status_.state_ptr = &constants::state_move_to_clean_string;
}

void PelletDispenser::waitAtClean()
{
  long clean_duration = getCleanDuration();
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::moveToBaseStopHandler),
    clean_duration);
  event_controller_.enable(event_id);
}

void PelletDispenser::setMoveToBaseStopState()
{
  assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
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
  stopAll();
  event_controller_.removeAllEvents();
  h_bridge_controller_ptr_->call(h_bridge_controller::constants::stop_all_pwm_function_name);
  audio_controller_ptr_->call(audio_controller::constants::stop_all_pwm_function_name);

  if (stageHomed())
  {
    setMoveToCleanState();
  }
  else
  {
    assay_status_.state_ptr = &constants::state_assay_not_started_string;
  }
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
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void PelletDispenser::setClientPropertyValuesHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  bool call_was_successful;

  modular_server_.response().writeKey(h_bridge_controller::constants::device_name);
  modular_server_.response().beginArray();
  h_bridge_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  call_was_successful = h_bridge_controller_ptr_->callWasSuccessful();
  modular_server_.response().write(call_was_successful);
  modular_server_.response().endArray();

  modular_server_.response().writeKey(optical_switch_interface::constants::device_name);
  modular_server_.response().beginArray();
  optical_switch_interface_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  call_was_successful = optical_switch_interface_ptr_->callWasSuccessful();
  modular_server_.response().write(call_was_successful);
  Array<bool,optical_switch_interface::constants::OUTPUT_COUNT> inverted(constants::inverted);
  optical_switch_interface_ptr_->call(optical_switch_interface::constants::inverted_property_name,
    modular_server::property::set_value_function_name,
    inverted);
  call_was_successful = optical_switch_interface_ptr_->callWasSuccessful();
  modular_server_.response().write(call_was_successful);
  modular_server_.response().endArray();

  modular_server_.response().writeKey(audio_controller::constants::device_name);
  modular_server_.response().beginArray();
  audio_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  call_was_successful = audio_controller_ptr_->callWasSuccessful();
  modular_server_.response().write(call_was_successful);
  modular_server_.response().endArray();

  modular_server_.response().endObject();
}

void PelletDispenser::getAssayStatusHandler()
{
  constants::AssayStatus assay_status = getAssayStatus();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::state_string,assay_status.state_ptr);

  modular_server_.response().endObject();

}

void PelletDispenser::moveStageToBasePositionHandler()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveStageToBasePosition();
  }
}

void PelletDispenser::moveStageToDeliverPositionHandler()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveStageToDeliverPosition();
  }
}

void PelletDispenser::moveStageToDispensePositionHandler()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveStageToDispensePosition();
  }
}

void PelletDispenser::moveStageToCleanPositionHandler()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveStageToCleanPosition();
  }
}

void PelletDispenser::playToneHandler(int arg)
{
  setPlayToneState();
}

void PelletDispenser::waitToDispenseHandler(int arg)
{
  setWaitToDispenseState();
}

void PelletDispenser::moveToDispenseHandler(int arg)
{
  setMoveToDispenseState();
}

void PelletDispenser::waitToPlayToneHandler(int arg)
{
  setWaitToPlayToneState();
}

void PelletDispenser::moveToCleanHandler(int arg)
{
  setMoveToCleanState();
}

void PelletDispenser::moveToBaseStopHandler(int arg)
{
  setMoveToBaseStopState();
}

void PelletDispenser::deliverHandler(modular_server::Pin * pin_ptr)
{
  deliver();
}

void PelletDispenser::abortHandler(modular_server::Pin * pin_ptr)
{
  abort();
}
