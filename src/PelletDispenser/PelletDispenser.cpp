// ----------------------------------------------------------------------------
// PelletDispenser.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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

  modular_server::Property & right_switches_enabled_property = modular_server_.property(step_dir_controller::constants::right_switches_enabled_property_name);
  right_switches_enabled_property.setDefaultValue(constants::right_switches_enabled_default);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setDefaultValue(constants::right_switch_stop_enabled_default);

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

  modular_server_.createProperty(constants::buzz_position_property_name,constants::buzz_position_default);

  modular_server_.createProperty(constants::load_position_property_name,constants::load_position_default);

  modular_server_.createProperty(constants::next_deliver_position_property_name,constants::next_deliver_position_default);

  modular_server_.createProperty(constants::next_dispense_position_property_name,constants::next_dispense_position_default);

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

  modular_server::Property & wait_at_load_duration_property = modular_server_.createProperty(constants::wait_at_load_duration_property_name,constants::wait_at_load_duration_default);
  wait_at_load_duration_property.setUnits(constants::ms_units);
  wait_at_load_duration_property.setRange(constants::wait_at_load_duration_min,constants::wait_at_load_duration_max);

  modular_server::Property & tap_period_property = modular_server_.createProperty(constants::tap_period_property_name,constants::tap_period_default);
  tap_period_property.setUnits(constants::ms_units);
  tap_period_property.setRange(constants::tap_period_min,constants::tap_period_max);

  modular_server::Property & tap_on_duration_property = modular_server_.createProperty(constants::tap_on_duration_property_name,constants::tap_on_duration_default);
  tap_on_duration_property.setUnits(constants::ms_units);
  tap_on_duration_property.setRange(constants::tap_on_duration_min,constants::tap_on_duration_max);

  modular_server::Property & tap_count_property = modular_server_.createProperty(constants::tap_count_property_name,constants::tap_count_default);
  tap_count_property.setRange(constants::tap_count_min,constants::tap_count_max);

  modular_server::Property & dispense_velocity_property = modular_server_.createProperty(constants::dispense_velocity_property_name,constants::dispense_velocity_default);
  dispense_velocity_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&PelletDispenser::setDispenseVelocityLimitHandler));
  dispense_velocity_property.setUnits(step_dir_controller::constants::position_units_per_second_units);
  dispense_velocity_property.setRange(constants::dispense_velocity_min,constants::dispense_velocity_max);

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
      assay_status_.state_ptr = &constants::state_move_to_buzz_string;
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
      assay_status_.state_ptr = &constants::state_move_to_buzz_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_buzz_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_buzz_string;
    restoreVelocityLimits();
    moveStageToBuzzPosition();
  }
  else if (state_ptr == &constants::state_moving_to_buzz_string)
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
  else if (state_ptr == &constants::state_move_to_load_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_load_string;
    moveStageToLoadPosition();
  }
  else if (state_ptr == &constants::state_moving_to_load_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_tap_string;
    }
  }
  else if (state_ptr == &constants::state_tap_string)
  {
    assay_status_.state_ptr = &constants::state_tapping_string;
    tap();
  }
  else if (state_ptr == &constants::state_tapping_string)
  {
  }
  else if (state_ptr == &constants::state_wait_at_load_string)
  {
    assay_status_.state_ptr = &constants::state_waiting_at_load_string;
    waitAtLoad();
  }
  else if (state_ptr == &constants::state_waiting_at_load_string)
  {
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
      setDispenseVelocityLimits();
      assay_status_.state_ptr = &constants::state_ready_to_dispense_string;
    }
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
    moveStageToNextDispensePosition();
  }
  else if (state_ptr == &constants::state_moving_to_dispense_string)
  {
    if (stageAtTargetPosition())
    {
      restoreVelocityLimits();
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

StageController::PositionArray PelletDispenser::getBuzzPosition()
{
  StageController::PositionArray buzz_position;
  modular_server_.property(constants::buzz_position_property_name).getValue(buzz_position);

  return buzz_position;
}

StageController::PositionArray PelletDispenser::getLoadPosition()
{
  StageController::PositionArray load_position;
  modular_server_.property(constants::load_position_property_name).getValue(load_position);

  return load_position;
}

StageController::PositionArray PelletDispenser::getNextDeliverPosition()
{
  StageController::PositionArray next_deliver_position;
  modular_server_.property(constants::next_deliver_position_property_name).getValue(next_deliver_position);

  return next_deliver_position;
}

StageController::PositionArray PelletDispenser::getNextDispensePosition()
{
  StageController::PositionArray next_dispense_position;
  modular_server_.property(constants::next_dispense_position_property_name).getValue(next_dispense_position);

  return next_dispense_position;
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

long PelletDispenser::getWaitAtLoadDuration()
{
  long wait_at_load_duration;
  modular_server_.property(constants::wait_at_load_duration_property_name).getValue(wait_at_load_duration);

  return wait_at_load_duration;
}

long PelletDispenser::getTapPeriod()
{
  long tap_period;
  modular_server_.property(constants::tap_period_property_name).getValue(tap_period);

  return tap_period;
}

long PelletDispenser::getTapOnDuration()
{
  long tap_on_duration;
  modular_server_.property(constants::tap_on_duration_property_name).getValue(tap_on_duration);

  return tap_on_duration;
}

long PelletDispenser::getTapCount()
{
  long tap_count;
  modular_server_.property(constants::tap_count_property_name).getValue(tap_count);

  return tap_count;
}

void PelletDispenser::moveStageToBuzzPosition()
{
  StageController::PositionArray buzz_position = getBuzzPosition();
  moveStageTo(buzz_position);
}

void PelletDispenser::moveStageToLoadPosition()
{
  StageController::PositionArray load_position = getLoadPosition();
  moveStageSoftlyTo(load_position);
}

void PelletDispenser::waitAtLoad()
{
  long wait_at_load_duration = getWaitAtLoadDuration();
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::setMoveToNextDeliverPositionHandler),
    wait_at_load_duration);
  event_controller_.enable(event_id);
}

void PelletDispenser::moveStageToNextDeliverPosition()
{
  StageController::PositionArray next_deliver_position = getNextDeliverPosition();
  deliver_position_ = next_deliver_position;
  moveStageSoftlyTo(next_deliver_position);
}

void PelletDispenser::setDispenseVelocityLimit(size_t channel)
{
  long velocity_min;
  modular_server_.property(step_dir_controller::constants::velocity_min_property_name).getElementValue(channel,velocity_min);

  long dispense_velocity;
  modular_server_.property(constants::dispense_velocity_property_name).getElementValue(channel,dispense_velocity);

  long acceleration_max;
  modular_server_.property(step_dir_controller::constants::acceleration_max_property_name).getElementValue(channel,acceleration_max);

  temporarilySetLimits(channel,velocity_min,dispense_velocity,acceleration_max);
}

void PelletDispenser::setDispenseVelocityLimits()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    setDispenseVelocityLimit(channel);
  }
}

