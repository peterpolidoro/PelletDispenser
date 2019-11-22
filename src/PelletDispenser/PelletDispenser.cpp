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
  audio_controller_ptr_ = &(createClientAtAddress(audio_controller::constants::device_name,constants::audio_controller_address));
  power_switch_controller_ptr_ = &(createClientAtAddress(power_switch_controller::constants::device_name,constants::power_switch_controller_address));

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

  modular_server::Property & invert_driver_direction_property = modular_server_.property(stepper_controller::constants::invert_driver_direction_property_name);
  invert_driver_direction_property.setDefaultValue(constants::invert_driver_direction_default);

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

  modular_server_.createProperty(constants::next_deliver_position_property_name,constants::next_deliver_position_default);

  modular_server_.createProperty(constants::dispense_channel_position_property_name,constants::dispense_channel_position_default);

  modular_server::Property & position_property = modular_server_.createProperty(constants::position_property_name,constants::position_ptr_default);
  position_property.setSubset(constants::position_subset);

  modular_server::Property & position_tone_frequency_property = modular_server_.createProperty(constants::position_tone_frequency_property_name,constants::position_tone_frequency_default);
  position_tone_frequency_property.setUnits(audio_controller::constants::hz_units);
  position_tone_frequency_property.setRange(constants::tone_frequency_min,constants::tone_frequency_max);

  modular_server::Property & position_tone_volume_property = modular_server_.createProperty(constants::position_tone_volume_property_name,constants::position_tone_volume_default);
  position_tone_volume_property.setRange(audio_controller::constants::volume_min,audio_controller::constants::volume_max);

  modular_server::Property & position_tone_delay_property = modular_server_.createProperty(constants::position_tone_delay_property_name,constants::position_tone_delay_default);
  position_tone_delay_property.setUnits(constants::seconds_units);
  position_tone_delay_property.setRange(constants::position_tone_delay_min,constants::position_tone_delay_max);

  modular_server::Property & position_tone_duration_property = modular_server_.createProperty(constants::position_tone_duration_property_name,constants::position_tone_duration_default);
  position_tone_duration_property.setUnits(constants::seconds_units);
  position_tone_duration_property.setRange(constants::position_tone_duration_min,constants::position_tone_duration_max);

  modular_server::Property & dispense_delay_property = modular_server_.createProperty(constants::dispense_delay_property_name,constants::dispense_delay_default);
  dispense_delay_property.setUnits(constants::seconds_units);
  dispense_delay_property.setRange(constants::dispense_delay_min,constants::dispense_delay_max);

  modular_server::Property & return_delay_min_property = modular_server_.createProperty(constants::return_delay_min_property_name,constants::return_delay_min_default);
  return_delay_min_property.setUnits(constants::seconds_units);
  return_delay_min_property.setRange(constants::return_delay_min,constants::return_delay_max);

  modular_server::Property & return_delay_max_property = modular_server_.createProperty(constants::return_delay_max_property_name,constants::return_delay_max_default);
  return_delay_max_property.setUnits(constants::seconds_units);
  return_delay_max_property.setRange(constants::return_delay_min,constants::return_delay_max);

  modular_server::Property & buzz_power_property = modular_server_.createProperty(constants::buzz_power_property_name,constants::buzz_power_default);
  buzz_power_property.setUnits(constants::percent_units);
  buzz_power_property.setRange(constants::buzz_power_min,constants::buzz_power_max);

  modular_server::Property & buzz_period_property = modular_server_.createProperty(constants::buzz_period_property_name,constants::buzz_period_default);
  buzz_period_property.setUnits(constants::ms_units);
  buzz_period_property.setRange(constants::buzz_period_min,constants::buzz_period_max);

  modular_server::Property & buzz_on_duration_property = modular_server_.createProperty(constants::buzz_on_duration_property_name,constants::buzz_on_duration_default);
  buzz_on_duration_property.setUnits(constants::ms_units);
  buzz_on_duration_property.setRange(constants::buzz_on_duration_min,constants::buzz_on_duration_max);

  modular_server::Property & buzz_count_property = modular_server_.createProperty(constants::buzz_count_property_name,constants::buzz_count_default);
  buzz_count_property.setRange(constants::buzz_count_min,constants::buzz_count_max);

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

  modular_server::Function & play_position_tone_function = modular_server_.createFunction(constants::play_position_tone_function_name);
  play_position_tone_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::playPositionToneHandler));

  modular_server::Function & buzz_function = modular_server_.createFunction(constants::buzz_function_name);
  buzz_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::buzzHandler));

  // Callbacks
  modular_server::Callback & start_assay_callback = modular_server_.createCallback(constants::start_assay_callback_name);
  start_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PelletDispenser::startAssayHandler));
  start_assay_callback.attachTo(modular_device_base::constants::bnc_a_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#if !defined(__AVR_ATmega2560__)
  start_assay_callback.attachTo(modular_device_base::constants::btn_a_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#endif

  modular_server::Callback & dispense_callback = modular_server_.createCallback(constants::dispense_callback_name);
  dispense_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PelletDispenser::dispenseHandler));
  dispense_callback.attachTo(modular_device_base::constants::bnc_b_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#if defined(__MK64FX512__)
  dispense_callback.attachTo(modular_device_base::constants::btn_b_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#endif

  modular_server::Callback & abort_callback = modular_server_.createCallback(constants::abort_callback_name);
  abort_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&PelletDispenser::abortHandler));

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
      assay_status_.state_ptr = &constants::state_move_to_next_deliver_string;
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
      assay_status_.state_ptr = &constants::state_move_to_next_deliver_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_next_deliver_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_next_deliver_string;
    moveStageToNextDeliverPosition();
  }
  else if (state_ptr == &constants::state_moving_to_next_deliver_string)
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
  else if (state_ptr == &constants::state_ready_to_dispense_string)
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
  else if (state_ptr == &constants::state_assay_finished_string)
  {
  }
}

constants::AssayStatus PelletDispenser::getAssayStatus()
{
  return assay_status_;
}

StageController::PositionArray PelletDispenser::getNextDeliverPosition()
{
  StageController::PositionArray next_deliver_position;
  modular_server_.property(constants::next_deliver_position_property_name).getValue(next_deliver_position);

  return next_deliver_position;
}

StageController::PositionArray PelletDispenser::getDispensePosition()
{
  StageController::PositionArray dispense_position = deliver_position_;

  long dispense_channel_position;
  modular_server_.property(constants::dispense_channel_position_property_name).getValue(dispense_channel_position);

  dispense_position[constants::DISPENSE_CHANNEL] = dispense_channel_position;

  return dispense_position;
}

long PelletDispenser::getPositionToneFrequency()
{
  long position_tone_frequency;
  modular_server_.property(constants::position_tone_frequency_property_name).getValue(position_tone_frequency);

  return position_tone_frequency;
}

long PelletDispenser::getPositionToneVolume()
{
  long position_tone_volume;
  modular_server_.property(constants::position_tone_volume_property_name).getValue(position_tone_volume);

  return position_tone_volume;
}

long PelletDispenser::getPositionToneDelay()
{
  double position_tone_delay;
  modular_server_.property(constants::position_tone_delay_property_name).getValue(position_tone_delay);

  return position_tone_delay * constants::milliseconds_per_second;
}

long PelletDispenser::getPositionToneDuration()
{
  double position_tone_duration;
  modular_server_.property(constants::position_tone_duration_property_name).getValue(position_tone_duration);

  return position_tone_duration * constants::milliseconds_per_second;
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

  long return_delay_min_ms = return_delay_min * constants::milliseconds_per_second;
  long return_delay_max_ms = return_delay_max * constants::milliseconds_per_second;
  long return_delay_ms = random(return_delay_min_ms,return_delay_max_ms);
  return return_delay_ms;
}