void PelletDispenser::restoreVelocityLimits()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    restoreLimits(channel);
  }
}

void PelletDispenser::moveStageToNextDispensePosition()
{
  StageController::PositionArray next_dispense_position = getNextDispensePosition();
  moveStageTo(next_dispense_position);
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
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::moveToBuzzHandler),
    return_delay);
  event_controller_.enable(event_id);
}

void PelletDispenser::setMoveToBuzzState()
{
  assay_status_.state_ptr = &constants::state_move_to_buzz_string;
}

void PelletDispenser::setMoveToLoadState()
{
  assay_status_.state_ptr = &constants::state_move_to_load_string;
}

void PelletDispenser::setWaitAtLoadState()
{
  assay_status_.state_ptr = &constants::state_wait_at_load_string;
}

void PelletDispenser::setMoveToNextDeliverPositionState()
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
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::setMoveToLoadHandler),
    buzz_period*buzz_count);
  event_controller_.enable(event_id);
}

void PelletDispenser::tap()
{
  long tap_power = getBuzzPower();
  long tap_period = getTapPeriod();
  long tap_on_duration = getTapOnDuration();
  long tap_count = getTapCount();

  power_switch_controller_ptr_->call(power_switch_controller::constants::set_power_function_name,
    constants::buzz_channel_group,
    tap_power);

  Array<size_t,constants::BUZZ_CHANNEL_COUNT> buzz_channels_array(constants::buzz_channels);

  power_switch_controller_ptr_->call(power_switch_controller::constants::add_pwm_function_name,
    buzz_channels_array,
    tap_on_duration,
    tap_period,
    tap_on_duration,
    tap_count);
  EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&PelletDispenser::setWaitAtLoadHandler),
    tap_period*tap_count);
  event_controller_.enable(event_id);
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
    setMoveToBuzzState();
  }
  else
  {
    assay_status_.state_ptr = &constants::state_assay_not_started_string;
  }
}

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

void PelletDispenser::setDispenseVelocityLimitHandler(size_t channel)
{
  if (assay_status_.state_ptr == &constants::state_ready_to_dispense_string)
  {
    setDispenseVelocityLimit(channel);
  }
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

void PelletDispenser::moveToDispenseHandler(int arg)
{
  setMoveToDispenseState();
}

void PelletDispenser::moveToBuzzHandler(int arg)
{
  setMoveToBuzzState();
}

void PelletDispenser::setMoveToLoadHandler(int arg)
{
  if (assay_status_.state_ptr == &constants::state_buzzing_string)
  {
    setMoveToLoadState();
  }
}

void PelletDispenser::setWaitAtLoadHandler(int arg)
{
  if (assay_status_.state_ptr == &constants::state_tapping_string)
  {
    setWaitAtLoadState();
  }
}

void PelletDispenser::setMoveToNextDeliverPositionHandler(int arg)
{
  if (assay_status_.state_ptr == &constants::state_waiting_at_load_string)
  {
    setMoveToNextDeliverPositionState();
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