long PelletDispenser::getBuzzPower()
{
  long buzz_power;
  modular_server_.property(constants::buzz_power_property_name).getValue(buzz_power);

  return buzz_power;
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

void PelletDispenser::moveStageToNextDeliverPosition()
{
  StageController::PositionArray next_deliver_position = getNextDeliverPosition();
  deliver_position_ = next_deliver_position;
  moveStageTo(next_deliver_position);
}

void PelletDispenser::moveStageToDispensePosition()
{
  StageController::PositionArray dispense_position = getDispensePosition();
  moveStageTo(dispense_position);
}

void PelletDispenser::playPositionTone()
{
  const ConstantString * position_ptr;
  modular_server_.property(constants::position_property_name).getValue(position_ptr);
  if (position_ptr == &constants::position_right)
  {
    audio_controller_ptr_->call(audio_controller::constants::playing_signal_property_name,
      constants::set_value_string,
      audio_controller::constants::playing_signal_bnc_b);
  }
  else
  {
    audio_controller_ptr_->call(audio_controller::constants::playing_signal_property_name,
      constants::set_value_string,
      audio_controller::constants::playing_signal_bnc_a);
  }

  long position_tone_frequency = getPositionToneFrequency();
  long position_tone_volume = getPositionToneVolume();
  long position_tone_delay = getPositionToneDelay();
  long position_tone_duration = getPositionToneDuration();

  audio_controller_ptr_->call(audio_controller::constants::add_tone_pwm_at_function_name,
    position_tone_frequency,
    audio_controller::constants::speaker_all,
    position_tone_volume,
    position_tone_delay,
    position_tone_duration,
    position_tone_duration,
    1);
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
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::moveToNextDeliverHandler),
    return_delay);
  event_controller_.enable(event_id);
}

void PelletDispenser::setMoveToNextDeliverState()
{
  assay_status_.state_ptr = &constants::state_move_to_next_deliver_string;
}

void PelletDispenser::buzz()
{
  long buzz_power = getBuzzPower();
  long buzz_period = getBuzzPeriod();
  long buzz_on_duration = getBuzzOnDuration();
  long buzz_count = getBuzzCount();

  power_switch_controller_ptr_->call(power_switch_controller::constants::set_power_function_name,
    constants::buzz_channel_group,
    buzz_power);

  Array<size_t,constants::BUZZ_CHANNEL_COUNT> buzz_channels_array(constants::buzz_channels);

  power_switch_controller_ptr_->call(power_switch_controller::constants::add_pwm_function_name,
    buzz_channels_array,
    buzz_on_duration,
    buzz_period,
    buzz_on_duration,
    buzz_count);
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::setReadyToDispenseHandler),
    buzz_period*buzz_count);
  event_controller_.enable(event_id);
}

void PelletDispenser::setReadyToDispenseState()
{
  assay_status_.state_ptr = &constants::state_ready_to_dispense_string;
}

void PelletDispenser::startAssay()
{
  stopAll();
  event_controller_.removeAllEvents();
  audio_controller_ptr_->call(audio_controller::constants::stop_all_pwm_function_name);

  assay_status_.state_ptr = &constants::state_assay_started_string;
}

void PelletDispenser::dispense()
{
  if (assay_status_.state_ptr == &constants::state_ready_to_dispense_string)
  {
    playPositionTone();
    setWaitToDispenseState();
  }
}

void PelletDispenser::abort()
{
  stopAll();
  event_controller_.removeAllEvents();
  audio_controller_ptr_->call(audio_controller::constants::stop_all_pwm_function_name);

  if (stageHomed())
  {
    setMoveToNextDeliverState();
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

void PelletDispenser::playPositionToneHandler()
{
  playPositionTone();
}

void PelletDispenser::buzzHandler()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    buzz();
  }
}

void PelletDispenser::waitToDispenseHandler(int arg)
{
  setWaitToDispenseState();
}

void PelletDispenser::moveToDispenseHandler(int arg)
{
  setMoveToDispenseState();
}

void PelletDispenser::moveToNextDeliverHandler(int arg)
{
  setMoveToNextDeliverState();
}

void PelletDispenser::setReadyToDispenseHandler(int arg)
{
  if (assay_status_.state_ptr == &constants::state_buzzing_string)
  {
    setReadyToDispenseState();
  }
}

void PelletDispenser::startAssayHandler(modular_server::Pin * pin_ptr)
{
  startAssay();
}

void PelletDispenser::dispenseHandler(modular_server::Pin * pin_ptr)
{
  dispense();
}

void PelletDispenser::abortHandler(modular_server::Pin * pin_ptr)
{
  abort();
}
